#include "PhysBodyPhone.h"
#include "Application.h"
#include "ModulePlayScene.h"

void PhysBodyPhone::OnCollision(PhysBody * bodyB)
{
	Activate();
}

update_status PhysBodyPhone::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void PhysBodyPhone::Activate()
{
	/*App->scene_play->IncreasePhoneCombo();*/
	//Show active sprite
}

void PhysBodyPhone::Deactivate()
{
	//Show idle sprite
}
