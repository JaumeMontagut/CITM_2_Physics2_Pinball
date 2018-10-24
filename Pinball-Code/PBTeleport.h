
#include "ModulePhysics.h"


class PBteleport : public PhysBody
{
public:
	iPoint TpPoint;
	iPoint pos;
	PBteleport(const iPoint &tpPoint, iPoint pixelPos, b2Vec2 forceDirection);
	void OnCollisionEnter(PhysBody* bodyB) override;
	b2Vec2 ForceDirection;
	update_status Update() override;
	update_status PostUpdate() override;

};






