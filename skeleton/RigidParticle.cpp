#include "RigidParticle.h"


RigidParticle::RigidParticle(PxRigidDynamic* pxRigidDynamic_, double lifeTime_, RenderItem* renderItem_)
{
	lifeTime = lifeTime_;
	pxRigidDynamic = pxRigidDynamic_;
	renderItem = renderItem_;
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
