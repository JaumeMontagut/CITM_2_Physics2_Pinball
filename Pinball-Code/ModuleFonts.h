#ifndef _FONTS_H_
#define _FONTS_H_
#pragma comment (lib, "SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib")
#include "SDL2_ttf-2.0.14\include\SDL_ttf.h"
#include "Module.h"

class ModuleFonts : public Module
{
public:
	ModuleFonts(bool start_enabled = true);
	~ModuleFonts();

};

#endif // !_FONTS_H_

