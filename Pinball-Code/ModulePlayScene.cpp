#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ChainCoordinates.h"
#include "ModuleUI.h"
#include "PBBumper.h"
#include "PBPhone.h"
#include "PBArrow.h"
#include "PBStar.h"
#include "PBTriangle.h"

ModulePlayScene::ModulePlayScene(bool start_enabled) : Module(start_enabled)
{

}

ModulePlayScene::~ModulePlayScene()
{}

// Load assets
bool ModulePlayScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//Textures---------------------------------------------------------------------
	circleTex = App->textures->Load("sprites/images/174.png"); 
	wallsTex = App->textures->Load("sprites/images/253.png");
	backgroundTex = App->textures->Load("sprites/images/65.png");
	redBumperTex = App->textures->Load("sprites/images/155.png");
	blueBumperTex = App->textures->Load("sprites/images/160.png");
	greyBumperTex = App->textures->Load("sprites/images/163.png");
	blueCharacter1Tex = App->textures->Load("sprites/sprites/DefineSprite_78/1.png");
	blueCharacter2Tex = App->textures->Load("sprites/sprites/DefineSprite_78/2.png");
	flashTex = App->textures->Load("sprites/shapes/157.png");
	handTex = App->textures->Load("sprites/images/1.png");
	phoneActive = App->textures->Load("sprites/sprites/DefineSprite_119/2.png");
	phoneInactive = App->textures->Load("sprites/sprites/DefineSprite_119/1.png");
	fliperTex = App->textures->Load("sprites/images/fliper.png");
	yellowArrowInactiveTex = App->textures->Load("sprites/sprites/DefineSprite_93/1.png");
	yellowArrowActiveTex = App->textures->Load("sprites/sprites/DefineSprite_93/2.png");
	orangeArrowInactiveTex = App->textures->Load("sprites/sprites/DefineSprite_98/1.png");
	orangeArrowActiveTex = App->textures->Load("sprites/sprites/DefineSprite_98/2.png");
	purpleArrowInactiveTex = App->textures->Load("sprites/sprites/DefineSprite_113/1.png");
	purpleArrowActiveTex = App->textures->Load("sprites/sprites/DefineSprite_113/2.png");
	starInactiveTex = App->textures->Load("sprites/shapes/79.png");
	starActiveTex = App->textures->Load("sprites/shapes/81.png");
	triangleInactiveTex = App->textures->Load("sprites/shapes/100.png");
	triangleActiveTex = App->textures->Load("sprites/shapes/102.png");
	girlCharacterTex = App->textures->Load("sprites/images/64.png");
	triTex = App->textures->Load("sprites/images/250.png");
	triBackTex = App->textures->Load("sprites/images/237.png");
	triFrontTex = App->textures->Load("sprites/images/240.png");
	teleportTex = App->textures->Load("sprites/images/166.png");


	bonusSFX = App->audio->LoadFx("sprites/sounds/560_target_lightup.wav");
	redBumperSFX = App->audio->LoadFx("sprites/sounds/547_Bump - Body Hit 07.wav");
	bluegreyBumperSFX = App->audio->LoadFx("sprites/sounds/562_mushroom_bounce.wav");
	phoneSFX = App->audio->LoadFx("sprites/sounds/552_chatter_target_hit.wav");
	phoneBonusSFX = App->audio->LoadFx("sprites/sounds/553_chatter_bonus_activated.wav");
	activateTargetSFX = App->audio->LoadFx("sprites/sounds/560_target_lightup.wav");
	starBonusSFX = App->audio->LoadFx("sprites/sounds/544_happy_stars_anim.wav");
	triangleBonusSFX = App->audio->LoadFx("sprites/sounds/550_sunshine_harp.wav");
	flipperUpSFX = App->audio->LoadFx("sprites/sounds/540_flipper_up.wav");
	flipperDownSFX = App->audio->LoadFx("sprites/sounds/541_flipper_down.wav");
	triSFX = App->audio->LoadFx("sprites/sounds/556_triangle_bumper_bounce2.wav");
	
	App->audio->PlayMusic("sprites/sounds/538_song.ogg");

	Physbackground.add(App->physics->CreateChain(0,0, backgroundChain, 216, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, downRedPart, 28, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, right, 70, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, downleft, 12, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, downRight, 12, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, rightCenter, 84, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, center, 68, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, tel, 40, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, top, 26, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, firstTop, 12, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, secondTop, 10, b2_staticBody, 0.0f));
	Physbackground.add(App->physics->CreateChain(0, 0, leftTop, 16, b2_staticBody, 0.0f));

	App->physics->CreateBumper(267, 256, 11, BUMPER_TYPE::Red);
	App->physics->CreateBumper(322, 255, 11, BUMPER_TYPE::Red);
	App->physics->CreateBumper(272, 289, 11, BUMPER_TYPE::Red);
	App->physics->CreateBumper(320, 292, 11, BUMPER_TYPE::Red);
	App->physics->CreateBumper(291, 323, 11, BUMPER_TYPE::Red);

	App->physics->CreateBumper(385, 101, 11, BUMPER_TYPE::Blue);
	App->physics->CreateBumper(427,  95, 11, BUMPER_TYPE::Blue);
	App->physics->CreateBumper(414, 137, 11, BUMPER_TYPE::Blue);

	App->physics->CreateBumper(158, 102, 11, BUMPER_TYPE::Grey);

	App->physics->CreateTri(-115, 0, leftTriPoints, 10, true, 96, 376);
	App->physics->CreateTri(0, 0, rightTriPoint, 10, false, 218, 378);
	App->physics->CreateTri(0, 0, leftTriPoints, 10, true, 325, 378);
	App->physics->CreateTri(116, -2, rightTriPoint, 10, false, 451, 376);

	phonePieces[0] = App->physics->CreatePhonePiece(380, 131, 14, 6, -121.6f);
	phonePieces[1] = App->physics->CreatePhonePiece(391, 143, 14, 6, -150.0f);
	phonePieces[2] = App->physics->CreatePhonePiece(455, 82, 14, 6, 67.0f);
	phonePieces[3] = App->physics->CreatePhonePiece(460, 99, 14, 6, 85.2f);
	phonePieces[4] = App->physics->CreatePhonePiece(460, 115, 14, 6, 92.9f);

	yellowArrows[0] = App->physics->CreateArrow(131, 269, 13, 12, 63.1f, ARROW_COLOR::YELLOW);
	yellowArrows[1] = App->physics->CreateArrow(142, 286, 13, 12, 63.1f, ARROW_COLOR::YELLOW);
	yellowArrows[2] = App->physics->CreateArrow(243, 361, 13, 12, 41.3f, ARROW_COLOR::YELLOW);

	orangeArrows[0] = App->physics->CreateArrow(472, 201, 13, 12, 60.7f, ARROW_COLOR::ORANGE);
	orangeArrows[1] = App->physics->CreateArrow(481, 219, 13, 12, 61.2f, ARROW_COLOR::ORANGE);

	purpleArrows[0] = App->physics->CreateArrow(444, 285, 13, 12, -60.2f, ARROW_COLOR::PURPLE);
	purpleArrows[1] = App->physics->CreateArrow(454, 269, 13, 12, -62.3f, ARROW_COLOR::PURPLE);
	purpleArrows[2] = App->physics->CreateArrow(346, 361, 13, 12, -41.1f, ARROW_COLOR::PURPLE);

	stars[0] = App->physics->CreateStar(371, 397, 12, 12, -49.2f);
	stars[1] = App->physics->CreateStar(384, 375, 12, 12, -30.9f);
	stars[2] = App->physics->CreateStar(410, 366, 12, 12, 0.0f);
	stars[3] = App->physics->CreateStar(436, 375, 12, 12, 30.9f);
	stars[4] = App->physics->CreateStar(450, 397, 12, 12, 49.2f);

	triangles[0] = App->physics->CreateTriangle(133, 382, 16, 7, -51.3f);
	triangles[1] = App->physics->CreateTriangle(155, 367, 16, 7, -26.2f);
	triangles[2] = App->physics->CreateTriangle(181, 357, 16, 7, 0.0f);
	triangles[3] = App->physics->CreateTriangle(207, 367, 16, 7, 26.2f);
	triangles[4] = App->physics->CreateTriangle(229, 382, 16, 7, 51.3f);

	App->physics->CreateTeleport({ 177,240 }, { 175,283 });
	App->physics->CreateTeleport({ 177,283 }, { 177,240 });

	App->physics->CreateTeleport({ 414,240 }, { 414,275 });
	App->physics->CreateTeleport({ 414,280 }, { 414,237 });

	b2Body* handlauncher = App->physics->CreateChain(0, 0, rectangle, 8, b2_dynamicBody, 0.0f, COLLISION_FILTER::FOREGROUND)->body;
	
	b2PrismaticJointDef jointDef;
	jointDef.Initialize(App->physics->ground, handlauncher, { 294,294 }, { 0.0f, 1.0f });

	jointDef.enableLimit = true;
	jointDef.lowerTranslation = 0.0f;
	jointDef.upperTranslation = 0.7f;
	

	jointDef.enableMotor = true;
	jointDef.maxMotorForce = 500.0f;
	jointDef.motorSpeed = 0.0f;
	jointDef.collideConnected = false;
	m_joint = (b2PrismaticJoint*)App->physics->world->CreateJoint(&jointDef);


	App->physics->CreateFliper(133, 463, false);
	App->physics->CreateFliper(224, 464, true);

	App->physics->CreateFliper(362, 461, false);

	App->physics->CreateFliper(458, 463, true);
	
	ball = App->physics->CreateCircle(294, 450, 6.5f);
	ball->body->SetBullet(true);
	circles.add(ball);
	
	
	return ret;
}



