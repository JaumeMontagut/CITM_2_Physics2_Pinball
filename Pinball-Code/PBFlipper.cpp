#include "PBFlipper.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

PBFlipper::PBFlipper() : PhysBody()
{
}

PBFlipper::PBFlipper(b2Vec2 mesure) :PhysBody(), mesure(mesure)
{
}

update_status PBFlipper::PreUpdate()
{
	if (!rightfliper)
	{
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
			App->audio->PlayFx(App->scene_play->flipperUpSFX);
		}
		else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			body->ApplyTorque(-40, true);

		}
		else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP) {
			App->audio->PlayFx(App->scene_play->flipperDownSFX);
			body->ApplyTorque(40, true);
		}
	}


	else
	{
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
			App->audio->PlayFx(App->scene_play->flipperUpSFX);
		}
		else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			body->ApplyTorque(40, true);
		}
		else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP) {
			App->audio->PlayFx(App->scene_play->flipperDownSFX);
			body->ApplyTorque(-40, true);
		}

	}
	
	
	return UPDATE_CONTINUE;

}

update_status PBFlipper::Update()
{
	int x, y;
	GetPixelPosition(x,y);
	if (rightfliper)
	{
		App->renderer->Blit(App->scene_play->fliperTex, x-mesure.x / 2, y-mesure.y/2, NULL, 1.0f, RADTODEG * body->GetAngle(), mesure.x/2, mesure.y/2,SDL_FLIP_HORIZONTAL);
	}
	else
	{
		/*b2Vec2 thisposition= body->GetPosition();*/
		
		App->renderer->Blit(App->scene_play->fliperTex, x-mesure.x/2-4, y-mesure.y/2, NULL,1.0f, RADTODEG * body->GetAngle());
	}
	return UPDATE_CONTINUE;
}
