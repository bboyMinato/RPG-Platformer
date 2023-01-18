#include "../include/Warrior.h"
#include "../include/TextureManager.h"
#include "../include/Input.h"
#include "../include/CollisionHandler.h"

Warrior::Warrior(Properties* props) : Character(props)
{
	_animation = new Animation();
	_animation->SetProps(_textureID, 0, 6, 60);

	_rigidBody = new RigidBody();
	_rigidBody->SetGravity(1.5f);

	_attackTime = ATTACK_TIME;
	_jumpForce = JUMP_FORCE;
	_jumpTime = JUMP_TIME;	

	_collider = new Collider();
	_collider->SetBuffer(-55, -70, 0, -40);
}

void Warrior::Draw()
{
	_animation->Draw(_transform->X, _transform->Y, _width, _height, _flip);

	Vector2D cam = Camera::GetInstance()->GetPosition();

	SDL_Rect box = _collider->GetBox();
	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt)
{
	_isRunning = false;

	_rigidBody->UnsetForce();
	_rigidBody->SetGravity(2);

	// run backward
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
	{						
		_rigidBody->ApplyForceX(BACKWARD_FORCE * RUN_FORCE);
		_isRunning = true;
		_flip = SDL_FLIP_HORIZONTAL;
	}

	// run forward
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
	{	
		_rigidBody->ApplyForceX(FORWARD_FORCE * RUN_FORCE);
		_isRunning = true;
		_flip = SDL_FLIP_NONE;
	}

	// attack
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
	{
		_rigidBody->UnsetForce();
		_isAttacking = true;		
	}

	// jump
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && _isGrounded)
	{
		_rigidBody->ApplyForceY(UPWARD_FORCE * _jumpForce);
		_isJumping = true;
		_isGrounded = false;			
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

	// attack timer
	if (_isAttacking && _attackTime > 0)
		_attackTime -= dt;

	else
	{
		_isAttacking = false;
		_attackTime = ATTACK_TIME;
	}

	//move on x axis
	_rigidBody->Update(1.5);
	_lastSafePosition.X = _transform->X;
	_transform->X += _rigidBody->Position().X;
	_collider->Set(_transform->X, _transform->Y, 56, 56);

	if (CollisionHandler::GetInstance()->MapCollision(_collider->GetBox()))
		_transform->X = _lastSafePosition.X;

	//move on y axis
	_rigidBody->Update(1.5);
	_lastSafePosition.Y = _transform->Y;
	_transform->Y += _rigidBody->Position().Y;
	_collider->Set(_transform->X, _transform->Y, 56, 56);


	if (CollisionHandler::GetInstance()->MapCollision(_collider->GetBox()))
	{
		_isGrounded = true;
		_transform->Y = _lastSafePosition.Y;
	}

	_origin->X = _transform->X + _width / 2;
	_origin->Y = _transform->Y + _height / 2;

	AnimationState();
	_animation->Update();
}

void Warrior::AnimationState()
{
	// idle
	_animation->SetProps(_textureID, 0, 6, 60);

	// attacking
	if (_isAttacking)
		_animation->SetProps(_textureID, 1, 6, 60);

	// running
	if(_isRunning)
		_animation->SetProps(_textureID, 2, 8, 60);

	// jumping
	if (_isJumping)
		_animation->SetProps(_textureID, 3, 8, 60);

	// falling
	if (_isFalling)
		_animation->SetProps(_textureID, 4, 8, 60);
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}