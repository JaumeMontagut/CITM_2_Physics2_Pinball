#include "PBBumper.h"
#include "ModulePhysics.h"
#include "ModulePlayScene.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Module.h"
#include "Application.h"
#include "p2Point.h"
#include "ModuleUI.h"

PBBumper::PBBumper(BUMPER_TYPE type) : PhysBody(), type(type) {
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

void PBBumper::OnCollisionEnter (PhysBody * bodyB) {
	if (type == BUMPER_TYPE::Red) {
		App->scene_play->IlluminateBlueCharacter();
		App->UI->AddScore(3000);
	}
	App->audio->PlayFx(bumperSFX);
	currFlash = 0u;
	if (type == BUMPER_TYPE::Blue)
	{
		App->UI->AddScore(4000);
	}
	if (type == BUMPER_TYPE::Grey)
	{
		App->UI->AddScore(1000);
	}
}

update_status PBBumper::Update()
{
	int x, y;
	GetPixelPosition(x, y);
	if (currFlash < flashFrames) {
		App->renderer->Blit(flashTex, x + flashOffset.x, y + flashOffset.y);
		currFlash++;
	}
	App->renderer->Blit(bumperTex, x + bumperOffset.x, y + bumperOffset.y);
	return UPDATE_CONTINUE;
}
