#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <iostream>

using namespace std;
using namespace physx;


enum typeRigidParticle { Bullet, Static ,Enemy};

class RigidParticle
{

public:

	RigidParticle(PxRigidDynamic* pxRigidDynamic_, double lifeTime_, RenderItem* renderItem_,double mass);
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

	double getMass() {
		return mass_;
	}

private:

	PxRigidDynamic* pxRigidDynamic;
	RenderItem* renderItem;

	double lifeTime;
	bool isAlive_ = true;
	double mass_;

};

