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

class PhysBodyBumper : public PhysBody {
public:
	PhysBodyBumper(BUMPER_TYPE type);
	void OnCollisionEnter (PhysBody* bodyB) override;
	update_status PostUpdate() override;
private:
	SDL_Texture * bumperTex = nullptr;
	iPoint bumperOffset = iPoint(-4, -2);
	SDL_Texture * flashTex = nullptr;
	iPoint flashOffset = iPoint(-13, -12);
	bool touched = false;
	uint bumperSFX = 0;
	BUMPER_TYPE type;
};

#endif // !
