#include "Proyectil.h"


Proyectil::Proyectil(TipoBala tipoBala_) 
{
	switch (tipoBala_)
	{
	case PISTOL: {
		setParticle(200, 0.99, GetCamera()->getDir() * 1500, GetCamera()->getEye(), { 0,-9.8,0 });
		break;
	}
	case ARTILLERY:
		setParticle(400, 0.6, GetCamera()->getDir() * 700, GetCamera()->getEye(), { 0,-9.8,0 });
		break;
	case FIREBALL:
		setParticle(1000, 0.5, GetCamera()->getDir() * 500, GetCamera()->getEye(), { 0,-9.8,0 });
		break;
	case LASER:
		setParticle(1760, 0.3, GetCamera()->getDir() * 400, GetCamera()->getEye(), { 0,-9.8,0 });
		break;
	default:
		break;
	}
}
