#pragma once

#include "Particle.h"
#include "ParticleGenerator.h"

class Firework : public Particle
{

public:
	Firework(ParticleVariables p_,
		std::list<std::shared_ptr<ParticleGenerator>> gen);
	Firework(Vector3 pos_, Vector3 vel_, double lifeTime_, double damping_, double tamano_, Vector3 ace_, Vector4 color_,
		std::list<std::shared_ptr<ParticleGenerator>> gens_);
	Firework(){ }
	~Firework();


	void setFirework(ParticleVariables p_, std::list<std::shared_ptr<ParticleGenerator>> gen);
	void setFirework(Firework* base_f);
	void setFireworkBase(Firework* base_f);
	void setFirework(Vector3 pos_, Vector3 vel_, double lifeTime_,double damping_,double tamano_, Vector3 ace_, Vector4 color_,
		std::list<std::shared_ptr<ParticleGenerator>> gens_);

	std::list<std::shared_ptr<ParticleGenerator>> getListGens() {
		return gens;
	}


	std::list<Particle*> Explode();

	void renderFirework() {
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(p.tamano)), &p.pose, p.color);
	};

private :
	std::list<std::shared_ptr<ParticleGenerator>> gens;
};

