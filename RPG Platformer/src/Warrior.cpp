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

	_jumpForce = JUMP_FORCE;
	_jumpTime = JUMP_TIME;

	_collider = new Collider();
	_collider->SetBuffer(-55, -70, 0, -40);
}

void Warrior::Draw()
{
	_animation->Draw(_transform->X, _transform->Y, _width, _height);

	Vector2D cam = Camera::GetInstance()->GetPosition();

	SDL_Rect box = _collider->GetBox();

	box.x -= cam.X;
	box.y -= cam.Y;

	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt)
{
	if (_animation->_flip == SDL_FLIP_HORIZONTAL)
		_animation->SetProps(_textureID, 0, 6, 60, SDL_FLIP_HORIZONTAL);

	else
		_animation->SetProps(_textureID, 0, 6, 60);

	_rigidBody->UnsetForce();
	_rigidBody->SetGravity(2);

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
	{
		_animation->SetProps(_textureID, 2, 8, 60, SDL_FLIP_HORIZONTAL);
		_rigidBody->ApplyForceX(-1);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
	{
		_animation->SetProps(_textureID, 2, 8, 60);
		_rigidBody->ApplyForceX(1);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && _isGrounded)
	{
		_animation->SetProps(_textureID, 3, 8, 60);

		_isJumping = true;
		_isGrounded = false;
		_rigidBody->ApplyForceY(-1 * _jumpForce);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && _isJumping && _jumpTime > 0)
	{
		_animation->SetProps(_textureID, 4, 8, 60);

		_jumpTime -= 0.5f;
		_rigidBody->ApplyForceY(-1 * _jumpForce);
	}

	else
	{
		_isJumping = false;
		_jumpTime = JUMP_TIME;
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

	_animation->Update();
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}