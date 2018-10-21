#include "PhysBodyBumper.h"
#include "ModulePhysics.h"
#include "ModulePlayScene.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Module.h"
#include "Application.h"
#include "p2Point.h"

PhysBodyBumper::PhysBodyBumper(BUMPER_TYPE type) : PhysBody(), type(type) {
	switch (type) {
	case BUMPER_TYPE::Blue:
		bumperTex = App->scene_play->blueBumperTex;
		flashTex = App->scene_play->flashTex;
		bumperSFX = App->scene_play->bluegreyBumperSFX;
		break;
	case BUMPER_TYPE::Red:
		bumperTex = App->scene_play->redBumperTex;
		flashTex = App->scene_play->flashTex;
		bumperSFX = App->scene_play->redBumperSFX;
		break;
	case BUMPER_TYPE::Grey:
		bumperTex = App->scene_play->greyBumperTex;
		flashTex = App->scene_play->flashTex;
		bumperSFX = App->scene_play->bluegreyBumperSFX;
		break;
	}
}

void PhysBodyBumper::OnCollision(PhysBody * bodyB) {
	if (type == BUMPER_TYPE::Red) {
		App->scene_play->IlluminateBlueCharacter();
	}
	App->audio->PlayFx(bumperSFX);
	touched = true;
}

update_status PhysBodyBumper::PostUpdate()
{
	int x, y;
	GetPixelPosition(x, y);
	if (touched) {
		App->renderer->Blit(flashTex, x + flashOffset.x, y + flashOffset.y);
		touched = false;
	}
	App->renderer->Blit(bumperTex, x + bumperOffset.x, y + bumperOffset.y);
	return UPDATE_CONTINUE;
}
