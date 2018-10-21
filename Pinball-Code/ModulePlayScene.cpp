#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ChainCoordinates.h"

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

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	wallsTex = App->textures->Load("sprites/images/253.png");
	backgroundTex = App->textures->Load("sprites/images/65.png");
	redBumperTex = App->textures->Load("sprites/images/155.png");
	blueCharacter1Tex = App->textures->Load("sprites/sprites/DefineSprite_78/1.png");
	blueCharacter2Tex = App->textures->Load("sprites/sprites/DefineSprite_78/2.png");

	bonusSFX = App->audio->LoadFx("sprites/sounds/560_target_lightup.wav");
	redBumperSFX = App->audio->LoadFx("sprites/sounds/547_Bump - Body Hit 07.wav");

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

	redBumper1 = App->physics->CreateBumper(267, 256, 11);
	
	return ret;
}

// Load assets
bool ModulePlayScene::CleanUp()
{
	LOG("Unloading Play scene");
	App->textures->Unload(circle);
	App->textures->Unload(box);
	App->textures->Unload(wallsTex);
	App->textures->Unload(backgroundTex);
	App->textures->Unload(wallsTex);
	App->textures->Unload(redBumperTex);
	App->textures->Unload(blueCharacter1Tex);

	//TODO: Remove SFX
	App->audio->UnloadSFX(bonusSFX);
	return true;
}

void ModulePlayScene::IlluminateBlueCharacter()
{
	illuminateCharacter = true;
}

update_status ModulePlayScene::PreUpdate()
{
	//Input
	return UPDATE_CONTINUE;
}

update_status ModulePlayScene::Update()
{
	//Logic
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	//Draw
	App->renderer->Blit(backgroundTex, 0, 0);
	App->renderer->Blit(wallsTex, 0, 0);
	if (!illuminateCharacter) {
		App->renderer->Blit(blueCharacter1Tex, 234, 192);
	}
	else {
		App->renderer->Blit(blueCharacter2Tex, 234, 192);
		illuminateCharacter = false;
	}
	//- Bouncers
	iPoint pos;
	redBumper1->GetPixelPosition(pos.x, pos.y);
	pos += redBumperOffset;
	App->renderer->Blit(redBumperTex, pos.x, pos.y);
	//- Added physics shapes
	p2List_item<PhysBody*>* c = circles.getFirst();
	while (c != NULL)
	{
		int x, y;
		c->data->GetPixelPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();
	while (c != NULL)
	{
		int x, y;
		c->data->GetPixelPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}
	//- Ball (on top of all before)

	return UPDATE_CONTINUE;
}

update_status ModulePlayScene::PostUpdate()
{

	return UPDATE_CONTINUE;
}
