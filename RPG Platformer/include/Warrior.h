#pragma once
#include "Character.h"
#include "SpirteAnimation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Camera.h"


#define RUN_FORCE 0.3f
#define JUMP_TIME 7.f
#define JUMP_FORCE 3.f
#define ATTACK_TIME 10.f
#define SLIDE_TIME 4.f

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
	bool _isCrouching = false;
	bool _isSliding = false;	

	float _attackTime = 1.f;
	float _jumpTime = 1.f;
	float _jumpForce = 1.f;
	float _slideTime = 1.f;
	float _jumpHeight = 10.f;

	SpriteAnimation* _animation = nullptr;
	RigidBody* _rigidBody = nullptr;
	Collider* _collider = nullptr;
	Vector2D _lastSafePosition;
};

