#include "PBTri.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Application.h"
#include "ModulePlayScene.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"

PBTri::PBTri(bool isLeft, int blitX, int blitY) : PhysBody(), isLeft(isLeft), blitX(blitX), blitY(blitY) {
	if (isLeft) {
		flip = SDL_FLIP_HORIZONTAL;
		frontOffset = iPoint(2, 16);
	}
	else {
		flip = SDL_FLIP_NONE;
		frontOffset = iPoint(10, 16);
	}
}

void PBTri::OnCollisionEnter(PhysBody* bodyB) {
	currFrame = 0u;
	App->audio->PlayFx(App->scene_play->triSFX);
	App->UI->AddScore(500);
}

update_status PBTri::Update() {
	if(currFrame < flashFrames) {
		App->renderer->Blit(App->scene_play->triBackTex, blitX + backOffset.x, blitY + backOffset.y, NULL, 1.0f, 0.0, INT_MAX, INT_MAX, flip);
		App->renderer->Blit(App->scene_play->triTex, blitX, blitY, NULL, 1.0f, 0.0, INT_MAX, INT_MAX, flip);
		App->renderer->Blit(App->scene_play->triFrontTex, blitX + frontOffset.x, blitY + frontOffset.y, NULL, 1.0f, 0.0, INT_MAX, INT_MAX, flip);
		currFrame++;
	}
	else {
		App->renderer->Blit(App->scene_play->triTex, blitX, blitY, NULL, 1.0f, 0.0, INT_MAX, INT_MAX, flip);
	}

	return UPDATE_CONTINUE;
}