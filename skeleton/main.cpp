#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "Particle.h"
#include "Proyectil.h"
#include "Diana.h"
#include "PartycleSystem.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;


std::vector<Proyectil*> gestorParticulas;
PartycleSystem* partycleSystem;

Diana* diana;

ContactReportCallback gContactReportCallback;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, 0.0f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	partycleSystem = new PartycleSystem();

	partycleSystem->generateFireworkSystem();

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	
	//diana = new Diana();
	
	partycleSystem->update(t);

	for (int i = 0; i < gestorParticulas.size(); i++) {
		
		gestorParticulas[i]->integrate(t);
		
		if (!gestorParticulas[i]->isAlive()) {
			delete gestorParticulas[i];
			gestorParticulas.erase(gestorParticulas.begin() + i);
			i--;
		}
	}

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	for (int i = 0; i < gestorParticulas.size(); i++)
		delete gestorParticulas[i];

	

	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'Z': 
	{
		//gestorParticulas.push_back(new Proyectil(TipoBala::PISTOL));
		partycleSystem->borraGenerator();
		break; 
	}
	case 'X':
	{
		//gestorParticulas.push_back(new Proyectil(TipoBala::ARTILLERY));
		//partycleSystem->addFuente2();
		partycleSystem->addExplosionEffect();
		break;
	}
	case 'M' :
	{
		partycleSystem->generateSpringDemo();
		break;
	}
	case 'K':
	{
		partycleSystem->generateAnchoredDemo();
		break;
	}
	case 'C':
	{
		//gestorParticulas.push_back(new Proyectil(TipoBala::FIREBALL ));
		//partycleSystem->addExplosion();
		partycleSystem->addGaussianGenerator();
		break;
	}
	case 'J': {
		partycleSystem->addUniformGenerator(WindForce);
		break;
	}
	case 'G': {
		partycleSystem->addUniformGenerator(WhirlwindForce);
		break;
	}
	case 'T':
	{
		//partycleSystem->shootFirework(5);
		partycleSystem->addParticles(20);
		break;
	}
	case 'Q':
	{
		//partycleSystem->shootFirework(1);
		partycleSystem->addCircleGenerator(WhirlwindForce);
		break;
	}
	case 'W':
	{
		//partycleSystem->shootFirework(1);
		partycleSystem->addCircleGenerator();
		break;
	}
	case 'L':
	{
		partycleSystem->shootFirework(2);
		break;
	}
	case 'F' : {
		partycleSystem->addFuente();
		break;
	}
	case 'N': {
		partycleSystem->addNiebla();
		break;
	}

	//case ' ':	break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}