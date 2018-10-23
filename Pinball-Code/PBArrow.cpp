#include "PBArrow.h"
#include "Application.h"
#include "ModulePlayScene.h"
#include "ModuleRender.h"

PBArrow::PBArrow(ARROW_COLOR color) {
	switch (color) {
	case ARROW_COLOR::YELLOW:
		break;
	case ARROW_COLOR::ORANGE:
		break;
	case ARROW_COLOR::PURPLE:
		inactiveTex = App->scene_play->yellowArrowInactiveTex;
		activeTex = App->scene_play->yellowArrowActiveTex;
		currTex = inactiveTex;
		break;
	}
}

update_status PBArrow::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void PBArrow::OnCollsion(PhysBody * bodyB)
{
	switch (ARROW_COLOR) {
		App->scene_play->IncreaseYellowArrow();
	}

}

void PBArrow::Activate()
{
}

void PBArrow::Deactivate()
{
}
