#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos_, Vector3 std_dev_vel_, double std_dev_t_,double _mean_t_, int num_particles_, double generation_probability_, Vector3 mean_pos_, Vector3 mean_vel_)
{

	std_dev_pos = std_dev_pos_;
	std_dev_vel = std_dev_vel_;
	std_dev_t = std_dev_t_;
	num_particles = num_particles_;
	generation_probability = generation_probability_;
	mean_pos = mean_pos_;
	mean_vel = mean_vel_;
	mean_t = _mean_t_;

	std::random_device rd;
	//std::seed_seq seed2{ rd(),rd(),rd(),rd(),rd(),rd(),rd(),rd() };
	gen{rd()};

	normal_distribution<> px{ mean_pos.x, std_dev_pos.x };
	normal_distribution<> py{ mean_pos.y, std_dev_pos.y };
	normal_distribution<> pz{ mean_pos.z, std_dev_pos.z };

	normal_distribution<> vx{ mean_vel.x, std_dev_vel.x };
	normal_distribution<> vy{ mean_vel.y, std_dev_vel.y };
	normal_distribution<> vz{ mean_vel.z, std_dev_vel.z };

	std::uniform_real_distribution<double> distr(0, 1);
}

GaussianParticleGenerator::~GaussianParticleGenerator()
{
}

list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> particles;


	for (int i = 0; i < num_particles; i++) {

		double probability = distr(gen);
		if (probability < generation_probability) {
			Particle* particleNew = new Particle();

			Vector3 pPos = { float(px(gen)),float(py(gen)),float(pz(gen)) };
			Vector3 vVel = { float(vx(gen)),float(vy(gen)),float(vz(gen)) };

			particleNew->setParticle(4, 0.555, 5, vVel, pPos, { 0,-9.8,0 }, { 0,0,1,1 }, 3);

			particles.push_back(particleNew);


		}

	}

	return particles;
}
