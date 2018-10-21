#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ChainCoordinates.h"
ModulePlayScene::ModulePlayScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
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
	rick = App->textures->Load("pinball/rick_head.png");

	texBackground[0] = App->textures->Load("sprites/images/253.png");
	texBackground[1] = App->textures->Load("sprites/images/65.png");
	walls = App->textures->Load("sprites/images/253.png");

	redBouncerTex = App->textures->Load("sprites/images/155.png");

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

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

	redBouncer1 = App->physics->CreateBouncer(267, 256, 11);
	redBouncer1->listener = this;
	
	return ret;
}

// Load assets
bool ModulePlayScene::CleanUp()
{
	LOG("Unloading Play scene");
	App->textures->Unload(circle);
	App->textures->Unload(box);
	App->textures->Unload(rick);

	App->textures->Unload(texBackground[0]);
	App->textures->Unload(texBackground[1]);

	App->textures->Unload(walls);

	App->textures->Unload(redBouncerTex);

	//TODO: Remove SFX
	App->audio->UnloadSFX(bonus_fx);
	return true;
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
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	return UPDATE_CONTINUE;
}

update_status ModulePlayScene::PostUpdate()
{
	//Draw
	App->renderer->Blit(texBackground[1], 0, 0);
	App->renderer->Blit(texBackground[0], 0, 0);
	App->renderer->Blit(walls, 0, 0);
	//Bouncers
	iPoint pos;
	redBouncer1->GetPixelPosition(pos.x, pos.y);
	pos += redBouncerOffset;
	App->renderer->Blit(redBouncerTex, pos.x, pos.y);
	//Added physics shapes
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

	//Ball (on top of all before)

	return UPDATE_CONTINUE;
}

void ModulePlayScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//if (bodyA == ) {

	//}

	App->audio->PlayFx(bonus_fx);
}
