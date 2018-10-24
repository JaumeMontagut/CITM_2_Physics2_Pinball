#include "PBTeleport.h"
#include "Application.h"
#include "ModulePlayScene.h"
#include "ModuleTextures.h"
PBteleport::PBteleport( const iPoint &tpPoint, iPoint pixelPos):  PhysBody(),TpPoint(tpPoint)
{
	pos = pixelPos;
	
}

update_status PBteleport::PostUpdate()
{
	
	App->renderer->Blit(App->scene_play->teleportTex, pos.x-9, pos.y-9);

	return UPDATE_CONTINUE;
}
