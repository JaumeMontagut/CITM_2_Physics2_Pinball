#include "PBBell.h"
#include "ModuleAudio.h"
#include "ModulePlayScene.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "Application.h"

update_status PBBell::PostUpdate()
{
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
