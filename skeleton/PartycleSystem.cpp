#include "PartycleSystem.h"


PartycleSystem::PartycleSystem()
{
	GaussianParticleGenerator* g = new GaussianParticleGenerator("fuente",{ 0.2, .2, .2 }, {.2,.1,0.1}, 2, 5, 1, 0.9, { 25,50,0}, {30,10,0},{0,0,1,1});
	_particlesGenerators.push_back(g);

	g = new GaussianParticleGenerator("fuente2", { 0.2, .2, .2 }, { .2,.1,0.1 }, 2, 5, 1, 0.9, { 25,50,0 }, { -30,10,0 },{1,0,0,1});
	_particlesGenerators.push_back(g);

	g = new GaussianParticleGenerator("fuente3", { 0.2, .2, .2 }, { .2,.1,0.1 }, 2, 5, 1, 0.9, { 25,50,0 }, { 0,10,-30 }, { 0,1,0,1 });
	_particlesGenerators.push_back(g);

	g = new GaussianParticleGenerator("fuente4", { 0.2, .2, .2 }, { .2,.1,0.1 }, 2, 5, 1, 0.9, { 25,50,0 }, { 0,10,30 }, { 1,1,0,1 });
	_particlesGenerators.push_back(g);
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

	for (auto i : _particles) {

		i->integrate(t);
	}
}

ParticleGenerator* PartycleSystem::getParticleGenerator(string name)
{
	return nullptr;
}
