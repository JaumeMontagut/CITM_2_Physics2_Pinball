#pragma once

#include "ModulePhysics.h"
#include "Module.h"

class PhysBodyPhone : public PhysBody {
public:
	void OnCollision(PhysBody * bodyB) override;
	update_status PostUpdate() override;

	void Activate();
	void Deactivate();
};