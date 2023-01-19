#include "PartycleSystem.h"
#include <iostream>

PartycleSystem::PartycleSystem()
{
	addFuente();
	createFireworks();
	PFR =  new ParticleForceRegistry();

	float x = -20;
	for (int i = 0; i < 8; i++) {
		generateAnchoredDemo({ x,320,-200 });
		x += 20;
	}
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

		if (g->isActive()) {
			aux = g->generateParticles();
			for (auto p : aux) {
				if (g->getForceGenerator() != nullptr)PFR->addRegistry(g->getForceGenerator(), p);
				_particles.push_back(p);
			}
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

	//gen = new UniformParticleGenerator("g",10,0.98, Vector3(10, 10, 10), Vector3(3, 3, 3),p,type);
	//gen->setMeanPos(Vector3(15, 30, 0), { 0,0,0 });
	//_particlesGenerators.push_back(gen);
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

void PartycleSystem::createFireworks()
{
	Particle* base_p = new Particle();
	base_p->setParticle(5, 0.555, 0.4, { 0,0,1 }, { 0,0,0 }, { 0,-3,0 }, { 0.4,1,0.4,1 },0.3, { 0,0,0 }, { 0,0,0 },
		false,false,CreateShape(physx::PxSphereGeometry(1)));

	std::shared_ptr<ParticleGenerator> gen1(new GaussianParticleGenerator("g", { 0.1,0.1,0.1 }, { 2,0.1,2 }, 0.3, 0.6, 1, 0.95, base_p,Nada));
	fireworks_pool.push_back(new Firework({ 0,0,0 }, {0,30,0},0.7, 0.999,1, {0,0,0},{0.3,1,0.2,1}, {gen1}));

	std::shared_ptr<ParticleGenerator> gen2(new GaussianParticleGenerator("g1", { 0.1,0.1,0.1 }, { 5,5,5 }, 0.1, 2, 1, 0.95, fireworks_pool[0],Nada));
	fireworks_pool.push_back(new Firework({ 0,0,0 }, { 0,30,0 }, 1.3, 0.999, 1, { 0,0,0 }, { 1,1,1,1 }, { gen2 }));

	fireworkGenerator1 = new UniformParticleGenerator("f1", 1, 0.7, {3,0.1,3 }, { 0.1,0.1,0.1 },{70,55,-200 }, {0,10,0}, fireworks_pool[1],
		Nada,0.3,0.0,-10,{0,0,0},{0,0,0},{0,0,0},false);

	fireworkGenerator2 = new UniformParticleGenerator("f2", 1, 0.7, { 3,0.1,3 }, { 0.1,0.1,0.1 }, { 30,55,-200 }, { 0,10,0 }, fireworks_pool[1],
		Nada, 0.3, 0.0, -10, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, false);
	_particlesGenerators.push_back(fireworkGenerator1);
	_particlesGenerators.push_back(fireworkGenerator2);


	Particle* base_fireWork1 = new Particle();
	base_fireWork1->setParticle(5, 0.555, 0.2, { 0,0,0 }, { 30,45,-200 }, { 0,0,0 }, { 0,0,0,1 },0.3, { 0,0,0 }, { 0,0,0 },
		false,true,CreateShape(physx::PxBoxGeometry(5,10,5)));

	Particle* base_fireWork2 = new Particle();
	base_fireWork2->setParticle(5, 0.555, 0.2, { 0,0,0 }, { 70,45,-200 }, { 0,0,0 }, { 0,0,0,1 }, 0.3, { 0,0,0 }, { 0,0,0 },
		false, true, CreateShape(physx::PxBoxGeometry(5, 10, 5)));
}

void PartycleSystem::activaFireworks()
{
	fireworkGenerator1->setActive(true);
	fireworkGenerator2->setActive(true);
}

void PartycleSystem::desactivaFirework()
{
	fireworkGenerator1->setActive(false);
	fireworkGenerator2->setActive(false);
}

void PartycleSystem::generateAnchoredDemo(Vector3 pos)
{
	Particle* p3 = new Particle();
	p3->setParticle(2.0, 0.85, 50, { 0,0,0 }, {pos.x,pos.y-20,pos.z}, {0,-1.5,0}, {0.35,0.1,0.8,1}, 3, {0,0,0}, {0,0,0}, false, true,
		CreateShape(physx::PxSphereGeometry(3)));
	AnchoredSpringFG* f3 = new AnchoredSpringFG(40, 10, pos);
	PFR->addRegistry(f3, p3);
	_particles.push_back(p3);
}

void PartycleSystem::explodeEnemy(Vector3 pos)
{
	Particle* base_p = new Particle();
	base_p->setParticle(5, 0.555, 0.4, { 0,0,1 }, pos, { 0,0,0 }, { 0.4,0.4,0.8,1 }, 0.3, { 0,0,0 }, { 0,0,0 },
		false, false, CreateShape(physx::PxSphereGeometry(1)));
	std::shared_ptr<ParticleGenerator> explode(new GaussianParticleGenerator("explodeEnemy",{5,5,5},{10,10,10},pos,{0,0,0}, 0.3, 1.3, 60, 0.9, base_p, GravityForce));

	list<Particle*> aux;
	aux = explode->generateParticles();
	for (auto p : aux) {
		if (explode->getForceGenerator() != nullptr)PFR->addRegistry(explode->getForceGenerator(), p);
		_particles.push_back(p);
	}
}

void PartycleSystem::addFuente()
{

	Particle* base_p = new Particle();
	base_p->setParticle(5, 0.999, 4.7, { 0,0,0 }, { 0,0,0 }, { 0,9.8,0 }, { 0.0,0,0.0,1 }, 0.6, { 0,0,0 }, { 0,0,0 },
		false, false,CreateShape(physx::PxSphereGeometry(3)));
	CircleGenerator* c = new CircleGenerator({ 130,40,-200 }, 3, 3, 0.9, base_p,0,WhirlwindForce,0.5,0.0,-10,{0,0,0},{0,0,0},{130,100,-200});
	_particlesGenerators.push_back(c);


	Particle* base_p1 = new Particle();
	base_p1->setParticle(5, 0.999, 4.7, { 0,0,0 }, { 0,0,0 }, { 0,9.8,0 }, { 0.0,0,0.0,1 }, 0.6, { 0,0,0 }, { 0,0,0 },
		false, false, CreateShape(physx::PxSphereGeometry(3)));
	CircleGenerator* c1 = new CircleGenerator({ -30,40,-200 }, 3, 3, 0.9, base_p1, 0, WhirlwindForce, 0.5, 0.0, -10, { 0,0,0 }, { 0,0,0 }, { -30,100,-200 });
	_particlesGenerators.push_back(c1);
}



