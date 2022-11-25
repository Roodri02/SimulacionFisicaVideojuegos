#include "PartycleSystem.h"
#include <iostream>

PartycleSystem::PartycleSystem()
{

	/*UniformParticleGenerator* g = new UniformParticleGenerator("xd", 4, 0.9,15, { 0,10, 0 }, { 0 , 0, 0 },{10,10,10},{4,4,4}, {0.4,0.8,.4,1}, 4, 0.555, 0.2, {0,0,0},{0,10,0},{10,10,10}, false);
	_particlesGenerators.push_back(g);*/


	/*Particle* base_p = new Particle();
	base_p->setParticle(5, 0.555, 0.05, { 0,0,1 }, { 0,0,0 }, { 0,-3,0 }, { 0,1,0,1 }, 0.3, { 20,20,0 }, { 0,0,0 }, false, false);
	GaussianParticleGenerator* g = new GaussianParticleGenerator("xd", { 0.2, .2, .2 }, { 20,20,20 },{0,0,0},{0,30,0}, .1, 10, 20, 0.9, base_p);
	_particlesGenerators.push_back(g);*/
	 
	//GaussianParticleGenerator* g = new GaussianParticleGenerator("fuente",{ 0.2, .2, .2 }, {.2,.1,0.1}, 2, 5, 1, 0.9, { 25,50,0}, {5,10,0},{0,0,1,1});
	//_particlesGenerators.push_back(g);

	//GaussianParticleGenerator* x = new GaussianParticleGenerator("fuente2", { 0.2, .2, .2 }, { .2,.1,0.1 }, 2, 5, 1, 0.9, { 25,50,0 }, { -5,10,0 },{1,0,0,1},4,0.555,0.2,{0,-9.8,0});
	//_particlesGenerators.push_back(x);

	//g = new GaussianParticleGenerator("fuente3", { 0.2, .2, .2 }, { .2,.1,0.1 }, 2, 5, 1, 0.9, { 25,50,0 }, { 0,10,-5 }, { 0,1,0,1 });
	//_particlesGenerators.push_back(g);

	//g = new GaussianParticleGenerator("fuente4", { 0.2, .2, .2 }, { .2,.1,0.1 }, 2, 5, 1, 0.9, { 25,50,0 }, { 0,10,5 }, { 1,1,0,1 });
	//_particlesGenerators.push_back(g);

	PFR =  new ParticleForceRegistry();
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
		aux = g->generateParticles();
		for (auto p : aux) {
			PFR->addRegistry(g->getForceGenerator(), p);
			_particles.push_back(p);
		}
	}






}

ParticleGenerator* PartycleSystem::getParticleGenerator(string name)
{
	return nullptr;
}

void PartycleSystem::shootFirework(int type)
{
	Firework* f = new Firework();
	f->setFirework(fireworks_pool[type]);
	_particles.push_back(f);
}

void PartycleSystem::OnParticleDeath(Particle* p)
{
}

