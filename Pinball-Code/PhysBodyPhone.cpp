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
	iPoint pos;
	GetPixelPosition(pos.x,pos.y);
	App->renderer->Blit(currTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), 8, 8);
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
