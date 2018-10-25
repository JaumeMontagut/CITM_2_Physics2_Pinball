#include "PBBell.h"
#include "ModuleAudio.h"
#include "ModulePlayScene.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "Application.h"

update_status PBBell::Update()
{
	int x, y;
	GetPixelPosition(x, y);
	App->renderer->Blit(App->scene_play->bellTex, x + offset.x, y + offset.y);
	return UPDATE_CONTINUE;
}

void PBBell::OnCollisionEnter(PhysBody * bodyB)
{
	b2Filter filter;
	filter.categoryBits = (uint16)COLLISION_FILTER::BALL;
	filter.maskBits = (uint16)COLLISION_FILTER::BACKGROUND;
	bodyB->body->GetFixtureList()->SetFilterData(filter);

	App->audio->PlayFx(App->scene_play->bellSFX);
}
