#pragma once
#include "Vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

#define UPWARD_FORCE -1.f
#define DOWNARD_FORCE 1.f
#define BACKWARD_FORCE -1
#define FORWARD_FORCE 1.f

class RigidBody
{
public:
	RigidBody()
	{
		_mass = UNI_MASS;
		_gravity = GRAVITY;
	}

	//setters for gravity and mass
	inline void SetMass(float mass) { _mass = mass; }
	inline void SetGravity(float gravity) { _gravity = gravity; }

	//force
	inline void ApplyForce(Vector2D F) { _force = F; }
	inline void ApplyForceX(float Fx) { _force.X = Fx; }
	inline void ApplyForceY(float Fy) { _force.Y = Fy; }
	inline void UnsetForce() { _force = Vector2D(0, 0); }

	//Friction
	inline void ApplyFriction(Vector2D Fr) { _friction = Fr; }
	inline void UnsetFriction() { _friction = Vector2D(0, 0); }

	//Getters
	inline float GetMass() { return _mass; }
	inline Vector2D Position() { return _position; }
	inline Vector2D Velocity() { return _velocity; }
	inline Vector2D Accelaration() { return _accelaration; }

	//Update
	void Update(float dt)
	{
		_accelaration.X = (_force.X + _friction.X) / _mass;
		_accelaration.Y = _gravity + (_force.Y / _mass);
		_velocity = _accelaration * dt;
		_position = _velocity * dt;
	}

private:
	float _mass;
	float _gravity;

	//forces that impact objects
	Vector2D _force;
	Vector2D _friction;

	//movement
	Vector2D _position;
	Vector2D _velocity;
	Vector2D _accelaration;
};