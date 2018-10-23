#include "PBStar.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayScene.h"

PBStar::PBStar()
{
	activeTex = App->scene_play->starActiveTex;
	inactiveTex = App->scene_play->starInactiveTex;
	currTex = inactiveTex;
}

update_status PBStar::PostUpdate()
{
	iPoint pos;
	GetPixelPosition(pos.x, pos.y);
	App->renderer->Blit(currTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), pivot.x, pivot.y);
	return UPDATE_CONTINUE;
}

void PBStar::OnCollisionEnter(PhysBody * bodyB)
{
	if (!active) {
		Activate();
	}
}

void PBStar::Activate()
{
	active = true;
	currTex = activeTex;
	App->scene_play->IncreaseStars();
}

void PBStar::Deactivate()
{
	active = false;
	currTex = inactiveTex;
}
