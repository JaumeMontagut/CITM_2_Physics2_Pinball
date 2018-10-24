
#include "ModulePhysics.h"


class PBteleport : public PhysBody
{
public:
	iPoint TpPoint;
	iPoint pos;
	
	PBteleport(const iPoint &tpPoint, iPoint pixelPos, b2Vec2 forceDirection);
	void OnCollisionEnter(PhysBody* bodyB) override;
	void OnCollisionExit() override;
	b2Vec2 ForceDirection;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool entered=false;
	bool arrived=false;

};






