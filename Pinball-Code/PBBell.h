#pragma once

#include "ModulePhysics.h"
#include "Module.h"

class PBBell : public PhysBody {
public:
	update_status Update() override;
	void OnCollisionEnter(PhysBody * bodyB) override;
private:
	iPoint offset = iPoint(-12,-18);
};