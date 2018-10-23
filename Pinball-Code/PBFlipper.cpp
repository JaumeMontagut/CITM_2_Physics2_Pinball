#include "PBFlipper.h"



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
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			body->ApplyTorque(-40, true);

		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
		{
			body->ApplyTorque(40, true);
		}
	}
	else
	{
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			body->ApplyTorque(40, true);
		}
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		{
			body->ApplyTorque(-40, true);
		}

	}
	
	
	return UPDATE_CONTINUE;

}

update_status PBFlipper::PostUpdate()
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
