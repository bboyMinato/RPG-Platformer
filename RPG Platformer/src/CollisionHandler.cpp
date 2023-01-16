#include "../include/CollisionHandler.h"

CollisionHandler* CollisionHandler::_instance = nullptr;

CollisionHandler::CollisionHandler()
{
    _collisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().back();
    _collisionTileMap = _collisionLayer->GetTileMap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);

    return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    int tileSize = 16;
    int rowCount = 62;
    int colCount = 90;

    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w) / tileSize;

    int top_tile = a.y / tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;

    if (left_tile < 0)
        left_tile = 0;

    if (right_tile > colCount)
        right_tile = colCount;

    if (top_tile < 0)
        top_tile = 0;

    if (bottom_tile > rowCount)
        bottom_tile = rowCount;

    //ERROR
    for (int i = left_tile; i <= right_tile; i++)
    {
        for (int j = top_tile; j <= bottom_tile; j++)
        {
            if (_collisionTileMap[j][i] > 0)
                return true;
        }
    }

    return false;
}