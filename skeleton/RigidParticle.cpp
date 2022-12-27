#include "RigidParticle.h"


RigidParticle::RigidParticle(PxRigidDynamic* pxRigidDynamic_, double lifeTime_, RenderItem* renderItem_,double mass, typeRigidParticle type)
{
	lifeTime = lifeTime_;
	pxRigidDynamic = pxRigidDynamic_;
	renderItem = renderItem_;
	mass_ = mass;
	type_ = type;
}

void RigidParticle::integrate(double t)
{
	lifeTime -= t;
	if (lifeTime < 0)
		isAlive_ = false;
}

RigidParticle::~RigidParticle()
{
	DeregisterRenderItem(renderItem);
}