// Load assets
bool ModulePlayScene::CleanUp()
{
	LOG("Unloading Play scene");
	App->textures->Unload(circleTex);
	App->textures->Unload(wallsTex);
	App->textures->Unload(backgroundTex);
	App->textures->Unload(wallsTex);
	App->textures->Unload(redBumperTex);
	App->textures->Unload(blueCharacter1Tex);
	App->textures->Unload(flashTex);
	App->textures->Unload(handTex);
	App->textures->Unload(fliperTex);
	App->textures->Unload(yellowArrowActiveTex);
	App->textures->Unload(yellowArrowInactiveTex);
	App->textures->Unload(orangeArrowActiveTex);
	App->textures->Unload(orangeArrowInactiveTex);
	App->textures->Unload(purpleArrowActiveTex);
	App->textures->Unload(purpleArrowInactiveTex);
	App->textures->Unload(starActiveTex);
	App->textures->Unload(starInactiveTex);
	App->textures->Unload(triTex);
	App->textures->Unload(triBackTex);
	App->textures->Unload(triFrontTex);

	return true;
}

void ModulePlayScene::IlluminateBlueCharacter()
{
	illuminateCharacter = true;
}

void ModulePlayScene::IncreasePhoneCombo()
{
	activePhonePieces++;
	App->audio->PlayFx(phoneSFX);
	if (activePhonePieces >= 5u) {
		activePhonePieces = 0u;
		//TODO: Add bonus points
		App->audio->PlayFx(phoneBonusSFX);
		for (uint i = 0u; i < 5u; ++i) {
			phonePieces[i]->Deactivate();
		}
	}
}

