#pragma once

#include "ModulePhysics.h"
#include "p2Point.h"
#include "Module.h"

struct SDL_Texture;

class PBTri : public PhysBody {
public:
	PBTri(bool isLeft, int blitX, int blitY);
	void OnCollisionEnter(PhysBody* bodyB) override;
	update_status PostUpdate() override;
private:
	SDL_Texture * tex = nullptr;
	bool isLeft;
	int blitX;
	int blitY;
};