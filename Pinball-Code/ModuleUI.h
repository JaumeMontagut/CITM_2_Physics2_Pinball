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
    uint lifes=3;

public:
	void AddScore(uint score);
	void SubstractLifes();
	void ReStartGame();
public:
	ModuleFonts(bool start_enabled = true);
	~ModuleFonts();
	bool Init()  override;
	bool Start() override;
	bool CleanUp() override;
	update_status PreUpdate() override;
	update_status PostUpdate() override;
	SDL_Texture* LoadMessatgeTex(TTF_Font* thisfont, const char* text, SDL_Color Color);
	SDL_Texture* CreateNumTex(SDL_Texture* destroyTex, int num, TTF_Font* thisfont, SDL_Color Color);


private:

	//Score variables-----------------
	std::string stringnum;
	p2SString scoreString;
	uint scoreNum = 0;
	uint previusScore = 0;

	const char* aux0 = "0";
	bool isOnPlayAgain=false;
	bool enterOnPlayAgain = false;
	//High Score variables-------------
	uint hiScore = 0;
	std::string stringnumhiScore;
	p2SString hiScoreString;
	//Fonts--------------------------
	TTF_Font* VAGFont12 = nullptr;
	TTF_Font* GothicFont12 = nullptr;
	TTF_Font* candyFont = nullptr;
	TTF_Font* FuturaFont = nullptr;
	TTF_Font* playAgainScreenFontNum = nullptr;
	TTF_Font* playAgainScreenFontTex = nullptr;


	//PlayAgain Tex -------------------
	SDL_Texture* backgroundCircles = nullptr;
	SDL_Texture* playTex = nullptr;
	SDL_Texture* gameTex = nullptr;
	SDL_Texture* overTex = nullptr;
	SDL_Texture* againTex = nullptr;
	SDL_Texture* rectBigger = nullptr;
	SDL_Texture* scoreEnd = nullptr;
	SDL_Texture* highScore = nullptr;
	SDL_Texture* scorePrevios = nullptr;

	SDL_Texture* ScoreTexPlayAgain = nullptr;
	SDL_Texture* HiScoTexPlayAgain = nullptr;
	SDL_Texture* LastTexPlayAgain = nullptr;

	SDL_Texture* scoreRect = nullptr;
	SDL_Texture* scoreTex = nullptr;
	SDL_Texture* scoreNumTex = nullptr;
	SDL_Texture* lifeRectTex = nullptr;
	SDL_Texture* ballstexTex = nullptr;
	SDL_Texture* ballTex = nullptr;
	SDL_Texture* highScoreText=nullptr;
	SDL_Texture* hiScoreTexNum = nullptr;



	void SetHighScore();
};

#endif // !_FONTS_H_

