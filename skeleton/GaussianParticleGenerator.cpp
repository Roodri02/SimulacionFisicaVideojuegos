#include "GaussianParticleGenerator.h"
#include "Firework.h"
GaussianParticleGenerator::GaussianParticleGenerator(string name_,Vector3 std_dev_pos_, Vector3 std_dev_vel_, double std_dev_t_,
	double _mean_t_, int num_particles_, double generation_probability_,Particle* base_p_)
{
	name = name_;
	std_dev_pos = std_dev_pos_;
	std_dev_vel = std_dev_vel_;
	std_dev_t = std_dev_t_;
	num_particles = num_particles_;
	generation_probability = generation_probability_;
	mean_t = _mean_t_;
	model = base_p_;
	mean_Vel_ = Vector3(0, 0, 0);

	std::random_device rd{};
	 gen = mt19937{rd()};


	distr = std::uniform_real_distribution<double>(0, 1);
}

GaussianParticleGenerator::GaussianParticleGenerator(string name, Vector3 std_dev_pos_, Vector3 std_dev_vel_, Vector3 mean_pos_, Vector3 mean_vel_, double std_dev_t_, double _mean_t_, int num_particles_, double generation_probability_, Particle* p)
{
	name = name;
	std_dev_pos = std_dev_pos_;
	std_dev_vel = std_dev_vel_;
	std_dev_t = std_dev_t_;
	num_particles = num_particles_;
	generation_probability = generation_probability_;
	mean_t = _mean_t_;
	model = p;
	mean_Pos_ = mean_pos_;
	mean_Vel_ = mean_vel_;

	std::random_device rd{};
	gen = mt19937{ rd() };


	distr = std::uniform_real_distribution<double>(0, 1);
}

GaussianParticleGenerator::~GaussianParticleGenerator()
{
}

list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> particles;


	px = normal_distribution<>{ mean_Pos_.x, std_dev_pos.x };
	py = normal_distribution<>{ mean_Pos_.y, std_dev_pos.y };
	pz = normal_distribution<>{ mean_Pos_.z, std_dev_pos.z };

	vx = normal_distribution<>{ mean_Vel_.x, std_dev_vel.x };
	vy = normal_distribution<>{ mean_Vel_.y, std_dev_vel.y };
	vz = normal_distribution<>{ mean_Vel_.z, std_dev_vel.z };


	tiempoVida = normal_distribution<>(mean_t, std_dev_t);
	for (int i = 0; i < num_particles; i++) {

		double probability = distr(gen);
		if (probability < generation_probability) {

			Vector3 pPos = { float(px(gen)),float(py(gen)),float(pz(gen)) };
			Vector3 vVel = { float(vx(gen)),float(vy(gen)),float(vz(gen)) };

			double time = tiempoVida(gen);


			if (Firework* fw = dynamic_cast<Firework*>(model)) {
				ParticleVariables m = model->getVariables();

				Firework* f = new Firework();
				f->setFirework(m.pose.p, m.vel, m.lifeTime, m.damping, m.tamano, m.ace, m.color, fw->getListGens());
				f->setPosAndVel(pPos, vVel);
				f->setTime(time);
				particles.push_back(f);
			}
			else {
				Particle* particleNew = model->clone();
				particleNew->setPosAndVel(pPos, vVel);
				particleNew->setTime(time);
				particles.push_back(particleNew);
			}


		}

	}

	return particles;
}
