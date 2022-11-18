#include "ForceGenerator.h";
#include "core.hpp"
class ParticleDragGenerator : public ForceGenerator
{
public:

	ParticleDragGenerator() {};
	ParticleDragGenerator(const float k1, const float k2) :_k1(k1), _k2(k2) {};
	virtual void updateForce(Particle* p, double t);
	inline void setKS(float k1_, float k2_) { _k1 = k1_;  _k2 = k2_; };
	inline float getK1() { return _k1; };
	inline float getK2() { return _k2; };

protected:
	float _k1;
	float _k2;

};