#ifndef _FONTS_H_
#define _FONTS_H_


#include "Module.h"

typedef struct _TTF_Font TTF_Font;
struct SDL_Texture;

class ModuleFonts : public Module
{
public:
	p2List<SDL_Texture*> textureFonts;
	p2List<TTF_Font*> mFonts;
public:
	ModuleFonts(bool start_enabled = true);
	~ModuleFonts();
	bool Init()  override;
	SDL_Texture* CreateTextTexture(TTF_Font* fonts , char* text);
	SDL_Texture* GetText(char* text, char* filename, int size);
	TTF_Font* GetFont(std::string filename, int size);

	bool CleanUp() override;
};

#endif // !_FONTS_H_

