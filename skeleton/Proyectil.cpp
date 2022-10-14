#include "Proyectil.h"


Proyectil::Proyectil(TipoBala tipoBala_) 
{
	switch (tipoBala_)
	{
	case PISTOL: {
		//setParticle(0.032, 0.99,5, GetCamera()->getDir() * 500, GetCamera()->getEye(), { 0,-9.8,0 },{1,0,0,1},0.3f);
		break;
	}
	case ARTILLERY:
		//setParticle(42.840, 0.99,5, GetCamera()->getDir() * 300, GetCamera()->getEye(), { 0,-9.8,0 }, { 0,1,0,1 },7.0f);
		break;
	case FIREBALL:
		//setParticle(1000, 0.99,5, GetCamera()->getDir() * 50, GetCamera()->getEye(), { 0,-1,0 }, { 1,0,0,1 },3.0f);
		break;
	case SNOWBALL:
		//setParticle(1760, 0.99,5, GetCamera()->getDir() * 75, GetCamera()->getEye(), { 0,-9.8,0 }, { 1,1,0,1 },1.0f);
		break;
	default:
		break;
	}
}
