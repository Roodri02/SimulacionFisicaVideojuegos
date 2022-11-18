#pragma once
#include <list>
#include "Firework.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "CircleGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"

enum tipoFuerza { GRAVITY_FORCE, DRAG_FORCE };

class PartycleSystem {

public:
	PartycleSystem();
	~PartycleSystem();

	void update(double t);
	ParticleGenerator* getParticleGenerator(string name);
	void shootFirework(int type);
	void OnParticleDeath(Particle* p);
	void generateFireworkSystem();
	void anadeParticulasFirework(std::list<Particle*> pA);
	
	void addForceGenerator(Particle* p, ForceGenerator* fg);
	void addFuente();
	void addFuente2();
	void addNiebla();
	void addExplosion();



	void addGravityGenerator();	
	void addWindGenerator();
	void borraGenerator();
	
protected:
	std::list<Particle*> _particles;
	std::list<Firework*> _fireworks;
	std::list<ParticleGenerator*> _particlesGenerators;

	std::vector<Firework*> fireworks_pool;
	ParticleGenerator* firework_gen;
	ParticleForceRegistry* PFR;

};

