#pragma once

#include "PxPhysicsAPI.h"
#include "RigidParticle.h"
#include "foundation/PxTransform.h"

#include <list>
#include <random>
#include "RigidForceGenerator.h"
#include "RigidGravityForceGenerator.h"
#include "RigidWindGenerator.h"

using namespace physx;
using namespace std;

enum typeForce1 { RigidGravityForce,WindForce, NoForce};


class RigidParticleGenerator
{
public:
	virtual std::list<RigidParticle*> generateParticles(PxPhysics* gPhysics, PxScene* gScene_) = 0;
	void setForceGenerator(typeForce1) {
		switch (typeForce_)
		{
		case RigidGravityForce:
			fg = new RigidGravityForceGenerator({0,-9.8,0});
			break;
		case WindForce:
			fg = new RigidWindGenerator(0.8,0, { 0,0,0.0001 });
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
	PxVec3 std_dev_pos, std_dev_vel;
	Vector3 mean_Pos_, mean_Vel_;
	double generation_probability, mean_t;
	int num_particles;
	RigidForceGenerator* fg = nullptr;
	typeForce1 typeForce_;

};

