#pragma once
#include <map>
#include <string>
#include <vector>
#include "SDL.h"
#include "Animation.h"

struct Sequence
{
	int speed;
	int frameCount;
	int width, height;
	std::vector<std::string> textureIDs;
};

class SeqAnimation : public Animation
{
public:
	SeqAnimation(bool repeat = true);

	virtual void Update();
	void Parse(std::string source);
	void SetCurrentSeq(std::string seqID);
	void SetRepeat(bool repeat) { _repeat = true; }
	void DrawFrame(float x, float y, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	Sequence _currentSeq;
	std::map<std::string, Sequence> _seqMap;
};