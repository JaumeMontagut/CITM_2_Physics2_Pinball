#include "PBPlayer.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayScene.h"
#include "ModuleAudio.h"

PBPlayer::PBPlayer()
{
}

update_status PBPlayer::PostUpdate()
{
	//Draw
	
	b2Vec2 posPix ( body->GetPosition());
	posPix.x = METERS_TO_PIXELS(posPix.x);
	posPix.y = METERS_TO_PIXELS(posPix.y);

	App->renderer->Blit(App->scene_play->circleTex, posPix.x-width/2, posPix.y - width / 2, NULL, 1.0f, GetRotation());
	

	return update_status();
}

void PBPlayer::OnCollisionEnter(PhysBody * bodyB)
{
	b2Vec2 velocity = body->GetLinearVelocity();
	if (!bodyB->body->GetFixtureList()->IsSensor() && (velocity.x * velocity.x + velocity.y * velocity.y) > 10) {
		App->audio->PlayFx(App->scene_play->ballHitSFX);
	}
}
