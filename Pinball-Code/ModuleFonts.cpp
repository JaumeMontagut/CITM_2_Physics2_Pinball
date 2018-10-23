#include "Application.h"
#include "ModuleFonts.h"
#include "SDL2_ttf-2.0.14/include/SDL_ttf.h"
#pragma comment(lib, "SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib")
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include <string>
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

SDL_Texture * ModuleFonts::CreateTextTexture(TTF_Font * fonts, char * text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(fonts, text, {0,0,0});
	if (surface == NULL)
	{
		LOG("Text Render Error &s\n", TTF_GetError());
		return nullptr;
	}
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface(App->renderer->renderer,surface);
	if (tex == NULL)
	{
		LOG("Text Texture Creation Error %s \n", SDL_GetError());
		return nullptr;
	}
	SDL_FreeSurface(surface);

	return tex;
}

SDL_Texture * ModuleFonts::GetText(char * text, char * filename, int size)
{
	return nullptr;
}

TTF_Font * ModuleFonts::GetFont(std::string filename, int size)
{
	std::string  fullPath = SDL_GetBasePath();
	fullPath.append("sprites/fonts" + filename);
	
	return nullptr;
}



bool ModuleFonts::CleanUp()
{
	TTF_Quit();
	return true;
}
