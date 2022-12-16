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

using namespace physx;
using namespace std;

class WorldManager
{

public:

	WorldManager(PxScene* gScene_, PxPhysics* gPhysics_);
	~WorldManager();

	void collisionEfect(PxActor* actor1, PxActor* actor2);
	void update(double t);
	void deleteGenerators();

	void addRigidGaussianGenerator();
	void addExplosion();
	void noExplosion();

private:

	list<RigidParticle*> rigidParticles;
	list<RigidParticleGenerator*> rigidParticleGen;

	RigidParticleForceRegistry* RPFR;

	PxScene* gScene;
	PxPhysics* gPhysics;
	RenderItem* item;

	RigidExplosionGenerator* explosion = nullptr;

	double generationCoolDown;
	double actualCoolDown;

	std::random_device rd{};
	std::mt19937 gen{ rd() };

};

