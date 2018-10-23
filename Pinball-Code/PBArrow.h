#ifndef _PHYS_BODY_ARROW_H_
#define _PHYS_BODY_ARROW_H_

#include"ModulePhysics.h"
#include"Module.h"

enum class ARROW_COLOR {
	YELLOW,
	ORANGE,
	PURPLE
};

class PBArrow : public PhysBody{
	PBArrow(ARROW_COLOR color);
	update_status PostUpdate() override;
	void OnCollsion(PhysBody * bodyB)override;

	void Activate();
	void Deactivate();

private:
	SDL_Texture * activeTex = nullptr;
	SDL_Texture * inactiveTex = nullptr;
	SDL_Texture * currTex = nullptr;
}


#endif // !_PHYS_BODY_ARROW_H_
