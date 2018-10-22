#ifndef _PHYS_BODY_ARROW_H_
#define _PHYS_BODY_ARROW_H_

#include "ModulePhysics.h"

class PBArrow : public PhysBody {

	update_status PostUpdate() override;
	void OnCollisionEnter(PhysBody * physBodyB) override;
};

#endif // !
