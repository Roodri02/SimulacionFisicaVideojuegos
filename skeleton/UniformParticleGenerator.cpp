#include "UniformParticleGenerator.h"
UniformParticleGenerator::UniformParticleGenerator(string name_,int num_particles_, double generation_probability_,double mean_t_, Vector3 mean_pos_, Vector3 mean_vel_,
	Vector3 pos_width_, Vector3 vel_widht_, Vector4 color, double mass_, double damp_, double tamanio_, Vector3 ace, Vector3 ambientPos_ , Vector3 ambientWidth_,bool dSpace)
{
	name = name_;
	num_particles = num_particles_;
	generation_probability = generation_probability_;
	mean_pos = mean_pos_;
	mean_vel = mean_vel_;
	mean_t = mean_t_;
	color_ = color;
	mass = mass_;
	damp = damp_;
	ace_ = ace;
	tamanio = tamanio_;
	pos_width = pos_width_;
	vel_widht = vel_widht_;
	ambientPos = ambientPos_;
	ambientWidth = ambientWidth_;
	destroySpace = dSpace;

	std::random_device rd{};
	gen = mt19937{ rd() };


	px = uniform_real_distribution<>{ mean_pos.x - pos_width_.x/2, mean_pos.x + pos_width_.x / 2 };
	py = uniform_real_distribution<>{ mean_pos.y - pos_width_.y/2, mean_pos.y + pos_width_.y / 2 };
	pz = uniform_real_distribution<>{ mean_pos.z - pos_width_.z / 2, mean_pos.z + pos_width_.z / 2 };

	vx = uniform_real_distribution<>{ mean_vel.x - vel_widht_.x / 2, mean_vel.x + vel_widht_.x / 2 };
	vy = uniform_real_distribution<>{ mean_vel.y - vel_widht_.y/2, mean_vel.y + vel_widht_.y / 2 };
	vz = uniform_real_distribution<>{ mean_vel.z - vel_widht_.z / 2, mean_vel.z + vel_widht_.z / 2 };

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
			Particle* particleNew = new Particle();

			Vector3 pPos = { float(px(gen)),float(py(gen)),float(pz(gen))};
			Vector3 vVel = { float(vx(gen)),float(vy(gen)),float(vz(gen)) };


			particleNew->setParticle(mass, damp, mean_t, vVel, pPos, ace_, color_, tamanio,ambientPos,ambientWidth,destroySpace);

			particles.push_back(particleNew);


		}

	}

	return particles;
}