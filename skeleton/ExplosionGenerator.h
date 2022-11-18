#include "ForceGenerator.h";
#include "core.hpp"
class ExplosionGenerator : public ForceGenerator
{
public:

	ExplosionGenerator() {};
	virtual void updateForce(Particle* p, double t);
	void setIntensidad(float i) { intensidad = i; }
	void setTime(float t) { timeCt = t; }
	void setCenter(Vector3 eC) { center = eC; }
	void setRadio(float r) { radio = r; }
	void setAll(float i, float t, Vector3 e, float r)
	{
		intensidad = i;
		timeCt = t;
		center = e;
		radio = r;
	}
protected:
	float _k1, _k2, intensidad, radio;
	float timeCt;
	Vector3 center;
};