#include "../include/SeqAnimation.h"
#include "../include/TextureManager.h"
#include "tinyxml.h"
#include <iostream>

SeqAnimation::SeqAnimation(bool repeat) : Animation(repeat)
{
}

void SeqAnimation::Update()
{
	if (_repeat || _isEnded)
	{
		_isEnded = false;
		_currentFrame = (SDL_GetTicks() / _currentSeq.speed) % _currentSeq.frameCount;
	}

	if (!_repeat && _currentFrame == (_currentSeq.frameCount - 1))
	{
		_isEnded = true;
		_currentFrame = (_currentSeq.frameCount - 1);
	}
}

void SeqAnimation::Parse(std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error())
		std::cout << "Failed to load animation file: " << source << std::endl;

	TiXmlElement* root = xml.RootElement();

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("sequence"))
		{
			Sequence seq;
			std::string seqID = e->Attribute("id");
			e->Attribute("speed", &seq.speed);
			e->Attribute("widht", &seq.width);
			e->Attribute("height", &seq.height);
			e->Attribute("frameCount", &seq.frameCount);

			for (TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement())
				seq.textureIDs.push_back(frame->Attribute("textureID"));

			_seqMap[seqID] = seq;
		}
	}
}

void SeqAnimation::SetCurrentSeq(std::string seqID)
{
	if (_seqMap.count(seqID) > 0)
		_currentSeq = _seqMap[seqID];

	else
		std::cout << "Given sequence ID in not matching: " << seqID << std::endl;
}

void SeqAnimation::DrawFrame(float x, float y, float xScale, float yScale, SDL_RendererFlip flip)
{
	TextureManager::GetInstance()->Draw(_currentSeq.textureIDs[_currentFrame], x, y, _currentSeq.width, _currentSeq.height, xScale, yScale, flip);
}
