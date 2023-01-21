#include "../include/Warrior.h"
#include "../include/TextureManager.h"
#include "../include/Input.h"
#include "../include/CollisionHandler.h"
#include "../include/Engine.h"

Warrior::Warrior(Properties* props) : Character(props)
{
	_animation = new SpriteAnimation();
	_animation->SetProps(_textureID, 0, 6, 100);
	
	_rigidBody = new RigidBody();
	_rigidBody->SetGravity(1.5f);

	_attackTime = ATTACK_TIME;
	_jumpForce = JUMP_FORCE;
	_jumpTime = JUMP_TIME;	
	_slideTime = SLIDE_TIME;

	_collider = new Collider();
	_collider->SetBuffer(-55, -70, 0, -40);
}

void Warrior::Draw()
{
	_animation->Draw(_transform->X, _transform->Y, _width, _height, 1, 1, _flip);
	_collider->Draw();
}

void Warrior::Update(float dt)
{
	_isRunning = false;

	_rigidBody->UnsetForce();	

	// run backward
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
	{			
		_flip = SDL_FLIP_HORIZONTAL;
		_rigidBody->ApplyForceX(BACKWARD_FORCE * RUN_FORCE);
		_isRunning = true;		
	}


	// run forward
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
	{	
		_flip = SDL_FLIP_NONE;
		_rigidBody->ApplyForceX(FORWARD_FORCE * RUN_FORCE);
		_isRunning = true;	
	}
	
	// sliding
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) && _isGrounded)
	{		
		_flip = SDL_FLIP_NONE;
		_isSliding = true;
		_isCrouching = false;
		_isRunning = false;			
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) && _isGrounded)
	{
		_flip = SDL_FLIP_HORIZONTAL;
		_isSliding = true;
		_isCrouching = false;
		_isRunning = false;		
	}


	// slide timer
	if (_isSliding && _slideTime > 0)
		_slideTime -= dt;

	else
	{
		_isSliding = false;
		_slideTime = SLIDE_TIME;
	}


	// crouch
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) && !_isSliding)
	{
		_isCrouching = true;
	}

	else
		_isCrouching = false;


	// attack
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
	{
		_rigidBody->UnsetForce();
		_isAttacking = true;		
	}

	// attack timer
	if (_isAttacking && _attackTime > 0)
		_attackTime -= dt;

	else
	{
		_isAttacking = false;
		_attackTime = ATTACK_TIME;
	}


	// jump
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && _isGrounded && !_isCrouching)
	{		
		_isJumping = true;
		_isGrounded = false;	
		_jumpTime -= dt;
		_rigidBody->ApplyForceY(UPWARD_FORCE * _jumpForce);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && _isJumping && _jumpTime > 0)
	{		
		_jumpTime -= dt;
		_rigidBody->ApplyForceY(UPWARD_FORCE * _jumpForce);
	}

	else
	{
		_isJumping = false;
		_jumpTime = JUMP_TIME;		
	}	

	// fall
	if (_rigidBody->Velocity().Y > 0 && !_isGrounded)
		_isFalling = true;

	else
		_isFalling = false;


	//move on x axis
	_rigidBody->Update(1.2);
	_lastSafePosition.X = _transform->X;
	_transform->X += _rigidBody->Position().X;
	_collider->Set(_transform->X, _transform->Y, 56, 56);

	if (_collider->CollidingWithMap())
		_transform->X = _lastSafePosition.X;
	

	//move on y axis
	_rigidBody->Update(1.2);
	_lastSafePosition.Y = _transform->Y;
	_transform->Y += _rigidBody->Position().Y;
	_collider->Set(_transform->X, _transform->Y, 56, 56);


	if (_collider->CollidingWithMap())
	{
		_isGrounded = true;
		_transform->Y = _lastSafePosition.Y;
	}

	if (CollisionHandler::GetInstance()->MapCollision(_collider->GetBox()) && _isJumping)
	{		
		_isJumping = false;
		_isGrounded = false;
		_isFalling = true;		
	}	

	_origin->X = _transform->X + _width / 2;
	_origin->Y = _transform->Y + _height / 2;

	AnimationState();
	_animation->Update();
}

void Warrior::AnimationState()
{
	// idle
	_animation->SetProps(_textureID, 0, 6, 100);

	// attacking
	if (_isAttacking)
		_animation->SetProps(_textureID, 1, 6, 100);

	// running
	if(_isRunning)
		_animation->SetProps(_textureID, 2, 8, 100);

	// jumping
	if (_isJumping)
		_animation->SetProps(_textureID, 3, 8, 100);

	// falling
	if (_isFalling)
		_animation->SetProps(_textureID, 4, 8, 100);

	// crouching
	if (_isCrouching)
		_animation->SetProps(_textureID, 9, 3, 100);

	// sliding
	if (_isSliding)
		_animation->SetProps("player_purple_2", 2, 8, 100);
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}