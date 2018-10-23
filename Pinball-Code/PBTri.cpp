#include "PBTri.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Application.h"

PBTri::PBTri(bool isLeft, int blitX, int blitY) : PhysBody(), isLeft(isLeft), blitX(blitX), blitY(blitY) {
}

void PBTri::OnCollisionEnter(PhysBody* bodyB) {

}

update_status PBTri::PostUpdate() {
	return UPDATE_CONTINUE;
}