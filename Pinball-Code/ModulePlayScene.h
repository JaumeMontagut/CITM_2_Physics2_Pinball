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

	void IlluminateBlueCharacter();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> Physbackground;


	SDL_Texture* circle = nullptr;
	SDL_Texture* box = nullptr;
	SDL_Texture* wallsTex = nullptr;
	SDL_Texture* backgroundTex = nullptr;

	uint bonusSFX=0;

	//Red bumper
	SDL_Texture* redBumperTex = nullptr;
	PhysBody* redBumper1;//TODO: Make an array and incialize it to nullptr
	iPoint redBumperOffset = iPoint(-4, -2);
	uint redBumperSFX = 0;


private:
	//Blue light character
	bool illuminateCharacter = false;
	SDL_Texture * blueLightTex;
};
