#include "PhysBodyBouncer.h"
#include "ModulePlayScene.h"
#include "ModuleAudio.h"
#include "Module.h"
#include "Application.h"

void PhysBodyBouncer::OnCollision(PhysBody * bodyB) {
	App->audio->PlayFx(App->scene_play->bonus_fx);
}