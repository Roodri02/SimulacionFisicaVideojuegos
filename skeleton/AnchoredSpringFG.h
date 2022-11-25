#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringFG : public SpringForceGenerator
{
	AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos);
	~AnchoredSpringFG();
};

