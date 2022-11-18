#include "ForceGenerator.h";
#include "core.hpp"
class ParticleDragGenerator : public ForceGenerator
{
public:

	ParticleDragGenerator() {};
	ParticleDragGenerator(const float k1, const float k2) :_k1(k1), _k2(k2) {};
	virtual void updateForce(Particle* p, double t);

protected:
	float _k1;
	float _k2;

};