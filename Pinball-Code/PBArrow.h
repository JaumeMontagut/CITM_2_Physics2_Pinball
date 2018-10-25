#pragma once

#include "ModulePhysics.h"
#include "Module.h"
#include "p2Point.h"
#include "p2List.h"

struct SDL_Texture;

enum class ARROW_COLOR {
	YELLOW,
	ORANGE,
	PURPLE
};

class PBArrow : public PhysBody {
public:
	PBArrow(ARROW_COLOR color);
	update_status PostUpdate() override;
	void OnCollisionEnter(PhysBody * bodyB) override;

	void Activate();
	void Deactivate();
	void StartComboAnim();

private:
	SDL_Texture * activeTex = nullptr;
	SDL_Texture * inactiveTex = nullptr;
	SDL_Texture * currTex = nullptr;
	iPoint offset = iPoint(0,-8);
	iPoint pivot = iPoint(9,13);
	ARROW_COLOR color;
	uint comboTime = 24u;
	uint currCombo = comboTime;
	bool active = false;
};