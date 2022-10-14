#include "PartycleSystem.h"


PartycleSystem::PartycleSystem()
{

	UniformParticleGenerator* g = new UniformParticleGenerator("xd", 4, 0.9,15, { 0,10, 0 }, { 0 , 0, 0 },{10,10,10},{4,4,4}, {0.4,0.8,.4,1}, 4, 0.555, 0.2, {0,0,0},{0,10,0},{10,10,10}, false);
	_particlesGenerators.push_back(g);

	//GaussianParticleGenerator* g = new GaussianParticleGenerator("xd", { 0.2, .2, .2 }, { 20,20,20 }, .1, 10, 20, 0.9, { 10,30, 10 }, { 0 , 0, 0 }, { 0.4,0.8,.4,1 },4,0.555, 0.2 ,{0,-3,0});
	//_particlesGenerators.push_back(g);

	//GaussianParticleGenerator* g = new GaussianParticleGenerator("fuente",{ 0.2, .2, .2 }, {.2,.1,0.1}, 2, 5, 1, 0.9, { 25,50,0}, {5,10,0},{0,0,1,1});
	//_particlesGenerators.push_back(g);

	//GaussianParticleGenerator* x = new GaussianParticleGenerator("fuente2", { 0.2, .2, .2 }, { .2,.1,0.1 }, 2, 5, 1, 0.9, { 25,50,0 }, { -5,10,0 },{1,0,0,1},4,0.555,0.2,{0,-9.8,0});
	//_particlesGenerators.push_back(x);

	//g = new GaussianParticleGenerator("fuente3", { 0.2, .2, .2 }, { .2,.1,0.1 }, 2, 5, 1, 0.9, { 25,50,0 }, { 0,10,-5 }, { 0,1,0,1 });
	//_particlesGenerators.push_back(g);

	//g = new GaussianParticleGenerator("fuente4", { 0.2, .2, .2 }, { .2,.1,0.1 }, 2, 5, 1, 0.9, { 25,50,0 }, { 0,10,5 }, { 1,1,0,1 });
	//_particlesGenerators.push_back(g);
}

PartycleSystem::~PartycleSystem()
{
}

void PartycleSystem::update(double t)
{
	list<Particle*> aux;
	for (auto g : _particlesGenerators) {
		aux = g->generateParticles();
		for (auto p : aux)
			_particles.push_back(p);
	}

	list<Particle*>::iterator it = _particles.begin();

	while (it != _particles.end()) {

		(*it)->integrate(t);
		if (!(*it)->isAlive()) {

			delete* it;
			it = _particles.erase(it);
		}
		else it++;
	}
}

ParticleGenerator* PartycleSystem::getParticleGenerator(string name)
{
	return nullptr;
}