void PartycleSystem::generateFireworkSystem()
{

	Particle* base_p = new Particle();
	base_p->setParticle(5, 0.555, 0.2, { 0,0,1 }, { 0,0,0 }, { 0,-3,0 }, { 0,1,0,1 },0.3, { 0,0,0 }, { 0,0,0 }, false,false);

	std::shared_ptr<ParticleGenerator> gen1(new GaussianParticleGenerator("gen1", { 0.1,0.1,0.1 }, { 5,5,5 }, 0.3, 0.6, 60, 0.95, base_p));
	fireworks_pool.push_back(new Firework({ 0,0,0 }, {0,30,0},0.2, 0.999,1, {0,-9.8,0},{1,0,0,1}, {gen1}));

	std::shared_ptr<ParticleGenerator> gen2(new GaussianParticleGenerator("gen2", { 0.1,0.1,0.1 }, { 5,5,5 }, 0.1, 2, 60, 0.95, fireworks_pool[0]));
	fireworks_pool.push_back(new Firework({ 0,0,0 }, { 0,30,0 }, 2, 0.999, 1, { 0,-9.8,0 }, { 0,0,1,1 }, { gen2 }));

	std::shared_ptr<ParticleGenerator> gen3(new GaussianParticleGenerator("gen3", { 0.1,0.1,0.1 }, { 15,15,15 }, 0.1, 2, 3, 0.95, fireworks_pool[1]));
	fireworks_pool.push_back(new Firework({ 0,0,0 }, { 0,30,0 }, 2, 0.999, 1, { 0,-9.8,0 }, { 0,0,1,1 }, { gen3 }));


	Particle* base_p_1 = new Particle();
	base_p_1->setParticle(5, 0.888, 10, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,1,0,1 }, 0.3, { 0,0,0 }, { 0,0,0 }, false, false);

	std::shared_ptr<ParticleGenerator> gen4(new GaussianParticleGenerator("gen4", {0.2,0.2,0.2 }, { 0.05, 0.05, 0.05 }, { 0,0,0 }, { 0,15,0 }, 1, 7, 2, 0.95, base_p_1));
	fireworks_pool.push_back(new Firework({ 0,0,0 }, { 0,30,0 }, 5, 0.999, 1, { 0,-9.8,0 }, { 1,0,0,1 }, { gen4 }));


	Particle* base_p_2 = new Particle();
	base_p_2->setParticle(5, 0.888, 5, { 0,0,1 }, { 0,0,0 }, { 0,-9.8,0 }, { 0,1,1,1 }, 0.4, { 0,0,0 }, { 0,0,0 }, false, false);
	shared_ptr<ParticleGenerator> genCirc1 (new CircleGenerator({ 0,0,0 }, 60, 20, 0.9, base_p_2, 1));
	fireworks_pool.push_back(new Firework({ 0,0,0 }, { 0,45,0 }, 4, 0.999, 1, { 0,-9.8,0 }, { 1,1,0,1 }, { genCirc1 }));


	shared_ptr<ParticleGenerator> genCirc2(new CircleGenerator({ 0,0,0 }, 60, 20, 0.9, fireworks_pool[4], 1));
	fireworks_pool.push_back(new Firework({ 0,0,0 }, { 0,45,0 }, 4, 0.999, 1, { 0,-9.8,0 }, { 1,1,0,1 }, { genCirc2 }));

}

void PartycleSystem::anadeParticulasFirework(std::list<Particle*> pA)
{
	for (auto i : pA)
		_particles.push_back(i);

}

void PartycleSystem::addForceGenerator(Particle* p, ForceGenerator* fg)
{
	PFR->addRegistry(fg, p);
}

void PartycleSystem::addFuente()
{

	Particle* base_p = new Particle();
	base_p->setParticle(5, 0.999, 2, { 0,0,0 }, { 0,0,0 }, { 0,9.8,0 }, { 0.7,.1,0.3,1 }, 0.6, { 0,0,0 }, { 0,0,0 }, false, false);
	CircleGenerator* c = new CircleGenerator({ 0,0,0 }, 20, 10, 0.9, base_p, 0);
	_particlesGenerators.push_back(c);
	Particle* base_p_1 = new Particle();
	base_p_1->setParticle(5, 0.999, 2, { 0,0,0 }, { 0,0,0 }, { 0,-9.8,0 }, { 0.7,.1,0.3,1 }, 0.6, { 0,0,0 }, { 0,0,0 }, false, false);
	CircleGenerator* c1 = new CircleGenerator({ 0,0,0 }, 20, 10, 0.9, base_p_1, 0);
	_particlesGenerators.push_back(c1);
	Particle* base_p_2 = new Particle();
	base_p_2->setParticle(5, 0.999, 2, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0.4,.1,0.3,1 }, 0.6, { 0,0,0 }, { 0,0,0 }, false, false);
	CircleGenerator* c2 = new CircleGenerator({ 0,0,0 }, 20, 10, 0.9, base_p_2, 0);
	_particlesGenerators.push_back(c2);

}


void PartycleSystem::addFuente2()
{

	Particle* base_p = new Particle();
	base_p->setParticle(5, 0.999, 2, { 0,0,0 }, { 0,0,0 }, { 0,-9.8,0 }, { 0.7,.1,0.3,1 }, 0.6, { 0,0,0 }, { 0,0,0 }, false, false);
	CircleGenerator* c = new CircleGenerator({ 0,0,0 }, 20, 10, 0.9, base_p, 1);
	_particlesGenerators.push_back(c);

}

