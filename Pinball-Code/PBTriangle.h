#pragma once

#include "ModulePhysics.h"
#include "Module.h"
#include "p2Point.h"
#include "p2List.h"

struct SDL_Texture;

class PBTriangle : public PhysBody {
public:
	PBTriangle();
	update_status PostUpdate() override;
	void OnCollisionEnter(PhysBody * bodyB) override;

	void Activate();
	void Deactivate();

private:
	SDL_Texture * activeTex = nullptr;
	SDL_Texture * inactiveTex = nullptr;
	SDL_Texture * currTex = nullptr;
	iPoint pivot = iPoint(0, 0);
	iPoint offset = iPoint(0, 0);
	bool active = false;
};