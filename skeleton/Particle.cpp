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

	if (1 / p.masa <= 0.0f) return;


	p.lifeTime -= t;
	if (p.lifeTime < 0)
		p.isAlive_ = false;

	p.pose.p = p.pose.p + p.vel * t;

	Vector3 totalAcceleration = p.ace; 
	totalAcceleration += p.force * (1/p.masa);

	p.vel += totalAcceleration * t;
	p.vel = p.vel * powf(p.damping, t);

	clearForce();





	if (p.destroySpace) {
		if (p.pose.p.x > p.actionSpace.x + p.actionSpaceWidth.x / 2 || p.pose.p.x < p.actionSpace.x - p.actionSpaceWidth.x / 2
			|| p.pose.p.y > p.actionSpace.y + p.actionSpaceWidth.y / 2 || p.pose.p.y < p.actionSpace.y - p.actionSpaceWidth.y / 2
			|| p.pose.p.z > p.actionSpace.z + p.actionSpaceWidth.z / 2 || p.pose.p.z < p.actionSpace.z - p.actionSpaceWidth.z / 2)
			p.isAlive_ = false;
	}
}

void Particle::setParticle(double mass_, double damp, double lifeTime_, Vector3 Vel, Vector3 Pos, Vector3 Ace, Vector4 color,
	double tamano,Vector3 actionSpace_,Vector3 actionSpaceWidth_,bool dSpace_, bool isVisible_)
{
	p.masa = mass_;
	p.vel = Vel;
	p.ace = Ace;
	p.damping = damp;
	p.lifeTime = lifeTime_;
	p.color = color;
	p.destroySpace = dSpace_;
	p.tamano = tamano;
	p.actionSpace = actionSpace_;
	p.actionSpaceWidth = actionSpaceWidth_;
	p.pose = PxTransform(Pos.x, Pos.y, Pos.z);
	p.isVisible = isVisible_;
	if(p.isVisible)
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(p.tamano)), &p.pose, p.color);
}

void Particle::setParticle(Particle* p_)
{

	ParticleVariables pAux = p_->getVariables();
	p = pAux;
	p.pose = PxTransform(pAux.pose.p.x, pAux.pose.p.y, pAux.pose.p.z);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(p.tamano)), &p.pose, p.color);
}


void Particle::clearForce() {
	p.force *= 0; 
}

void Particle::addForce(const Vector3& f) {
	p.force += f; 
}