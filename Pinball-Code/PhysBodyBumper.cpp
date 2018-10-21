#include "PhysBodyBumper.h"
#include "ModulePlayScene.h"
#include "ModuleAudio.h"
#include "Module.h"
#include "Application.h"

void PhysBodyBumper::OnCollision(PhysBody * bodyB) {
	App->audio->PlayFx(App->scene_play->redBumperSFX);
	App->scene_play->IlluminateBlueCharacter();
}