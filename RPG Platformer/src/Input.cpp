#include "../include/Input.h"
#include "../include/Engine.h"
Input* Input::_instance = nullptr;

Input::Input()
{
    _keystates = SDL_GetKeyboardState(nullptr);
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    if (_keystates[key] == 1)
        return true;

    return false;
}

void Input::HandleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_Quit();
            break;
        case SDL_KEYDOWN:
            KeyDown();
            break;
        case SDL_KEYUP:
            KeyUp();
            break;
        default:
            break;
        }
    }
}

void Input::KeyUp()
{
    _keystates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
    _keystates = SDL_GetKeyboardState(nullptr);
}
