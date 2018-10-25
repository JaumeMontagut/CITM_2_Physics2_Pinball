#pragma once

#include "ModulePhysics.h"
#include "p2Point.h"
#include "Module.h"
#include "SDL/include/SDL_render.h"

struct SDL_Texture;

class PBTri : public PhysBody {
public:
	PBTri(bool isLeft, int blitX, int blitY);
	void OnCollisionEnter(PhysBody* bodyB) override;
	update_status Update() override;
private:
	SDL_Texture * tex = nullptr;
	bool isLeft;
	int blitX;
	int blitY;
	uint flashFrames = 4u;
	uint currFrame = flashFrames;
	SDL_RendererFlip flip;
	iPoint backOffset = iPoint(-8, 0);
	iPoint frontOffset; 
};