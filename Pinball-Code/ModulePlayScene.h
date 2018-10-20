#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModulePlayScene : public Module
{
public:
	ModulePlayScene(Application* app, bool start_enabled = true);
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
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> Physbackground;
	PhysBody* redBouncer1;

	SDL_Texture* circle = nullptr;
	SDL_Texture* box = nullptr;
	SDL_Texture* rick = nullptr;
	SDL_Texture* walls = nullptr;
	SDL_Texture* redBouncer = nullptr;
	uint bonus_fx=0;


};
