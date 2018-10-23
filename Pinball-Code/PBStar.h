#pragma once

#include "ModulePhysics.h"
#include "Module.h"
#include "p2Point.h"
#include "p2List.h"

struct SDL_Texture;

class PBStar : public PhysBody {
public:
	PBStar();
	update_status PostUpdate() override;
	void OnCollisionEnter(PhysBody * bodyB) override;

	void Activate();
	void Deactivate();

private:
	SDL_Texture * activeTex = nullptr;
	SDL_Texture * inactiveTex = nullptr;
	SDL_Texture * currTex = nullptr;
	iPoint pivot = iPoint(9, 8);
	iPoint offset = iPoint(-3, -3);
	bool active = false;
};