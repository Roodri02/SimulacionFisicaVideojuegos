#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(string name_,Vector3 std_dev_pos_, Vector3 std_dev_vel_, double std_dev_t_,
	double _mean_t_, int num_particles_, double generation_probability_,Particle* base_p_)
{
	name = name_;
	std_dev_pos = std_dev_pos_;
	std_dev_vel = std_dev_vel_;
	std_dev_t = std_dev_t_;
	num_particles = num_particles_;
	generation_probability = generation_probability_;

	Vector3 mean_pos = base_p_->getMeanPos();
	Vector3 mean_vel = base_p_->getMeanVel();

	model = base_p_;

	std::random_device rd{};
	 gen = mt19937{rd()};

	px =  normal_distribution<>{ mean_pos.x, std_dev_pos.x };
	py =  normal_distribution<>{ mean_pos.y, std_dev_pos.y };
	pz =  normal_distribution<>{ mean_pos.z, std_dev_pos.z };

	vx = normal_distribution<>{ mean_vel.x, std_dev_vel.x };
	vy = normal_distribution<>{ mean_vel.y, std_dev_vel.y };
	vz = normal_distribution<>{ mean_vel.z, std_dev_vel.z };

	distr = std::uniform_real_distribution<double>(0, 1);
	tiempoVida = normal_distribution<>(mean_t, std_dev_t);
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

			Particle* particleNew = model->clone();

			Vector3 pPos = { float(px(gen)),float(py(gen)),float(pz(gen)) };
			Vector3 vVel = { float(vx(gen)),float(vy(gen)),float(vz(gen)) };

			double time = tiempoVida(gen);

			particles.push_back(particleNew);


		}

	}

	return particles;
}
