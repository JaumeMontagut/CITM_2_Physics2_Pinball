#include "ModuleFonts.h"

#include "SDL2_ttf-2.0.14/include/SDL_ttf.h"
#pragma comment(lib, "SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib")
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

bool ModuleFonts::CleanUp()
{
	TTF_Quit();
	return true;
}
