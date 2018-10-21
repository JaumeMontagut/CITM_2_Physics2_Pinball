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

	PhysBody* handlauncher;
	SDL_Texture* handTex = nullptr;

	
	b2PrismaticJoint* m_joint;
	SDL_Texture* circle = nullptr;

	
	SDL_Texture* circleTex = nullptr;

	SDL_Texture* box = nullptr;
	SDL_Texture* wallsTex = nullptr;
	SDL_Texture* backgroundTex = nullptr;
	
	uint bonusSFX=0;

	//Bumpers
	SDL_Texture * flashTex = nullptr;
	//Blue bumper
	SDL_Texture * blueBumperTex = nullptr;
	uint bluegreyBumperSFX = 0u;
	//Red bumper
	SDL_Texture* redBumperTex = nullptr;
	uint redBumperSFX = 0u;
	//Grey bumper
	SDL_Texture * greyBumperTex = nullptr;
	//Blue light character
	bool illuminateCharacter = false;
	SDL_Texture * blueCharacter1Tex = nullptr;
	SDL_Texture * blueCharacter2Tex = nullptr;
};
