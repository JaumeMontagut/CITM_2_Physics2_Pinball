#pragma once

#include "ModulePhysics.h"


class PBPlayer : public PhysBody
{
public:
	
	PBPlayer();
	update_status PostUpdate() override;
	/*PBPlayer(const iPoint &tpPoint, iPoint pixelPos, b2Vec2 forceDirection);
	void OnCollisionEnter(PhysBody* bodyB) override;
	void OnCollisionExit() override;
	b2Vec2 ForceDirection;
	update_status PreUpdate() override;
	update_status Update() override;
	
	bool entered = false;
	bool arrived = false;*/

};
