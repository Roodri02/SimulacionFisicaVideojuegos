#pragma once
#pragma once

#include <map>
#include "RigidForceGenerator.h"
#include "RigidParticle.h"

typedef std::pair<RigidForceGenerator*, RigidParticle*> RFRPair;


class RigidParticleForceRegistry : public std::multimap<RigidForceGenerator*, RigidParticle*>
{
public:
	void updateForces(double duration) {
		for (auto it = this->begin(); it != this->end(); it++) {
			it->first->updateForce(it->second, duration);
		}
	}


	void addRegistry(RigidForceGenerator* fg, RigidParticle* p) {
		insert(RFRPair{ fg,p });
	}

	void deleteParticleRegistry(RigidParticle* p) {
		for (auto it = begin(); it != end();) {
			if (it->second == p) it = erase(it);
			else it++;
		}
	}
};

