#include "ForceGenerator.h";
#include "core.hpp"
class ExplosionGenerator : public ForceGenerator
{
public:

	ExplosionGenerator(double K_, double radio_, double explosion_, Vector3 center_) {
		K = K_;
		center = center_;
		radio = radio_;
		explosion = explosion_;
	};

	virtual void updateForce(Particle* p, double t);
	void addConst(double t) {
		explosion += t;
		radio = vE * t * 100;
	}
protected:
	double K, radio, explosion;
	double const e = 2.71828182845904525356;
	double vE = 343.55489;
	Vector3 center;
};