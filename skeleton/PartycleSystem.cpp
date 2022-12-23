#include "PartycleSystem.h"
#include <iostream>

PartycleSystem::PartycleSystem()
{


	//addGaussianGenerator(Nada);
	PFR =  new ParticleForceRegistry();
}

PartycleSystem::~PartycleSystem()
{
}

void PartycleSystem::update(double t)
{
	list<Particle*>::iterator it = _particles.begin();
	while (it != _particles.end()) {
		(*it)->integrate(t);
		if (!(*it)->isAlive()) {

			GetCamera();

			if (Firework* f = dynamic_cast<Firework*>(*it)) {
				list<Particle*> pAux = f->Explode();

				for (auto i : pAux)
					_particles.push_back(i);
			}
			PFR->deleteParticleRegistry(*it);
			delete* it;
			it = _particles.erase(it);

		}
		else it++;
	}

	PFR->updateForces(t);

	if (explosion) exp->addConst(t);

	list<Particle*> aux;
	for (auto g : _particlesGenerators) {
		aux = g->generateParticles();
		for (auto p : aux) {
			if(g->getForceGenerator() != nullptr)PFR->addRegistry(g->getForceGenerator(), p);
			_particles.push_back(p);
		}
	}

}


void PartycleSystem::addForceGenerator(Particle* p, ForceGenerator* fg)
{
	PFR->addRegistry(fg, p);
}


void PartycleSystem::addExplosionEffect()
{

	if (_particles.size() > 0) {
		exp = new ExplosionGenerator(400, 400, 200, { 0, 0, 0 });
		explosion = true;
	}

	for (auto i : _particles) {
		PFR->addRegistry(exp, i);
	}
}

void PartycleSystem::generateBouyancyDemo()
{
	Particle* p4 = new Particle();
	p4->setParticle(10, 0.85, 50, { 0,0,0 }, { 10,0,0 }, { 0,0,0 }, { 0.35,0.1,0.8,1 }, 0.5, { 0,0,0 }, { 0,0,0 }, false, true,
		CreateShape(physx::PxSphereGeometry(0.5)));
	BuoyancyForceGenerator* f4 = new BuoyancyForceGenerator(1, 7, 0.05, 7, 200);
	PFR->addRegistry(f4, p4);
	GravityForceGenerator* fg =  new GravityForceGenerator({0,-9.8,0});
	PFR->addRegistry(fg, p4);

	_particles.push_back(p4);
}

void PartycleSystem::addGaussianGenerator(typeForce type)
{
	Particle* p = new Particle();
	ParticleGenerator* gen;

	p->setParticle(10, 0.8, 100, Vector3(0, 0, 0), Vector3(0, 0, 0),
		Vector3(0, 0, 0), { 1,0,1,1 }, 0.5, { 0,0,0 }, { 0,0,0 }, false, false,CreateShape(physx::PxSphereGeometry(4)));

	gen = new GaussianParticleGenerator("Enemigos1", Vector3(100, 0.1, 100), Vector3(0.1, 0.1, 0.1),{0,50,0},{0,0,0}, 0.3, 100, 1, 0.8, p,type);
	_particlesGenerators.push_back(gen);
}

void PartycleSystem::addUniformGenerator(typeForce type)
{
	Particle* p = new Particle();
	ParticleGenerator* gen;

	//p->setParticle(4, 0.9, 50, Vector3(0, 0, 0), Vector3(0, 0, 0),
		//Vector3(0, 0, 0), { 1,1,1,1 }, 0.5, { 0,40,0 }, { 10,10,10 }, false, false);

	gen = new UniformParticleGenerator("g",10,0.98, Vector3(10, 10, 10), Vector3(3, 3, 3),p,type);
	gen->setMeanPos(Vector3(15, 30, 0), { 0,0,0 });
	_particlesGenerators.push_back(gen);
}

void PartycleSystem::addCircleGenerator(typeForce type)
{
	Particle* p = new Particle();
	ParticleGenerator* gen;

	//p->setParticle(4, 0.9, 50, Vector3(0, 0, 0), Vector3(0, 0, 0),
		//Vector3(0, 0, 0), { 1,1,1,1 }, 0.5, { 0,40,0 }, { 10,10,10 }, false, false);

	gen = new CircleGenerator({ 0,0,0 }, 10, 10, 0.9, p, 0,type);
	gen->setMeanPos(Vector3(15, 30, 0), { 0,0,0 });
	_particlesGenerators.push_back(gen);
}

void PartycleSystem::borraGenerator()
{
	auto it = _particlesGenerators.begin();
	while (_particlesGenerators.size() != 0) {
		it = _particlesGenerators.erase(it);
	}
}
