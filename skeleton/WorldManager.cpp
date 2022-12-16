#include "WorldManager.h"
WorldManager::WorldManager(PxScene* gScene_, PxPhysics* gPhysics_) {

	gScene = gScene_;
	gPhysics = gPhysics_;

	PxRigidStatic* plano = gPhysics->createRigidStatic(PxTransform({ -100,-50,-100 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.3, 100));
	plano->attachShape(*shape);
	item = new RenderItem(shape, plano, { 0.3, 0.8, 0.3, 1 });
	gScene->addActor(*plano);

	PxRigidStatic* planoPared1 = gPhysics->createRigidStatic(PxTransform({ -100 , -10, -198 }));
	PxShape* shape1 = CreateShape(PxBoxGeometry(100, 40, 2));
	planoPared1->attachShape(*shape1);
	item = new RenderItem(shape1, planoPared1, { 0.5, 0.8, 0.5, 1 });
	gScene->addActor(*planoPared1);

	PxRigidStatic* planoPared2 = gPhysics->createRigidStatic(PxTransform({ -198 , -10, -100 }));
	PxShape* shape2 = CreateShape(PxBoxGeometry(2, 40, 100));
	planoPared2->attachShape(*shape2);
	item = new RenderItem(shape2, planoPared2, { 0.5, 0.8, 0.5, 1 });
	gScene->addActor(*planoPared2);

	RPFR = new RigidParticleForceRegistry();

	actualCoolDown = 0;
	generationCoolDown = 1;
}


void WorldManager::collisionEfect(PxActor* actor1_, PxActor* actor2_)
{
	PxRigidActor* actor;
	RigidParticle* p1 = nullptr;
	RigidParticle* p2 = nullptr;

	auto i = rigidParticles.begin();
	while ((p1 == nullptr || p2 == nullptr) && i != rigidParticles.end()) {
		actor = (*i)->getPxActor();
		if (actor == actor1_) {
			p1 = (*i);
		}
		if (actor == actor2_) {
			p2 = (*i);
		}
		++i;

	}


}






void WorldManager::update(double t)
{
	auto i = rigidParticles.begin();

	while (i != rigidParticles.end()) {

		(*i)->integrate(t);

		if (!(*i)->isAlive()) {
			RPFR->deleteParticleRegistry(*i);
			delete (*i);
			i = rigidParticles.erase(i);
		}

		else {
			++i;
		}
	}


	RPFR->updateForces(t);

	actualCoolDown += t;
	if (actualCoolDown >= generationCoolDown) {
		for (auto j : rigidParticleGen) {

			std::list<RigidParticle*> aux = j->generateParticles(gPhysics,gScene);

			for (auto i : aux) {
				rigidParticles.push_back(i);
			}

		}

		actualCoolDown = 0;
	}

	if (explosion != nullptr) explosion->addConst(t);
}


void WorldManager::deleteGenerators()
{
	auto i = rigidParticleGen.begin();

	while (i != rigidParticleGen.end()) {
		i = rigidParticleGen.erase(i);
	}
}

void WorldManager::addRigidGaussianGenerator()
{

	PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	RigidGaussianParticleGenerator* rgpg = new RigidGaussianParticleGenerator(CreateShape(PxBoxGeometry(1, 1, 3), gMaterial), 20, 0.8, 1, 5,{10,0.1,10});
	rgpg->setMeanPos({ -100,-30,-100 }, { 0,0,0 });
	rigidParticleGen.push_back(rgpg);

}

void WorldManager::addExplosion()
{
	explosion = new RigidExplosionGenerator(100000, 400, 200, { -100, 0, -100 });

	for (auto i : rigidParticles) {
		RPFR->addRegistry(explosion, i);
	}
}

void WorldManager::noExplosion()
{
	for (auto i : rigidParticles) {
		RPFR->deleteParticleRegistry(i);
	}
}

WorldManager::~WorldManager()
{
	auto i = rigidParticles.begin();

	while (i != rigidParticles.end()) { 
		i = rigidParticles.erase(i);
	}
}