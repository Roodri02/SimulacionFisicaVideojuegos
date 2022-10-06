#include "Diana.h"

Diana::Diana()
{
	setParticle(1000, 0, 0, GetCamera()->getDir(), {-100,0,-100}, { 0,-9.8,0 }, { 0,0,1,1 },6);
}

Diana::~Diana()
{
}

void Diana::integrate()
{
}
