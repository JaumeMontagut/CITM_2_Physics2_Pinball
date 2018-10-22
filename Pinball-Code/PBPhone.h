#pragma once

#include "ModulePhysics.h"
#include "Module.h"
#include "SDL/include/SDL_stdinc.h"

struct SDL_Texture;

class PBPhone : public PhysBody {
public:
	PBPhone();
	void OnCollisionEnter(PhysBody * bodyB) override;
	update_status PostUpdate() override;

	void Activate();
	void Deactivate();

private:
	bool active = false;
	SDL_Texture * currTex = nullptr;
	SDL_Texture * activeTex = nullptr;
	SDL_Texture * unactiveTex = nullptr;
	iPoint offset = iPoint(-1,-6);
};