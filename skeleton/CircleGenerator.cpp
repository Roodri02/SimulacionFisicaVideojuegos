#include "CircleGenerator.h"
#include "Firework.h"

CircleGenerator::CircleGenerator(Vector3 mean_pos , double numParticles_, double radio_, double generation_probability_, Particle* p,int tipo)
{
	model = p;
	num_particles = numParticles_;
	radio = radio_;
	generation_probability = generation_probability_;
	tipo_ = tipo;
	mean_Pos_ = mean_pos;
}

CircleGenerator::~CircleGenerator()
{
}

list<Particle*> CircleGenerator::generateParticles()
{
	list<Particle*> particles;

	distr = std::uniform_real_distribution<double>(0, 1);
	for (int i = 0; i < num_particles; i++) {

		double probability = distr(gen);
		if (probability < generation_probability) {

			Vector3 vVel;

			switch (tipo_)
			{
			case 0 :{
				vVel = { float(physx::PxCos(angle) * radio),0,float(physx::PxSin(angle) * radio) };
				break;
			}
			case 1: {
				vVel = { float(physx::PxCos(angle) * radio),20,float(physx::PxSin(angle) * radio) };
				break;
			}

			default:
				break;
			}

			if (Firework* fw = dynamic_cast<Firework*>(model)) {
				Firework* f = new Firework();
				f->setFirework(fw);
				f->setPosAndVel(mean_Pos_, vVel); 
				particles.push_back(f);
			}
			else {
				Particle* particleNew = model->clone();
				particleNew->setPosAndVel(mean_Pos_, vVel);
				particles.push_back(particleNew);
			}

			angle += 360 / num_particles;
		}

	}

	return particles;
}
