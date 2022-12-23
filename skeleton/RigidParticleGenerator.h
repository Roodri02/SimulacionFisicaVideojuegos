#pragma once

#include "PxPhysicsAPI.h"
#include "RigidParticle.h"
#include "foundation/PxTransform.h"

#include <list>
#include <random>
#include "RigidForceGenerator.h"
#include "RigidGravityForceGenerator.h"

using namespace physx;
using namespace std;

enum typeForce1 { RigidGravityForce, NoForce};


class RigidParticleGenerator
{
public:
	virtual std::list<RigidParticle*> generateParticles(PxPhysics* gPhysics, PxScene* gScene_) = 0;
	void setForceGenerator(Vector3 gravity) {
		switch (typeForce_)
		{
		case RigidGravityForce:
			fg = new RigidGravityForceGenerator(gravity);
			break;
		case NoForce:
			break;
		default:
			break;
		}
	}

	RigidForceGenerator* getForceGenerator() {
		return fg;
	}

protected:


	PxShape* shape;
	RenderItem* renderItem;
	PxVec3 std_dev_pos;
	Vector3 mean_Pos_, mean_Vel_;
	double generation_probability, mean_t;
	int num_particles;
	RigidForceGenerator* fg = nullptr;
	typeForce1 typeForce_;

};

