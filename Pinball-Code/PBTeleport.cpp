#include "PBTeleport.h"
#include "Application.h"
#include "ModulePlayScene.h"
#include "ModuleTextures.h"
PBteleport::PBteleport( const iPoint &tpPoint, iPoint pixelPos, b2Vec2 forceDirection):  PhysBody(),TpPoint(tpPoint)
{
	pos = pixelPos;
	
}

void PBteleport::OnCollisionEnter(PhysBody * bodyB)
{
	if (!App->scene_play->teleporting)
	{
		App->scene_play->ball->body->SetTransform({ PIXEL_TO_METERS((float)TpPoint.x), PIXEL_TO_METERS((float)TpPoint.y) }, 0);
		App->scene_play->ball->body->SetAngularVelocity(0.0f);
		/*App->scene_play->ball->body->SetLinearVelocity(ForceDirection);*/
		App->scene_play->ball->body->ApplyForce(ForceDirection, App->scene_play->ball->body->GetPosition(),true);
		App->scene_play->teleporting = true;
	}
	
}

update_status PBteleport::Update()
{
	/*if (App->scene_play->ball->body->GetPosition() == body->GetPosition())
	{
		
	}*/

	return UPDATE_CONTINUE;
}

update_status PBteleport::PostUpdate()
{
	
	App->renderer->Blit(App->scene_play->teleportTex, pos.x-9, pos.y-9);

	return UPDATE_CONTINUE;
}
