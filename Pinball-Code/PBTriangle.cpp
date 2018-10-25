#include "PBTriangle.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayScene.h"

PBTriangle::PBTriangle()
{
	activeTex = App->scene_play->triangleActiveTex;
	inactiveTex = App->scene_play->triangleInactiveTex;
	currTex = inactiveTex;
}

update_status PBTriangle::Update()
{
	iPoint pos;
	GetPixelPosition(pos.x, pos.y);
	App->renderer->Blit(currTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), pivot.x, pivot.y);
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
	App->scene_play->IncreaseTriangles();
}

void PBTriangle::Deactivate()
{
	active = false;
	currTex = inactiveTex;
}
