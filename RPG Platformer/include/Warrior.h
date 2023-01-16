#pragma once
#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Camera.h"

#define JUMP_TIME 20.0f;
#define JUMP_FORCE 4.f;

class Warrior : public Character
{
public:
	Warrior() {}
	Warrior(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	bool _isJumping = false;
	bool _isGrounded = true;

	float _jumpTime = 1.f;
	float _jumpForce = 1.f;

	Animation* _animation = nullptr;
	RigidBody* _rigidBody = nullptr;
	Collider* _collider = nullptr;
	Vector2D _lastSafePosition;
};

