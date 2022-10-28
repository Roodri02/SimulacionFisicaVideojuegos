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

	list<Particle*>::iterator it = _particles.begin();

	while (it != _particles.end()) {
		(*it)->integrate(t);
		if (!(*it)->isAlive()) {


			if (Firework* f = dynamic_cast<Firework*>(*it)) {
				list<Particle*> pAux = f->Explode();

				for (auto i : pAux)
					_particles.push_back(i);
			}
			delete* it;
			it = _particles.erase(it);

		}
		else it++;
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

void PartycleSystem::addFuente(int type)
{

	Firework* f = new Firework();
	f->setFireworkBase(fireworks_pool[3]);

	GaussianParticleGenerator* g = new GaussianParticleGenerator("fuente",{0.05,0.1,0.05 }, { 0.1, 0.1, 0.1 },{0,0,0},{0,-3,0}, 0.05, 4, 1, 0.9, f);
	_particlesGenerators.push_back(g);

}

void PartycleSystem::addCircleGenerator(int type)
{


}