void ModulePlayScene::IncreaseYellowArrow()
{
	activeYellowArrows++;
	App->audio->PlayFx(activateTargetSFX);
	if (activeYellowArrows >= 3u) {
		activeYellowArrows = 0u;
		//TODO: Add bonus points
		for (uint i = 0u; i < 3u; ++i) {
			yellowArrows[i]->Deactivate();
		}
	}
}

void ModulePlayScene::IncreaseOrangeArrow()
{
	activeOrangeArrows++;
	App->audio->PlayFx(activateTargetSFX);
	if (activeOrangeArrows >= 2u) {
		activeOrangeArrows = 0u;
		//TODO: Add bonus points
		for (uint i = 0u; i < 2u; ++i) {
			orangeArrows[i]->Deactivate();
		}
	}
}

void ModulePlayScene::IncreasePurpleArrow()
{
	activePurpleArrows++;
	App->audio->PlayFx(activateTargetSFX);
	if (activePurpleArrows >= 3u) {
		activePurpleArrows = 0u;
		//TODO: Add bonus points
		for (uint i = 0u; i < 3u; ++i) {
			purpleArrows[i]->Deactivate();
		}
	}
}

void ModulePlayScene::IncreaseStars()
{
	activeStars++;
	App->audio->PlayFx(activateTargetSFX);
	if (activeStars >= 5u) {
		activeStars = 0u;
		//TODO: Add bonus points
		App->audio->PlayFx(starBonusSFX);
		for (uint i = 0u; i < 5u; ++i) {
			stars[i]->Deactivate();
		}
	}
}

