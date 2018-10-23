#include "PBArrow.h"
#include "ModulePhysics.h"
#include "Application.h"
#include "ModulePlayScene.h"
#include "ModuleRender.h"
#include "p2List.h"

PBArrow::PBArrow(ARROW_COLOR color) : color(color), PhysBody() {
	switch (color) {
	case ARROW_COLOR::YELLOW:
		inactiveTex = App->scene_play->yellowArrowInactiveTex;
		activeTex = App->scene_play->yellowArrowActiveTex;
		break;
	case ARROW_COLOR::ORANGE:
		inactiveTex = App->scene_play->orangeArrowInactiveTex;
		activeTex = App->scene_play->orangeArrowActiveTex;
		break;
	case ARROW_COLOR::PURPLE:
		inactiveTex = App->scene_play->purpleArrowInactiveTex;
		activeTex = App->scene_play->purpleArrowActiveTex;
		break;
	}
	currTex = inactiveTex;
}

update_status PBArrow::PostUpdate()
{
	iPoint pos;
	GetPixelPosition(pos.x, pos.y);
	if (currCombo < comboTime) {
		if (currCombo < 4u) {
			App->renderer->Blit(inactiveTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), pivot.x, pivot.y);
		}
		else if (currCombo < 8u) {
			App->renderer->Blit(activeTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), pivot.x, pivot.y);
		}
		else if (currCombo < 12u) {
			App->renderer->Blit(inactiveTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), pivot.x, pivot.y);
		}
		else if (currCombo < 16u) {
			App->renderer->Blit(activeTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), pivot.x, pivot.y);
		}
		else if (currCombo < 20u) {
			App->renderer->Blit(inactiveTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), pivot.x, pivot.y);
		}
		else {
			App->renderer->Blit(activeTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), pivot.x, pivot.y);
		}
		currCombo++;
	}
	else {
		App->renderer->Blit(currTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), pivot.x, pivot.y);
	}
	return UPDATE_CONTINUE;
}

void PBArrow::OnCollisionEnter(PhysBody * bodyB)
{
	if (!active) {
		Activate();
		switch (color) {
		case ARROW_COLOR::YELLOW:
			App->scene_play->IncreaseYellowArrow();
			break;
		case ARROW_COLOR::ORANGE:
			App->scene_play->IncreaseOrangeArrow();
			break;
		case ARROW_COLOR::PURPLE:
			App->scene_play->IncreasePurpleArrow();
			break;
		}
	}
}

void PBArrow::Activate()
{
	active = true;
	currTex = activeTex;
}

void PBArrow::Deactivate()
{
	active = false;
	currTex = inactiveTex;
	currCombo = 0u;
}
