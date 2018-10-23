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
	OpenFont("sprites/fonts/463_VAG Rounded Std Light.ttf", 48);
	scoreTex = App->textures->Load("sprites/images/score.png");
	return true;
}
bool ModuleFonts::CleanUp()
{
	App->textures->Unload(scoreTex);

	TTF_Quit();
	return true;
}

update_status ModuleFonts::PostUpdate()
{
	if(scoreTex !=nullptr)
	App->renderer->Blit(scoreTex, 9, 455);

	return update_status::UPDATE_CONTINUE;
}

//SDL_Texture * ModuleFonts::CreateTextTexture(TTF_Font * fonts, char * text)
//{
//	SDL_Surface* surface = TTF_RenderText_Solid(fonts, text, {0,0,0});
//	if (surface == NULL)
//	{
//		LOG("Text Render Error &s\n", TTF_GetError());
//		return nullptr;
//	}
//	
//	SDL_Texture* tex = SDL_CreateTextureFromSurface(App->renderer->renderer,surface);
//	if (tex == NULL)
//	{
//		LOG("Text Texture Creation Error %s \n", SDL_GetError());
//		return nullptr;
//	}
//	SDL_FreeSurface(surface);
//
//	return tex;
//}




bool ModuleFonts::OpenFont(char* fontPath, int size)
{
	font= TTF_OpenFont(fontPath, size);
	if (font == NULL)
	{
		return false;
	}
	return true;
}

bool ModuleFonts::PrintMessage(TTF_Font* thisfont, char * text, SDL_Color Color)
{
	SDL_Surface* textSurf=nullptr;
	if (thisfont != nullptr)
		textSurf = TTF_RenderText_Solid(thisfont, text, Color);
	else
		return false;

	if (textSurf != nullptr)
	{
		SDL_Texture *textTex =nullptr;
		SDL_Rect textRect;
		
		textTex = SDL_CreateTextureFromSurface(App->renderer->renderer, textSurf);
		SDL_QueryTexture(textTex, NULL, NULL, &textRect.w, &textRect.h);
		App->renderer->Blit(textTex, 0, 0);
		SDL_FreeSurface(textSurf);
		App->textures->Unload(textTex);
	}

	return true;
}



