#ifndef _PHYS_BODY_BOUNCER_H_
#define _PHYS_BODY_BOUNCER_H_

#include "ModulePhysics.h"
#include "p2Point.h"
#include "Module.h"

struct SDL_Texture;

enum class BUMPER_TYPE {
	Red,
	Blue,
	Grey
};

class PBBumper : public PhysBody {
public:
	PBBumper(BUMPER_TYPE type);
	void OnCollisionEnter (PhysBody* bodyB) override;
	update_status PostUpdate() override;
private:
	SDL_Texture * bumperTex = nullptr;
	iPoint bumperOffset = iPoint(-4, -2);
	SDL_Texture * flashTex = nullptr;
	iPoint flashOffset = iPoint(-13, -12);
	uint bumperSFX = 0;
	BUMPER_TYPE type;
	const uint flashFrames = 4u;
	uint currFlash = flashFrames;
};

#endif // !
