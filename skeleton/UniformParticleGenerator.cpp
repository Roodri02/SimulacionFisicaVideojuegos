#include "UniformParticleGenerator.h"
#include "Firework.h"
UniformParticleGenerator::UniformParticleGenerator(string name_,int num_particles_, double generation_probability_,
	Vector3 pos_width_, Vector3 vel_widht_, Vector3 mean_pos_, Vector3 mean_vel_,Particle* base_p_, typeForce T, double k1 , double k2, double K , Vector3 gravity
	, Vector3 windVel , Vector3 whirlPos,bool active)
{
	name = name_;
	num_particles = num_particles_;
	generation_probability = generation_probability_;
	pos_width = pos_width_;
	vel_widht = vel_widht_;

	std::random_device rd{};
	gen = mt19937{ rd() };

	model = base_p_;

	typeForce_ = T;
	active_ = active;
	mean_Pos_ = mean_pos_;
	mean_Vel_ = mean_vel_;

	setForceGenerator(gravity, k1, k2, windVel, K, whirlPos);

	px = uniform_real_distribution<>{ mean_Pos_.x - pos_width_.x/2, mean_Pos_.x + pos_width_.x / 2 };
	py = uniform_real_distribution<>{ mean_Pos_.y - pos_width_.y/2, mean_Pos_.y + pos_width_.y / 2 };
	pz = uniform_real_distribution<>{ mean_Pos_.z - pos_width_.z / 2, mean_Pos_.z + pos_width_.z / 2 };

	vx = uniform_real_distribution<>{ mean_Vel_.x - vel_widht_.x / 2, mean_Vel_.x + vel_widht_.x / 2 };
	vy = uniform_real_distribution<>{ mean_Vel_.y - vel_widht_.y/2, mean_Vel_.y + vel_widht_.y / 2 };
	vz = uniform_real_distribution<>{ mean_Vel_.z - vel_widht_.z / 2, mean_Vel_.z + vel_widht_.z / 2 };

}

UniformParticleGenerator::~UniformParticleGenerator()
{
}

list<Particle*> UniformParticleGenerator::generateParticles()
{
	list<Particle*> particles;


	for (int i = 0; i < num_particles; i++) {

		double probability = distr(gen);
		if (probability < generation_probability) {


			if (Firework* fw = dynamic_cast<Firework*>(model)) {
				ParticleVariables m = model->getVariables();

				Firework* f = new Firework();
				f->setFirework(m.pose.p, m.vel, m.lifeTime, m.damping, m.tamano, m.ace, m.color, fw->getListGens());
				f->setPosAndVel({ float(px(gen)), float(py(gen)), float(pz(gen)) }, mean_Vel_);
				f->setTime(1.5);
				particles.push_back(f);
			}
			else {
				Particle* particleNew = model->clone();

				Vector3 pPos = { float(px(gen)),float(py(gen)),float(pz(gen)) };
				particleNew->setPosAndVel(mean_Pos_, mean_Vel_);
				particles.push_back(particleNew);
			}


		}

	}

	return particles;
}