#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ChainCoordinates.h"
#include "PhysBodyBumper.h"
#include "PhysBodyPhone.h"

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
	phoneUnactive = App->textures->Load("sprites/sprites/DefineSprite_119/1.png");

	bonusSFX = App->audio->LoadFx("sprites/sounds/560_target_lightup.wav");
	redBumperSFX = App->audio->LoadFx("sprites/sounds/547_Bump - Body Hit 07.wav");
	bluegreyBumperSFX = App->audio->LoadFx("sprites/sounds/562_mushroom_bounce.wav");
	phoneSFX = App->audio->LoadFx("sprites/sounds/552_chatter_target_hit.wav");
	phoneBonusSFX = App->audio->LoadFx("sprites/sounds/553_chatter_bonus_activated.wav");

	Physbackground.add(App->physics->CreateChain(0,0, backgroundChain, 216));
	Physbackground.add(App->physics->CreateChain(0, 0, downRedPart, 28));
	Physbackground.add(App->physics->CreateChain(0, 0, right, 70));
	Physbackground.add(App->physics->CreateChain(0, 0, downleft, 12));
	Physbackground.add(App->physics->CreateChain(0, 0, downRight, 12));
	Physbackground.add(App->physics->CreateChain(0, 0, rightCenter, 84));
	Physbackground.add(App->physics->CreateChain(0, 0, center, 68));
	Physbackground.add(App->physics->CreateChain(0, 0, tel, 40));
	Physbackground.add(App->physics->CreateChain(0, 0, top, 26));
	Physbackground.add(App->physics->CreateChain(0, 0, firstTop, 12));
	Physbackground.add(App->physics->CreateChain(0, 0, secondTop, 10));
	Physbackground.add(App->physics->CreateChain(0, 0, leftTop, 16));
	Physbackground.add(App->physics->CreateChain(0, 0, leftTri, 12));
	Physbackground.add(App->physics->CreateChain(0, 0, centerLeftTri, 10));
	Physbackground.add(App->physics->CreateChain(0, 0, rightTri, 10));
	Physbackground.add(App->physics->CreateChain(0, 0, lastTri, 10));
	for (p2List_item<PhysBody*>* backitem = Physbackground.getFirst(); backitem; backitem = backitem->next)
	{
		backitem->data->body->SetType(b2_staticBody);
	}

	PhysBody* redBumper[5];
	redBumper[0] = App->physics->CreateBumper(267, 256, 11, BUMPER_TYPE::Red);
	redBumper[1] = App->physics->CreateBumper(322, 255, 11, BUMPER_TYPE::Red);
	redBumper[2] = App->physics->CreateBumper(272, 289, 11, BUMPER_TYPE::Red);
	redBumper[3] = App->physics->CreateBumper(320, 292, 11, BUMPER_TYPE::Red);
	redBumper[4] = App->physics->CreateBumper(291, 323, 11, BUMPER_TYPE::Red);

	PhysBody* blueBumper[3];
	blueBumper[0] = App->physics->CreateBumper(385, 101, 11, BUMPER_TYPE::Blue);
	blueBumper[1] = App->physics->CreateBumper(427,  95, 11, BUMPER_TYPE::Blue);
	blueBumper[2] = App->physics->CreateBumper(414, 137, 11, BUMPER_TYPE::Blue);

	PhysBody* greyBumper;
	greyBumper = App->physics->CreateBumper(158, 102, 11, BUMPER_TYPE::Grey);

	phonePieces[0] = App->physics->CreatePhonePiece(380, 131, 14, 6, -121.6f);
	phonePieces[1] = App->physics->CreatePhonePiece(10, 10, 14, 6, 0.0f);
	phonePieces[2] = App->physics->CreatePhonePiece(10, 10, 14, 6, 0.0f);
	phonePieces[3] = App->physics->CreatePhonePiece(10, 10, 14, 6, 0.0f);
	phonePieces[4] = App->physics->CreatePhonePiece(10, 10, 14, 6, 0.0f);

	//hand = App->physics->CreateRectangle(294,476,18,21);

	b2Body* handlauncher = App->physics->CreateChain(0, 0, rectangle, 8)->body;
	
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

	CreateFlipperJoint();
	
	
	return ret;
}

inline void ModulePlayScene::CreateFlipperJoint()
{
	CircleFlipper = App->physics->CreateCircle(133,463,4)->body;
	CircleFlipper->SetType(b2BodyType::b2_staticBody);
	rectangleFlipper = App->physics->CreateRectangle(151, 463, 40, 9)->body;
	rectangleFlipper->SetType(b2BodyType::b2_dynamicBody);

	b2RevoluteJointDef jointFlipperDef;
	jointFlipperDef.Initialize(rectangleFlipper, CircleFlipper, CircleFlipper->GetWorldCenter());
	jointFlipperDef.enableLimit = true;
	jointFlipperDef.lowerAngle = -45 * DEGTORAD;
	jointFlipperDef.upperAngle = 45 * DEGTORAD;

	joinFlipper = (b2RevoluteJoint*)App->physics->world->CreateJoint(&jointFlipperDef);

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
	
	//TODO: Remove SFX
	App->audio->UnloadSFX(bonusSFX);
	return true;
}

void ModulePlayScene::IlluminateBlueCharacter()
{
	illuminateCharacter = true;
}

void ModulePlayScene::IncreasePhoneCombo()
{
	activePhonePieces++;
	if (activePhonePieces > 5) {
		activePhonePieces = 0u;
		//TODO: Add bonus points
		App->audio->PlayFx(phoneSFX);
		for (uint i = 0; i < 5; ++i) {
			App->audio->PlayFx(phoneBonusSFX);
			phonePieces[i]->Deactivate();
		}
	}
}

update_status ModulePlayScene::PreUpdate()
{
	//Input
	return UPDATE_CONTINUE;
}

update_status ModulePlayScene::Update()
{

	//App->renderer->Blit(backgroundTex, 0, 0);
	//App->renderer->Blit(handTex, 275, 450 + METERS_TO_PIXELS(m_joint->GetBodyB()->GetPosition().y));
	//App->renderer->Blit(wallsTex, 0, 0);

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
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 6.5f));
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		m_joint->SetMotorSpeed((0.0F, 1.0F));
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		m_joint->SetMotorSpeed(-40.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		rectangleFlipper->ApplyAngularImpulse(-0.5f,true);
	}
	
	return UPDATE_CONTINUE;
}

update_status ModulePlayScene::PostUpdate()
{
	//Draw
	
	//- Bouncers

	p2List_item<PhysBody*>* circle = circles.getFirst();
	while (circle != NULL)
	{
		int x, y;
		circle->data->GetPixelPosition(x, y);
		App->renderer->Blit(circleTex, x, y, NULL, 1.0f, circle->data->GetRotation());
		circle = circle->next;
	}

	return UPDATE_CONTINUE;
}


