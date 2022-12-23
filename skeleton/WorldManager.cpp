#include "WorldManager.h"
WorldManager::WorldManager(PxScene* gScene_, PxPhysics* gPhysics_) {

	gScene = gScene_;
	gPhysics = gPhysics_;

	PxRigidStatic* plano = gPhysics->createRigidStatic(PxTransform({ 50,40,-30 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.3, 200));
	plano->attachShape(*shape);
	plano->setName("Static");
	item = new RenderItem(shape, plano, { 0.3, 0.8, 0.3, 1 });
	gScene->addActor(*plano);

	PxRigidStatic* planoPared1 = gPhysics->createRigidStatic(PxTransform({ 50 , 80, -230 }));
	PxShape* shape1 = CreateShape(PxBoxGeometry(200, 40, 2));
	planoPared1->attachShape(*shape1);
	planoPared1->setName("Static");
	item = new RenderItem(shape1, planoPared1, { 0.5, 0.8, 0.5, 1 });
	gScene->addActor(*planoPared1);

	PxRigidStatic* planoPared2 = gPhysics->createRigidStatic(PxTransform({ 150 , 80, -30 }));
	PxShape* shape2 = CreateShape(PxBoxGeometry(2, 40, 200));
	planoPared2->attachShape(*shape2);
	planoPared2->setName("Static");
	item = new RenderItem(shape2, planoPared2, { 0.5, 0.8, 0.5, 1 });
	gScene->addActor(*planoPared2);


	PxRigidStatic* planoPared3 = gPhysics->createRigidStatic(PxTransform({ -50 , 80, -30 }));
	PxShape* shape3 = CreateShape(PxBoxGeometry(2, 40, 200));
	planoPared3->attachShape(*shape3);
	planoPared3->setName("Static");
	item = new RenderItem(shape3, planoPared3, { 0.5, 0.8, 0.5, 1 });
	gScene->addActor(*planoPared3);


	PxRigidStatic* techo = gPhysics->createRigidStatic(PxTransform({ 50,120,-30 }));
	PxShape* shape4 = CreateShape(PxBoxGeometry(100, 0.3, 200));
	techo->attachShape(*shape4);
	techo->setName("Static");
	item = new RenderItem(shape4, techo, { 0.3, 0.8, 0.3, 1 });
	gScene->addActor(*techo);

	RPFR = new RigidParticleForceRegistry();


	enemigosTipo1 = 20;
	enemigosTipo2 = 30;
	enemigosTipo3 = 40;

	enemigosActuales = 0;

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
			RPFR->deleteParticleRegistry(*i);
			delete (*i);
			i = rigidParticles.erase(i);
		}
		else if (actor == actor2_) {
			if ((*i)->getPxRigidDynamic()->getName() != "Static") {
				RPFR->deleteParticleRegistry(*i);
				delete (*i);
				i = rigidParticles.erase(i);
			}
		}
		else ++i;

	}

}






void WorldManager::update(double t)
{
	auto i = rigidParticles.begin();

	while (i != rigidParticles.end() && rigidParticles.size()>0) {

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
	if (actualCoolDown >= generationCoolDown && enemigosActuales>0) {
		for (auto j : rigidParticleGen) {

			std::list<RigidParticle*> aux = j->generateParticles(gPhysics,gScene);

			for (auto i : aux) {
				if (j->getForceGenerator() != nullptr) RPFR->addRegistry(j->getForceGenerator(), i);
				rigidParticles.push_back(i);
			}

			enemigosActuales -= aux.size();
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
	RigidGaussianParticleGenerator* rgpg = new RigidGaussianParticleGenerator(CreateShape(PxBoxGeometry(1, 1, 3), gMaterial), 1, 0.8, 1, 5,{45,0.1,45});
	rgpg->setMeanPos({ 50,50,0 }, { 0,0,0 });
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

void WorldManager::shoot()
{
	PxRigidDynamic* new_solid;
	new_solid = gPhysics->createRigidDynamic(PxTransform(GetCamera()->getTransform()));
	PxShape* s = CreateShape(PxSphereGeometry(bulletSize));
	new_solid->attachShape(*s);
	new_solid->setLinearVelocity(GetCamera()->getDir()*bulletSpeed);
	new_solid->setAngularVelocity({ 0,0,0 });
	PxRigidBodyExt::setMassAndUpdateInertia(*new_solid, 200);
	RenderItem* renderItem = new RenderItem(s, new_solid, { 0.7, 0.1, 0.3, 1 });
	RigidParticle* rp = new RigidParticle(new_solid, 100, renderItem, 0.5);

	gScene->addActor(*new_solid);

	RPFR->addRegistry(new RigidGravityForceGenerator({ 0,-2,0 }), rp);
	rigidParticles.push_back(rp);
}

WorldManager::~WorldManager()
{
	auto i = rigidParticles.begin();

	while (i != rigidParticles.end()) { 
		i = rigidParticles.erase(i);
	}
}