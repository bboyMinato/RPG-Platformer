#pragma once
#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Camera.h"


#define RUN_FORCE 1.5f
#define JUMP_TIME 20.0f
#define JUMP_FORCE 4.f
#define ATTACK_TIME 10.f

class Warrior : public Character
{
public:
	Warrior() {}
	Warrior(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

	void AnimationState();

private:
	bool _isRunning = false;
	bool _isJumping = false;
	bool _isFalling = false;
	bool _isGrounded = false;
	bool _isAttacking = false;

	float _attackTime = 1.f;
	float _jumpTime = 1.f;
	float _jumpForce = 1.f;

	Animation* _animation = nullptr;
	RigidBody* _rigidBody = nullptr;
	Collider* _collider = nullptr;
	Vector2D _lastSafePosition;
};

