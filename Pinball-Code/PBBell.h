#pragma once

#include "ModulePhysics.h"
#include "Module.h"

class PBBell : public PhysBody {
public:
	update_status PostUpdate() override;
	void OnCollisionEnter(PhysBody * bodyB) override;
};