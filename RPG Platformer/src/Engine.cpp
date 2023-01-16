#include "../include/Engine.h"
#include "../include/TextureManager.h"
#include "../include/Warrior.h"
#include "../include/Input.h"
#include "../include/Timer.h"
#include "../include/Camera.h"

Engine* Engine::_instance = nullptr;
Warrior* player = nullptr;

void Engine::Init()
{
	_isRunning = true;

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed; " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)))
		std::cout << "IMG_Init has failed; " << SDL_GetError() << std::endl;

	_window = SDL_CreateWindow("RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if (_window == nullptr)
		std::cout << "Window has failed to initialize! Error: " << SDL_GetError() << std::endl;

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (_renderer == nullptr)
		std::cout << "Renderer has failed to initialize! Error: " << SDL_GetError() << std::endl;

	if (!MapParser::GetInstance()->Load())
		std::cout << "Failed to load map!" << std::endl;

	_levelMap = MapParser::GetInstance()->GetMap("Level");

	TextureManager::GetInstance()->LoadTexture("background_layer_1", "res/img/oak_wood/background/background_layer_1.png");
	TextureManager::GetInstance()->LoadTexture("background_layer_2", "res/img/oak_wood/background/background_layer_2.png");
	TextureManager::GetInstance()->LoadTexture("background_layer_3", "res/img/oak_wood/background/background_layer_3.png");
	TextureManager::GetInstance()->LoadTexture("player", "res/img/oak_wood/character/char_blue.png");

	player = new Warrior(new Properties("player", 100, 200, 56, 56));

	Camera::GetInstance()->SetTarget(player->GetOrigin());
}

void Engine::Clean()
{
	TextureManager::GetInstance()->Clean();

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);

	SDL_Quit();
	IMG_Quit();
}

void Engine::Quit()
{

}

void Engine::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
	_levelMap->Update();
	player->Update(dt);
	Camera::GetInstance()->Update(dt);
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);

	TextureManager::GetInstance()->Draw("background_layer_1", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	TextureManager::GetInstance()->Draw("background_layer_2", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	TextureManager::GetInstance()->Draw("background_layer_3", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	_levelMap->Render();
	player->Draw();

	SDL_RenderPresent(_renderer);
}

void Engine::Events()
{
	Input::GetInstance()->HandleEvents();
}