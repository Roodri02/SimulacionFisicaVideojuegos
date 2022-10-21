#include "Firework.h"

Firework::Firework()
{
}

int Firework::update(double t)
{
    return 0;
}

std::list<Particle*> Firework::Explode()
{
    std::list<Particle*> aux;

    for (auto i : gens) {
        (*i)->generateParticles();
    }


    return std::list<Particle*>();
}
