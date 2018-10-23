#ifndef _UI_H_
#define _UI_H_


#include "Module.h"
#include <string>
#include "p2SString.h"
typedef struct _TTF_Font TTF_Font;
struct SDL_Texture;
struct SDL_Color;
class ModuleFonts : public Module
{
public:

	//Fonts--------------------------
	TTF_Font* VAGFont12=nullptr;
	TTF_Font* GothicFont12 = nullptr;
	TTF_Font* candyFont = nullptr;
	TTF_Font* FuturaFont = nullptr;

	SDL_Texture* scoreRect = nullptr;
	SDL_Texture* scoreTex=nullptr;
	SDL_Texture* scoreNumTex = nullptr;
	uint scoreNum=0;
public:
	void SetScore(uint score);
public:
	ModuleFonts(bool start_enabled = true);
	~ModuleFonts();
	bool Init()  override;
	bool Start() override;
	bool CleanUp() override;
	update_status PreUpdate() override;
	update_status PostUpdate() override;


	SDL_Texture* LoadMessatgeTex(TTF_Font* thisfont, const char* text, SDL_Color Color);
private:
	std::string stringnum;
	p2SString scoreString;
};

#endif // !_FONTS_H_

