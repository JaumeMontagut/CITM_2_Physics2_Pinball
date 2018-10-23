#include "Application.h"
#include "ModuleUI.h"
#include "SDL2_ttf-2.0.14/include/SDL_ttf.h"
#pragma comment(lib, "SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib")
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModuleFonts::ModuleFonts(bool start_enabled)
{
}

ModuleFonts::~ModuleFonts()
{
}

bool ModuleFonts::Init()
{
	if (TTF_Init() == -1)
	{
		LOG("Initialization error: %s\n", TTF_GetError());
		return false;
	}
	
	return true;
}
bool ModuleFonts::Start()
{

	
	//Fonts-------------------------------------------------------------------
	fontScore = TTF_OpenFont("sprites/fonts/463_VAG Rounded Std Light.ttf", 48);

	//Images-------------------------------------------------------------
	scoreRect = App->textures->Load("sprites/images/score.png");
	scoreTex = LoadMessatgeTex(fontScore, "score", { 255,255,255,255 });
	return true;
}
bool ModuleFonts::CleanUp()
{
	App->textures->Unload(scoreRect);
	App->textures->Unload(scoreTex);
	TTF_Quit();
	return true;
}

update_status ModuleFonts::PostUpdate()
{
	if(scoreRect !=nullptr)
	App->renderer->Blit(scoreRect, 9, 455);
	App->renderer->Blit(scoreTex, 15, 463);
	return update_status::UPDATE_CONTINUE;
}





SDL_Texture* ModuleFonts::LoadMessatgeTex(TTF_Font* thisfont, char * text, SDL_Color Color)
{
	SDL_Texture *textTex = nullptr;
	SDL_Surface* textSurf=nullptr;

	if (thisfont != nullptr)
		textSurf = TTF_RenderText_Solid(thisfont, text, Color);
	else
		return nullptr;

	if (textSurf != nullptr)
	{
		
		SDL_Rect textRect;
		
		textTex = SDL_CreateTextureFromSurface(App->renderer->renderer, textSurf);
		SDL_QueryTexture(textTex, NULL, NULL, &textRect.w, &textRect.h);
		App->renderer->Blit(textTex, 0, 0);
		SDL_FreeSurface(textSurf);
		
	}

	return textTex;
}



