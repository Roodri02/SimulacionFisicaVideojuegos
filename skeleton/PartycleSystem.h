#pragma once
#include <list>
#include "Firework.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "CircleGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "ExplosionGenerator.h"
#include "AnchoredSpringFG.h"
#include "SpringForceGenerator.h"
#include "BuoyancyForceGenerator.h"

enum tipoFuerza { GRAVITY_FORCE, DRAG_FORCE };

class PartycleSystem {

public:
	PartycleSystem();
	~PartycleSystem();

	void update(double t);
	
	void addForceGenerator(Particle* p, ForceGenerator* fg);
	void addExplosionEffect();

	void generateBouyancyDemo();
	void addFuente();

	void addGaussianGenerator(typeForce t= GravityForce);
	void addUniformGenerator(typeForce t = GravityForce);
	void addCircleGenerator(typeForce t = GravityForce);
	void borraGenerator();
	void createFireworks();
	void activaFireworks();
	void desactivaFirework();
	void generateAnchoredDemo(Vector3 pos);
	void explodeEnemy(Vector3 pos);
	
protected:
	std::list<Particle*> _particles;
	std::list<Firework*> _fireworks;
	std::list<ParticleGenerator*> _particlesGenerators;

	std::vector<Firework*> fireworks_pool;
	ParticleGenerator* firework_gen;
	ParticleForceRegistry* PFR;

	SpringForceGenerator* f1;
	SpringForceGenerator* f2;

	UniformParticleGenerator* fireworkGenerator1;
	UniformParticleGenerator* fireworkGenerator2;

	ExplosionGenerator* exp;
	bool explosion=false;
};

