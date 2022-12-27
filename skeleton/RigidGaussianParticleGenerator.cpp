#include "RigidGaussianParticleGenerator.h"



RigidGaussianParticleGenerator::RigidGaussianParticleGenerator(PxShape* shape_, int num_particles_,double generation_probability_, 
	double std_dev_t_, double _mean_t_,PxVec3 std_dev_pos_, PxVec3 std_dev_vel_, typeForce1 type)
{
	shape = shape_;
	std_dev_t = std_dev_t_;
	generation_probability = generation_probability_;
	num_particles = num_particles_;
	mean_t = _mean_t_;
	mean_Vel_ = { 0,0,0 };
	std_dev_pos = std_dev_pos_;
	std_dev_vel = std_dev_vel_;
	typeForce_ = type;

	setForceGenerator({ 0,-9.8,0 });
}

std::list<RigidParticle*> RigidGaussianParticleGenerator::generateParticles(PxPhysics* gPhysics, PxScene* gScene_)
{
	std::uniform_real_distribution<double> distr(0, 1);
	std::uniform_real_distribution<double> d(1, 300);
	std::normal_distribution<> tiempoVida(mean_t, std_dev_t);

	std::normal_distribution<> px = normal_distribution<double>{ mean_Pos_.x, std_dev_pos.x };
	std::normal_distribution<> py = normal_distribution<double>{ mean_Pos_.y, std_dev_pos.y };
	std::normal_distribution<> pz = normal_distribution<double>{ mean_Pos_.z, std_dev_pos.z };


	std::normal_distribution<> vx = normal_distribution<double>{ mean_Vel_.x, std_dev_vel.x };
	std::normal_distribution<> vy = normal_distribution<double>{ mean_Vel_.y, std_dev_vel.y };
	std::normal_distribution<> vz = normal_distribution<double>{ mean_Vel_.z, std_dev_vel.z };


	std::list<RigidParticle*> listRigidParticles;

	for (int i = 0; i < num_particles; i++) {
		if (distr(gen) < generation_probability) {

			PxRigidDynamic* new_solid;
			new_solid = gPhysics->createRigidDynamic(PxTransform(float(px(gen)), float(py(gen)), float(pz(gen))));
			new_solid->attachShape(*shape);
			new_solid->setLinearVelocity(PxVec3(float(vx(gen)), float(vy(gen)), float(vz(gen))));
			new_solid->setAngularVelocity({ 0,0,0 });
			PxRigidBodyExt::setMassAndUpdateInertia(*new_solid, d(gen));
			renderItem = new RenderItem(shape, new_solid, { 0.7, 0.1, 0.3, 1 });
			RigidParticle* rp = new RigidParticle(new_solid, tiempoVida(gen), renderItem,5);

			gScene_->addActor(*new_solid);
			listRigidParticles.push_back(rp);
		}
		else {
			PxRigidDynamic* new_solid;
			new_solid = gPhysics->createRigidDynamic(PxTransform(float(px(gen)), float(py(gen)), float(pz(gen))));
			new_solid->attachShape(*shape);
			new_solid->setLinearVelocity(mean_Vel_);
			new_solid->setAngularVelocity({ 0,0,0 });
			PxRigidBodyExt::setMassAndUpdateInertia(*new_solid, d(gen));
			renderItem = new RenderItem(shape, new_solid, { 1, 0.3, 0.7, 1 });
			RigidParticle* rp = new RigidParticle(new_solid, 10, renderItem, 10,Bomba);

			gScene_->addActor(*new_solid);
			listRigidParticles.push_back(rp);
		}
	}

	return listRigidParticles;
}
