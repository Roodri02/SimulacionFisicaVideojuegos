#include "Particle.h"
#include <iostream>

using namespace physx;

Particle::Particle(Vector3 pos, Vector3 Vel,Vector3 Ace, double damp, double lifeTime_, Vector4 color)
{
	vel = Vel;
	ace = Ace;
	damping = damp;
	lifeTime = lifeTime_;
	pose = PxTransform(pos.x,pos.y,pos.z);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(40)), &pose,color);
}

Particle::Particle() {

}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	lifeTime -= t;
	if (lifeTime < 0)
		isAlive_ = false;
	pose.p = pose.p + vel * t;
	vel = vel * pow(damping, t) + ace * t;
	std::cout << t << "\n";
}

void Particle::setParticle(double mass_, double damp, double lifeTime_, Vector3 Vel, Vector3 Pos, Vector3 Ace, Vector4 color)
{
	masa = mass_;
	vel = Vel;
	ace = Ace;
	damping = damp;
	lifeTime = lifeTime_;
	pose = PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(5)), &pose, color);
}
