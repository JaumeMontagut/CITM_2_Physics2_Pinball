#ifndef _PHYS_BODY_BOUNCER_H_
#define _PHYS_BODY_BOUNCER_H_

#include "ModulePhysics.h"
#include "p2Point.h"
#include "Module.h"

struct SDL_Texture;

class PhysBodyBumper : public PhysBody {
public:
	PhysBodyBumper(SDL_Texture* bumperTex, SDL_Texture* flashTex);
	void OnCollision(PhysBody* bodyB) override;
	update_status PostUpdate() override;
private:
	SDL_Texture * bumperTex = nullptr;
	iPoint bumperOffset = iPoint(-4, -2);
	SDL_Texture * flashTex = nullptr;
	iPoint flashOffset = iPoint(-13, -12);
	bool touched = false;
};

#endif // !
