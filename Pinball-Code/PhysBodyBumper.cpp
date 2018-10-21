#include "PhysBodyBumper.h"
#include "ModulePlayScene.h"
#include "ModuleAudio.h"
#include "Module.h"
#include "Application.h"

void PhysBodyBumper::OnCollision(PhysBody * bodyB) {
	App->audio->PlayFx(App->scene_play->redBumperSFX);
	App->scene_play->IlluminateBlueCharacter();
}

update_status PhysBodyBumper::PostUpdate()
{
	int x, y;
	GetPixelPosition(x, y);
	App->renderer->Blit(App->scene_play->flashTex, x + App->scene_play->flashOffset.x, y + App->scene_play->flashOffset.y);
	return UPDATE_CONTINUE;
}
