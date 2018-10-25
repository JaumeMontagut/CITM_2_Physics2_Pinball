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
class PBStar;
class PBTriangle;

class ModulePlayScene : public Module
{
public:
	ModulePlayScene(bool start_enabled = true);
	~ModulePlayScene();

	bool Start();
	update_status PreUpdate();

	void LoseBall();

	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void IlluminateBlueCharacter();
	void IncreasePhoneCombo();
	void IncreaseYellowArrow();
	void IncreaseOrangeArrow();
	void IncreasePurpleArrow();
	void IncreaseStars();
	void IncreaseTriangles();

	void DeactivatePhoneCombo();
	void DeactivateYellowArrow(bool animation);
	void DeactivateOrangeArrow(bool animation);
	void DeactivatePurpleArrow(bool animation);
	void DeactivateStars();
	void DeactivateTriangles();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> Physbackground;
	SDL_Texture* handTex = nullptr;
	b2PrismaticJoint* m_joint;
	SDL_Texture* circleTex = nullptr;
	SDL_Texture* wallsTex = nullptr;
	SDL_Texture* backgroundTex = nullptr;
	//Tris
	SDL_Texture * triTex = nullptr;
	SDL_Texture * triBackTex = nullptr;
	SDL_Texture * triFrontTex = nullptr;
	uint triSFX = 0u;
	//Flipper
	uint flipperUpSFX = 0u;
	uint flipperDownSFX = 0u;
	SDL_Texture* fliperTex = nullptr;
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
	//Girl character
	SDL_Texture * girlCharacterTex = nullptr;
	//Blue light character
	bool illuminateCharacter = false;
	SDL_Texture * blueCharacter1Tex = nullptr;
	SDL_Texture * blueCharacter2Tex = nullptr;
	//Targets light
	uint activateTargetSFX = 0u;
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
	SDL_Texture * phoneInactive = nullptr;
	uint activePhonePieces = 0u;
	PBPhone * phonePieces[5] = { nullptr };
	uint phoneSFX = 0u;
	uint phoneBonusSFX = 0u;
	//Stars
	SDL_Texture * starActiveTex = nullptr;
	SDL_Texture * starInactiveTex = nullptr;
	uint activeStars = 0u;
	PBStar * stars[5u] = { nullptr };
	uint starBonusSFX = 0u;
	//Triangles
	SDL_Texture * triangleActiveTex = nullptr;
	SDL_Texture * triangleInactiveTex = nullptr;
	uint activeTriangles = 0u;
	PBTriangle * triangles[5u] = { nullptr };
	uint triangleBonusSFX = 0u;
	//Bell
	uint bellSFX = 0u;
	SDL_Texture * bellTex = nullptr;
	//Teleport
	SDL_Texture* teleportTex = nullptr;
	uint teleportSFX = 0u;
	//Exit play area
	uint exitAreaSFX = 0u;
	//Launch
	uint lauchSFX = 0u;
	//Ball hit
	uint ballHitSFX = 0u;


public :
	PhysBody * ball;
	bool PlayerEntereTele=false;
	bool PlayerArrivedTele = false;
	bool Playertraveling = false;
	
};
