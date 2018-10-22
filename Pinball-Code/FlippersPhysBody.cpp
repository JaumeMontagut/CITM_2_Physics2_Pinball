#include "FlippersPhysBody.h"


FliperPhysbody::FliperPhysbody():PhysBody()
{
	
	
}

update_status FliperPhysbody::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		body->ApplyAngularImpulse(-0.5f, true);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		body->ApplyAngularImpulse(0.5f, true);
	}
	return UPDATE_CONTINUE;

}
