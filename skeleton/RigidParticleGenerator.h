#pragma once

#include "PxPhysicsAPI.h"
#include "RigidParticle.h"
#include "foundation/PxTransform.h"

#include <list>
#include <random>

using namespace physx;
using namespace std;

class RigidParticleGenerator
{
public:
	virtual std::list<RigidParticle*> generateParticles(PxPhysics* gPhysics, PxScene* gScene_) = 0;


protected:



	PxShape* shape;
	RenderItem* renderItem;
	PxVec3 std_dev_pos;
	Vector3 mean_Pos_, mean_Vel_;
	double generation_probability, mean_t;
	int num_particles;

};

