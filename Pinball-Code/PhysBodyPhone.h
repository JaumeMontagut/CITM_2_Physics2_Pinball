#pragma once

#include "ModulePhysics.h"
#include "Module.h"

struct SDL_Texture;

class PhysBodyPhone : public PhysBody {
public:
	PhysBodyPhone();
	void OnCollision(PhysBody * bodyB) override;
	update_status PostUpdate() override;

	void Activate();
	void Deactivate();

private:
	bool active = false;
	SDL_Texture * currTex = nullptr;
	SDL_Texture * activeTex = nullptr;
	SDL_Texture * unactiveTex = nullptr;
};