#include "Proyectil.h"

Proyectil::Proyectil(TipoBala tipoBala_)
{

	if (tipoBala_ == PISTOL) {
		setPosition({0,0,0});
		setVelocity({0,50,0});
		setAceleration({0,-9.8,0});
		setDamping(0.999);
		setMass(1760);
	}
		
}
