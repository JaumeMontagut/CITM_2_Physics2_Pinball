#ifndef _PHYS_BODY_BOUNCER_H_
#define _PHYS_BODY_BOUNCER_H_

#include "ModulePhysics.h"

class PhysBodyBouncer : public PhysBody {
	void OnCollision(PhysBody* bodyB) override;
};

#endif // !
