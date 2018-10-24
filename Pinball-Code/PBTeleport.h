
#include "ModulePhysics.h"


class PBteleport : public PhysBody
{
public:
	iPoint TpPoint;
	iPoint pos;
	PBteleport(const iPoint &tpPoint, iPoint pixelPos);
	update_status PostUpdate() override;

};






