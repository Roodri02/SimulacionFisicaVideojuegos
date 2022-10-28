#include "Firework.h"

using namespace physx;

Firework::Firework(ParticleVariables p_ ,std::list<std::shared_ptr<ParticleGenerator>> gen)
{
    for (auto i : gen)
        gens.push_back(i);

    p = p_;
 
}

Firework::Firework(Vector3 pos, Vector3 vel_, double lifeTime_, double damping_, double tamano_, Vector3 ace_, Vector4 color_, std::list<std::shared_ptr<ParticleGenerator>> gens_)
{
    for (auto i : gens_)
        gens.push_back(i);

    p.pose = PxTransform(pos.x, pos.y, pos.z);
    p.vel = vel_;
    p.lifeTime = lifeTime_;
    p.damping = damping_;
    p.tamano = tamano_;
    p.ace = ace_;
    p.color = color_;

}

Firework::~Firework()
{
    DeregisterRenderItem(renderItem);
}

void Firework::setFirework(ParticleVariables p_, std::list<std::shared_ptr<ParticleGenerator>> gen){
    for (auto i : gen)
        gens.push_back(i);

    p = p_;
    renderItem = new RenderItem(CreateShape(PxSphereGeometry(p.tamano)), &p.pose, p.color);
}


void Firework::setFirework(Firework* base_f)
{
    std::list<std::shared_ptr<ParticleGenerator>> gensAux = base_f->getListGens();
    for (auto i : gensAux)
        gens.push_back(i);

    ParticleVariables aux = base_f->getVariables();
    p = aux;

    renderItem = new RenderItem(CreateShape(PxSphereGeometry(p.tamano)), &p.pose, p.color);
}

void Firework::setFireworkBase(Firework* base_f)
{
    std::list<std::shared_ptr<ParticleGenerator>> gensAux = base_f->getListGens();
    for (auto i : gensAux)
        gens.push_back(i);

    ParticleVariables aux = base_f->getVariables();
    p = aux;
   
  
}

void Firework::setFirework(Vector3 pos, Vector3 vel_, double lifeTime_, double damping_, double tamano_, Vector3 ace_, Vector4 color_,
    std::list<std::shared_ptr<ParticleGenerator>> gens_)
{
    for (auto i : gens_)
        gens.push_back(i);

    p.pose = PxTransform(pos.x, pos.y, pos.z);
    p.vel = vel_;
    p.lifeTime = lifeTime_;
    p.damping = damping_;
    p.tamano = tamano_;
    p.ace = ace_;
    p.color = color_;

    renderItem = new RenderItem(CreateShape(PxSphereGeometry(p.tamano)), &p.pose, p.color);

}

std::list<Particle*> Firework::Explode()
{
    std::list<Particle*> aux;

    for (auto i : gens) {
        std::list<Particle*> aux2;
        i->setMeanPos(p.pose.p, p.vel);
        aux2 = i->generateParticles();

        for (auto x : aux2)
            aux.push_back(x);
    }

    return aux;
}


