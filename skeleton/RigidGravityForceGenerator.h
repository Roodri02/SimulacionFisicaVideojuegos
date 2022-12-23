#pragma once
#include "RigidForceGenerator.h"
#include "RigidParticle.h"

class RigidGravityForceGenerator : public RigidForceGenerator
{
public:
	RigidGravityForceGenerator(const Vector3& g);

	virtual void updateForce(RigidParticle* particle, double t);

	inline void setGravity(Vector3 g) {
		_gravity = g;
	}

private:
	Vector3 _gravity;
};

