#include "Particle.h"

using namespace physx;

Particle::Particle(Vector3 pos, Vector3 Vel,Vector3 Ace, double damp)
{
	vel = Vel;
	ace = Ace;
	damping = damp;
	pose = PxTransform(pos.x,pos.y,pos.z);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(5)), &pose,Vector4(0.2,0.5,0.8,1));
	RegisterRenderItem(renderItem);
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p = pose.p +  vel * t;
	vel = vel * pow(damping, t) + ace * t;
}
