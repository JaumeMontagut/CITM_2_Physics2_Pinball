#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleRender.h"

class PhysBody;

class ModulePlayScene : public Module
{
public:
	ModulePlayScene(bool start_enabled = true);
	~ModulePlayScene();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> Physbackground;


	SDL_Texture* circle = nullptr;
	SDL_Texture* box = nullptr;
	SDL_Texture* rick = nullptr;
	SDL_Texture* walls = nullptr;
	SDL_Texture* texBackground[2];
	SDL_Texture* redBouncerTex = nullptr;
	PhysBody* redBouncer1;
	iPoint redBouncerOffset = iPoint(-4, -2);
	uint bonus_fx=0;


};
