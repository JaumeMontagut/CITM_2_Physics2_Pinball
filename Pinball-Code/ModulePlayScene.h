#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleRender.h"
#include "Box2D\Box2D\Box2D.h"

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
	p2List<PhysBody*> Physbackground;
	PhysBody* hand;

	b2PrismaticJoint* m_joint;
	SDL_Texture* circle = nullptr;


	SDL_Texture* circleTex = nullptr;

	SDL_Texture* box = nullptr;
	SDL_Texture* wallsTex = nullptr;
	SDL_Texture* backgroundTex = nullptr;
	
	uint bonusSFX=0;

	//Bumpers
	SDL_Texture * flashTex = nullptr;
	//Red bumper
	SDL_Texture* redBumperTex = nullptr;
	PhysBody* redBumper[5] = {nullptr};
	uint redBumperSFX = 0;


private:
	//Blue light character
	bool illuminateCharacter = false;
	SDL_Texture * blueCharacter1Tex = nullptr;
	SDL_Texture * blueCharacter2Tex = nullptr;
};
