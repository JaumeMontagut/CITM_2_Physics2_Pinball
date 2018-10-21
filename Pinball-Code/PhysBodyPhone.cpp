#include "PhysBodyPhone.h"
#include "Application.h"
#include "ModulePlayScene.h"
#include "ModulePhysics.h"

PhysBodyPhone::PhysBodyPhone() : PhysBody()
{
	activeTex = App->scene_play->phoneActive;
	unactiveTex = App->scene_play->phoneUnactive;

	currTex = unactiveTex;
}

void PhysBodyPhone::OnCollision(PhysBody * bodyB)
{
	if (!activeTex) {
		Activate();
	}
}

update_status PhysBodyPhone::PostUpdate()
{
	int x, y;
	GetPixelPosition(x,y);
	App->renderer->Blit(currTex, x, y);
	return UPDATE_CONTINUE;
}

void PhysBodyPhone::Activate()
{
	active = true;
	App->scene_play->IncreasePhoneCombo();
	currTex = activeTex;
}

void PhysBodyPhone::Deactivate()
{
	active = false;
	currTex = unactiveTex;
	//Show idle sprite
}
