#include "RigidExplosionGenerator.h"

void RigidExplosionGenerator::updateForce(RigidParticle* p, double t)
{


	Vector3 forceDir{ 0,0,0 };
	Vector3 force;
	Vector3 meanPos = p->getPxRigidDynamic()->getGlobalPose().p;

	float r = sqrt(pow(meanPos.x - center.x, 2)
		+ pow((meanPos.y - center.y), 2)
		+ pow((meanPos.z - center.z), 2));


	if (r < radio)
	{
		double a = K / pow(r, 2);
		double b = pow(e, -(t / explosion));

		forceDir = a * b * Vector3(meanPos.x - center.x, meanPos.y - center.y,
			meanPos.z - center.z);

	}

	p->getPxRigidDynamic()->addForce(forceDir, PxForceMode::eFORCE);





}