void PartycleSystem::addNiebla()
{
	Particle* base_p = new Particle();
	base_p->setParticle(5, 0.555, 0.05, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0.7,.1,0.3,1 }, 0.3, { 0,0,0 }, { 5,5,5 }, true, false);
	GaussianParticleGenerator* g = new GaussianParticleGenerator("xd", { 10, 10, 10 }, { 2,2,2 },{0,0,0},{0,0,0}, 2, 8, 10, 0.9, base_p);
	_particlesGenerators.push_back(g);


}

void PartycleSystem::addExplosion()
{
	Particle* base_p = new Particle();
	base_p->setParticle(5, 0.555, 10, { 0,0,1 }, { 0,0,0 }, { 0,-0.5,0 }, { 1,1,1,1 }, 0.3, { 20,20,0 }, { 0,0,0 }, false, false);
	GaussianParticleGenerator* g = new GaussianParticleGenerator("xd", { 0.2, .2, .2 }, { 20,20,20 },{0,0,0},{0,30,0}, .1, 10, 20, 0.9, base_p);
	_particlesGenerators.push_back(g);

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

void PartycleSystem::addParticles(int numParticles)
{
	for (int i = 0; i < numParticles; i++) {
		double masa = 1 + rand() % (200 - 15);
		float x = rand() % 101, z = rand() % 101;;

		vector<int> dir = { -1, 1 };

		int aux1 = rand() % 2;
		int aux2 = rand() % 2;

		Particle* p = new Particle();
		p->setParticle(masa, 0.8, 40, { 0,0,0 }, { dir[aux1]*x,0,dir[aux2]*z }, { 0,0,0 }, { 1,0.3,1,1 }, 0.5, { 0,0,0 }, { 0,0,0 }, false, true);

		_particles.push_back(p);
	}
}

void PartycleSystem::generateSpringDemo()
{
	//Particle* p1 = new Particle({ -10.0,10.0,0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60);
	//Particle* p2 = new Particle({ -10.0,10.0,0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 60);

	//p2->setMasa();

	//SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
	//PFR->addRegistry(f1, p1);
	//SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);
	//PFR->addRegistry(f2, p2);

	//_particlesGenerators.push_back(f1);
	//_particlesGenerators.push_back(f2);
}

void PartycleSystem::addGaussianGenerator(typeForce type)
{
	Particle* p = new Particle();
	ParticleGenerator* gen;

	p->setParticle(10, 0.8, 100, Vector3(0, 0, 0), Vector3(0, 0, 0),
		Vector3(0, 0, 0), { 1,0,1,1 }, 0.5, { 0,0,0 }, { 0,0,0 }, false, false);

	gen = new GaussianParticleGenerator("g", Vector3(0.1, 0.1, 10), Vector3(0.1, 0.1, 0.1),{0,0,0},{0,0,0}, 0.3, 100, 1, 0.8, p,type);
	gen->setMeanPos(Vector3(15, 40, 0) , {0,0,0});
	_particlesGenerators.push_back(gen);
}

void PartycleSystem::addUniformGenerator(typeForce type)
{
	Particle* p = new Particle();
	ParticleGenerator* gen;

	p->setParticle(4, 0.9, 50, Vector3(0, 0, 0), Vector3(0, 0, 0),
		Vector3(0, 0, 0), { 1,1,1,1 }, 0.5, { 0,40,0 }, { 10,10,10 }, false, false);

	gen = new UniformParticleGenerator("g",10,0.98, Vector3(10, 10, 10), Vector3(3, 3, 3),p,type);
	gen->setMeanPos(Vector3(15, 30, 0), { 0,0,0 });
	_particlesGenerators.push_back(gen);
}

void PartycleSystem::addCircleGenerator(typeForce type)
{
	Particle* p = new Particle();
	ParticleGenerator* gen;

	p->setParticle(4, 0.9, 50, Vector3(0, 0, 0), Vector3(0, 0, 0),
		Vector3(0, 0, 0), { 1,1,1,1 }, 0.5, { 0,40,0 }, { 10,10,10 }, false, false);

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
