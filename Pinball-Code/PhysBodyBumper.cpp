#include "PhysBodyBumper.h"
#include "ModulePhysics.h"
#include "ModulePlayScene.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Module.h"
#include "Application.h"
#include "p2Point.h"

PhysBodyBumper::PhysBodyBumper(SDL_Texture* bumperTex, SDL_Texture * flashTex) : PhysBody(),
bumperTex(bumperTex),
flashTex(flashTex) {

}

void PhysBodyBumper::OnCollision(PhysBody * bodyB) {
	App->audio->PlayFx(App->scene_play->redBumperSFX);
	App->scene_play->IlluminateBlueCharacter();
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
