#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <iostream>

using namespace std;
using namespace physx;

class RigidParticle
{

public:

	RigidParticle(PxRigidDynamic* pxRigidDynamic_, double lifeTime_, RenderItem* renderItem_);
	~RigidParticle();

	PxRigidActor* getPxActor() {
		return pxRigidDynamic;
	}
	PxRigidDynamic* getPxRigidDynamic() {
		return pxRigidDynamic;
	}

	virtual void integrate(double t);


	bool isAlive() {
		return isAlive_;
	}

private:

	PxRigidDynamic* pxRigidDynamic;
	RenderItem* renderItem;

	double lifeTime;
	bool isAlive_ = true;

};

