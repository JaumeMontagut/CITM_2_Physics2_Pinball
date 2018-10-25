#include "PBTeleport.h"
#include "Application.h"
#include "ModulePlayScene.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

PBteleport::PBteleport( const iPoint &tpPoint, iPoint pixelPos, b2Vec2 forceDirection):  PhysBody(),
TpPoint(tpPoint),ForceDirection(forceDirection),pos(pixelPos)
{
	
	
}

void PBteleport::OnCollisionEnter(PhysBody * bodyB)
{
	App->audio->PlayFx(App->scene_play->teleportSFX);
	if (!App->scene_play->PlayerEntereTele && !App->scene_play->PlayerArrivedTele && !App->scene_play->Playertraveling)
	{
		App->scene_play->ball->body->SetTransform({ PIXEL_TO_METERS((float)TpPoint.x), PIXEL_TO_METERS((float)TpPoint.y) }, 0);
		
		App->scene_play->PlayerEntereTele = true;
	}
	if (App->scene_play->Playertraveling)
	{
		App->scene_play->ball->body->SetAngularVelocity(0);
		App->scene_play->ball->body->SetLinearVelocity(ForceDirection);
		
		/*App->scene_play->ball->body->ApplyForce(ForceDirection, App->scene_play->ball->body->GetPosition(), true);*/
		App->scene_play->Playertraveling = false;
		App->scene_play->PlayerArrivedTele = true;
	}
	
}

void PBteleport::OnCollisionExit()
{
	if (App->scene_play->PlayerEntereTele==true)
	{
		App->scene_play->Playertraveling = true;
		App->scene_play->PlayerEntereTele = false;
	}
	if (App->scene_play->PlayerArrivedTele)
	{
		App->scene_play->PlayerArrivedTele = false;
	}
}

update_status PBteleport::Update()
{
	
	App->renderer->Blit(App->scene_play->teleportTex, pos.x-9, pos.y-9);

	
	
	return UPDATE_CONTINUE;
}
