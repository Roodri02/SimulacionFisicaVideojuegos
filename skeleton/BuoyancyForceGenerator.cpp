#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float a, float b, float c, float d)
{
	_height = h;
	_volume = a * b * c;
	_liquid_density = d;

	_liquid_particle = new Particle();

	_liquid_particle->setParticle(10,0.85,50, {0,0,0}, {20,30,20}, {0,0,0},
		{0,0.1,0.7,1},1, {0,0,0}, {0,0,0} ,false, true, CreateShape(physx::PxBoxGeometry(a, b, c)));
}

void BuoyancyForceGenerator::updateForce(Particle* p, double t)
{
	float h = p->getVariables().pose.p.y;
	float h0 = _liquid_particle->getVariables().pose.p.y;

	Vector3 f(0, 0, 0);
	float immersed = 0;

	if (h - h0 > _height * 0.5) { immersed = 0.0; }
	else if (h0 - h > _height * 0.5) { immersed = 1.0; }
	else { immersed = (h0 - h) / _height + 0.5; }

	f.y = _liquid_density * _volume * immersed;

	p->addForce(f);
}