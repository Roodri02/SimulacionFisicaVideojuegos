#pragma once
#include "Particle.h"


enum TipoBala{ PISTOL, ARTILLERY , FIREBALL , LASER };


class Proyectil : public Particle
{
public:
	Proyectil(TipoBala tipoBala_);
};

