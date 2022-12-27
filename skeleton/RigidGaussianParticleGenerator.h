#pragma once
#include "RigidParticleGenerator.h"

class RigidGaussianParticleGenerator : public  RigidParticleGenerator
{
public:
	RigidGaussianParticleGenerator(PxShape* shape_, int num_particles_,
		double generation_probability_, double std_dev_t_, double _mean_t_, PxVec3 std_dev_pos_, PxVec3 std_dev_vel_, typeForce1 type = NoForce);
	~RigidGaussianParticleGenerator() {};

	std::list<RigidParticle*> generateParticles(PxPhysics* gPhysics, PxScene* gScene_) override;

	void setMeanPos(Vector3 mean_Pos, Vector3 mean_Vel) {
		mean_Pos_ = mean_Pos;
		if (mean_Vel_ == Vector3(0, 0, 0))mean_Vel_ = mean_Vel;
	};

protected:
	double std_dev_t;

	std::random_device rd{};
	std::mt19937 gen{ rd() };

};

