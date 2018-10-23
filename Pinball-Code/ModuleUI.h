#ifndef _UI_H_
#define _UI_H_


#include "Module.h"
#include <string>
typedef struct _TTF_Font TTF_Font;
struct SDL_Texture;
struct SDL_Color;
class ModuleFonts : public Module
{
public:
	p2List<SDL_Texture*> textureFonts;
	p2List<TTF_Font*> mFonts;
	TTF_Font* fontScore=nullptr;
	SDL_Texture* scoreRect = nullptr;
	SDL_Texture* scoreTex=nullptr;
	
public:
	ModuleFonts(bool start_enabled = true);
	~ModuleFonts();
	bool Init()  override;
	bool Start() override;
	bool CleanUp() override;
	update_status PostUpdate() override;


	SDL_Texture* LoadMessatgeTex(TTF_Font* thisfont, char* text, SDL_Color Color);

};

#endif // !_FONTS_H_

