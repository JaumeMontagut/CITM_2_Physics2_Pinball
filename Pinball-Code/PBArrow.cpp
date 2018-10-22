#include "PBArrow.h"
#include "ModuleRender.h"
#include "Application.h"



update_status PBArrow::PostUpdate()
{
	//iPoint pos;
	//GetPixelPosition(pos.x, pos.y);
	//App->renderer->Blit(currTex, pos.x + offset.x, pos.y + offset.y, NULL, 1.0f, RADTODEG * body->GetAngle(), 8, 8);

	return UPDATE_CONTINUE;
}

void PBArrow::OnCollisionEnter(PhysBody * physBodyB)
{

}