void ModulePlayScene::IncreaseTriangles()
{
	activeTriangles++;
	App->audio->PlayFx(activateTargetSFX);
	if (activeTriangles >= 5u) {
		activeTriangles = 0u;
		//TODO: Add bonus points
		App->audio->PlayFx(triangleBonusSFX);
		for (uint i = 0u; i < 5u; ++i) {
			triangles[i]->Deactivate();
		}
	}
}

update_status ModulePlayScene::PreUpdate()
{
	if (App->fonts->lifes > 0)
	{
		if (METERS_TO_PIXELS(ball->body->GetPosition().y) > SCREEN_HEIGHT)
		{
			ball->body->SetLinearVelocity({ 0,0 });
			ball->body->SetAngularVelocity(0.0f);
			ball->body->SetTransform({ PIXEL_TO_METERS(294),PIXEL_TO_METERS(450) }, 0);
			App->fonts->SubstractLifes();
		}

	}
	
	//Input
	return UPDATE_CONTINUE;
}

update_status ModulePlayScene::Update()
{
	App->renderer->Blit(backgroundTex, 0, 0);
	App->renderer->Blit(handTex, 275, 450 + METERS_TO_PIXELS(m_joint->GetBodyB()->GetPosition().y));
	App->renderer->Blit(wallsTex, 0, 0);

	if (!illuminateCharacter) {
		App->renderer->Blit(blueCharacter1Tex, 234, 192);
	}
	else {
		App->renderer->Blit(blueCharacter2Tex, 234, 192);
		illuminateCharacter = false;
	}

	//Logic
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		PhysBody* circle = App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 6.5f);
		circle->body->SetBullet(true);
		circles.add(circle);
		
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		m_joint->SetMotorSpeed((0.0F, 1.0F));
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		m_joint->SetMotorSpeed(-40.0f);
	}

	
	return UPDATE_CONTINUE;
}

update_status ModulePlayScene::PostUpdate()
{
	//Draw forward elements
	App->renderer->Blit(girlCharacterTex, 145, 381);

	//Draw
	p2List_item<PhysBody*>* circle = circles.getFirst();
	while (circle != NULL)
	{
		int x, y;
		circle->data->GetPixelPosition(x, y);
		App->renderer->Blit(circleTex, x, y, NULL, 1.0f, circle->data->GetRotation());
		circle = circle->next;
	}
	/*App->fonts->PrintMessage(App->fonts->font, "Hola que hace xd", { 155,50,0,255 });*/
	return UPDATE_CONTINUE;
}


