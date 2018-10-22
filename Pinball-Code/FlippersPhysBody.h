#ifndef _FLIPERPHYSBODY_H_
#define _FLIPERPHYSBODY_H_
#include "ModulePhysics.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL\include\SDL_scancode.h"
// Small class to return to other modules to track position and rotation of physics bodies
class FliperPhysbody : public PhysBody
{
public:
	
	
public:
	FliperPhysbody();
    update_status PostUpdate() override;

	/*virtual void OnCollision(PhysBody* bodyB);
	
	virtual update_status Update();
	virtual update_status PostUpdate();*/

};



#endif // !_FLIPERPHYSBODY_H

