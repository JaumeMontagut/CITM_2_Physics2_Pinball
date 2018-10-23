#include "PBPhone.h"
#include "Application.h"
#include "ModulePlayScene.h"
#include "ModulePhysics.h"

PBPhone::PBPhone() : PhysBody()
{
	activeTex = App->scene_play->phoneActive;
	inactiveTex = App->scene_play->phoneInactive;

	currTex = inactiveTex;
}

void PBPhone::OnCollisionEnter(PhysBody * bodyB)
{
	if (!active) {
		Activate();
	}
}

update_status PBPhone::PostUpdate()
{
	iPoint pos;
	GetPixelPosition(pos.x,pos.y);
	App->renderer->Blit(currTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), 8, 8);
	return UPDATE_CONTINUE;
}

void PBPhone::Activate()
{
	active = true;
	currTex = activeTex;
	App->scene_play->IncreasePhoneCombo();
}

void PBPhone::Deactivate()
{
	active = false;
	currTex = inactiveTex;
}
