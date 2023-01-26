#include "..\include\Enemy.h"
#include "../include/TextureManager.h"
#include "../include/CollisionHandler.h"
#include "../include/ObjectManager.h"

static RegisterObject<Enemy> registerobject("BOAR");

Enemy::Enemy(Properties* props) : Character(props)
{
	_animation = new SpriteAnimation();
	_animation->SetProps(_textureID, 0, 4, 100);	

	_rigidBody = new RigidBody();
	_rigidBody->SetGravity(1.5f);

	_collider = new Collider();
	_collider->SetBuffer(0, -10, -80, -53);
}

void Enemy::Draw()
{
	_animation->Draw(_transform->X, _transform->Y, _width, _height, 1, 1, _flip);	
	_collider->Draw();
}

void Enemy::Update(float dt)
{
	_rigidBody->UnsetForce();
	_rigidBody->SetGravity(1);

	//move on x axis
	_rigidBody->Update(1.2);
	_lastSafePosition.X = _transform->X;
	_transform->X += _rigidBody->Position().X;
	_collider->Set(_transform->X, _transform->Y, 48, 32);


	if (_collider->CollidingWithMap())
		_transform->X = _lastSafePosition.X;


	//move on y axis
	_rigidBody->Update(1.2);
	_lastSafePosition.Y = _transform->Y;
	_transform->Y += _rigidBody->Position().Y;
	_collider->Set(_transform->X, _transform->Y, 48, 32);


	if (_collider->CollidingWithMap())
	{
		_isGrounded = true;
		_transform->Y = _lastSafePosition.Y;
	}
		
	_origin->X = _transform->X + (float)_width / 2;
	_origin->Y = _transform->Y + (float)_height / 2;

	_animation->Update();
}

void Enemy::AnimationState()
{
}

void Enemy::Clean()
{
	TextureManager::GetInstance()->Clean();
}