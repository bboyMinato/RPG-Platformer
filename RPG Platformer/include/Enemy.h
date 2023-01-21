#pragma once
#include "Character.h"
#include "SpirteAnimation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"

class Enemy : public Character
{
public:
	Enemy() {}
	Enemy(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

	void AnimationState();

private:
	bool _isGrounded = false;
	bool _isDead = false;

	SpriteAnimation* _animation = nullptr;
	RigidBody* _rigidBody = nullptr;
	Collider* _collider = nullptr;
	Vector2D _lastSafePosition;
};