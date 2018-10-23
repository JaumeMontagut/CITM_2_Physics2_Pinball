#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleRender.h"
#include "Box2D\Box2D\Box2D.h"

class PhysBody;
class PBPhone;
class PBArrow;

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
	void IncreasePhoneCombo();
	void IncreaseYellowArrow();
	void IncreaseOrangeArrow();
	void IncreasePurpleArrow();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> Physbackground;
	SDL_Texture* handTex = nullptr;
	b2PrismaticJoint* m_joint;
	SDL_Texture* circle = nullptr;
	SDL_Texture* circleTex = nullptr;
	SDL_Texture* wallsTex = nullptr;
	SDL_Texture* backgroundTex = nullptr;
	SDL_Texture* fliperTex = nullptr;

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
	//Arrows
	uint arrowSFX = 0u;
	//Yellow arrow
	SDL_Texture * yellowArrowActiveTex = nullptr;
	SDL_Texture * yellowArrowInactiveTex = nullptr;
	PBArrow * yellowArrows[3u] = { nullptr };
	uint activeYellowArrows = 0u;
	//Orange arrow
	SDL_Texture * orangeArrowActiveTex = nullptr;
	SDL_Texture * orangeArrowInactiveTex = nullptr;
	PBArrow * orangeArrows[2u] = { nullptr };
	uint activeOrangeArrows = 0u;
	//Purple arrow
	SDL_Texture * purpleArrowActiveTex = nullptr;
	SDL_Texture * purpleArrowInactiveTex = nullptr;
	PBArrow * purpleArrows[3u] = { nullptr };
	uint activePurpleArrows = 0u;
	//Phone piece
	SDL_Texture * phoneActive = nullptr;
	SDL_Texture * phoneUnactive = nullptr;
	uint activePhonePieces = 0u;
	PBPhone * phonePieces[5] = { nullptr };
	uint phoneSFX = 0u;
	uint phoneBonusSFX = 0u;

public :
	PhysBody * ball;

	
};
