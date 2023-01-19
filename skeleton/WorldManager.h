#pragma once
#include <PxPhysicsAPI.h>
#include <list>
#include <random>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "RigidParticle.h"
#include "RigidParticleGenerator.h"
#include "RigidParticleForceRegistry.h"
#include "RigidGaussianParticleGenerator.h"
#include "RigidExplosionGenerator.h"
#include "PartycleSystem.h"

using namespace physx;
using namespace std;

class WorldManager
{

public:

	WorldManager(PxScene* gScene_, PxPhysics* gPhysics_, PartycleSystem* particleSystem);
	~WorldManager();

	void collisionEfect(PxActor* actor1, PxActor* actor2);
	void update(double t);
	void deleteGenerators();
	void addExplosion(Vector3 pos);
	void noExplosion();


	void shoot();

	void comienzaRonda1();

	void comienzaRonda2();

	void comienzaRonda3();

private:

	list<RigidParticle*> rigidParticles;
	list<RigidParticleGenerator*> rigidParticleGen;

	RigidParticleForceRegistry* RPFR;

	PxScene* gScene;
	PxPhysics* gPhysics;
	PartycleSystem* particleSystem_;
	RenderItem* item;

	RigidExplosionGenerator* explosion = nullptr;

	double generationCoolDown;
	double actualCoolDown;
	double enemigosActuales;
	double bulletSpeed = 200;
	double bulletSize = 0.5;

	std::random_device rd{};
	std::mt19937 gen{ rd() };

	double enemigosTipo1, enemigosTipo2, enemigosTipo3;
	double enemigosEliminados = 0 , enemigosEliminar = 0;
	double enemigosEliminarRonda1, enemigosEliminarRonda2, enemigosEliminarRonda3;


};

