#pragma once

#include "ModulePhysics.h"
#include "Module.h"
#include "p2Point.h"
#include "p2List.h"

struct SDL_Texture;

class PBTriangle : public PhysBody {
public:
	PBTriangle();
	update_status Update() override;
	void OnCollisionEnter(PhysBody * bodyB) override;

	void Activate();
	void Deactivate();

private:
	SDL_Texture * activeTex = nullptr;
	SDL_Texture * inactiveTex = nullptr;
	SDL_Texture * currTex = nullptr;
	iPoint offset = iPoint(0, 0);
	iPoint pivot = iPoint(10, 3);
	bool active = false;
};