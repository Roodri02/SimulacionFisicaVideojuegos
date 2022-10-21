#include "Particle.h"
#include <iostream>

using namespace physx;

Particle::Particle(Vector3 pos, Vector3 Vel,Vector3 Ace, double damp, double lifeTime_, Vector4 color)
{
	p.vel = Vel;
	p.ace = Ace;
	p.damping = damp;
	p.lifeTime = lifeTime_;
	p.pose = PxTransform(pos.x,pos.y,pos.z);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(40)), &p.pose,color);
}

Particle::Particle() {

}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	p.lifeTime -= t;
	if (p.lifeTime < 0)
		p.isAlive_ = false;
	p.pose.p = p.pose.p + p.vel * t;
	p.vel = p.vel * pow(p.damping, t) + p.ace * t;

	if (p.destroySpace) {
		if (p.pose.p.x > p.actionSpace.x + p.actionSpaceWidth.x / 2 || p.pose.p.x < p.actionSpace.x - p.actionSpaceWidth.x / 2
			|| p.pose.p.y > p.actionSpace.y + p.actionSpaceWidth.y / 2 || p.pose.p.y < p.actionSpace.y - p.actionSpaceWidth.y / 2
			|| p.pose.p.z > p.actionSpace.z + p.actionSpaceWidth.z / 2 || p.pose.p.z < p.actionSpace.z - p.actionSpaceWidth.z / 2)
			p.isAlive_ = false;
	}


	std::cout << t << "\n";
}

void Particle::setParticle(double mass_, double damp, double lifeTime_, Vector3 Vel, Vector3 Pos, Vector3 Ace, Vector4 color,
	double tamano,Vector3 actionSpace_,Vector3 actionSpaceWidth_,bool dSpace_)
{
	p.masa = mass_;
	p.vel = Vel;
	p.ace = Ace;
	p.damping = damp;
	p.lifeTime = lifeTime_;
	p.destroySpace = dSpace_;
	p.actionSpace = actionSpace_;
	p.actionSpaceWidth = actionSpaceWidth_;
	p.pose = PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(tamano)), &p.pose, color);
}
