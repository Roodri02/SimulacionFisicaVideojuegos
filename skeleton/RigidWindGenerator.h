#pragma once
#include "RigidForceGenerator.h"

class RigidWindGenerator : public RigidForceGenerator
{
private:
    float _k1 = 0;
    float _k2 = 0;
    Vector3 windVel;

    double const cD = 0.5;
    double const pi = 3.1415926535;
    double const airDensity = 1.20;

public:
    RigidWindGenerator(const float k1, const float k2, Vector3 windVel_) {};

    virtual void updateForce(RigidParticle* p, double t);
    inline void setKS(float k1_, float k2_) { _k1 = k1_;  _k2 = k2_; };
    inline float getK1() { return _k1; };
    inline float getK2() { return _k2; };
};

