#include "PBTriangle.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayScene.h"

PBTriangle::PBTriangle()
{
	activeTex = App->scene_play->starActiveTex;
	inactiveTex = App->scene_play->starInactiveTex;
	currTex = inactiveTex;
}

update_status PBTriangle::PostUpdate()
{
	iPoint pos;
	GetPixelPosition(pos.x, pos.y);
	App->renderer->Blit(currTex, pos.x, pos.y, NULL, 1.0f, RADTODEG * body->GetAngle(), pivot.x, pivot.y);
	return UPDATE_CONTINUE;
}

void PBTriangle::OnCollisionEnter(PhysBody * bodyB)
{
	if (!active) {
		Activate();
	}
}

void PBTriangle::Activate()
{
	active = true;
	currTex = activeTex;
	App->scene_play->IncreaseStars();
}

void PBTriangle::Deactivate()
{
	active = false;
	currTex = inactiveTex;
}
