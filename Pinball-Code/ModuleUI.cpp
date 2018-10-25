#include "Application.h"
#include "ModuleUI.h"
#include "SDL2_ttf-2.0.14/include/SDL_ttf.h"
#pragma comment(lib, "SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib")
#include "ModuleTextures.h"
#include "ModuleRender.h"

#include "ModuleInput.h"
#include "ModulePlayScene.h"
#include "ModulePhysics.h"




void ModuleFonts::AddScore(uint addscore)

{
	SDL_DestroyTexture(scoreNumTex);
	scoreNum += addscore;
	stringnum = std::to_string(scoreNum);
	const char* charnum = stringnum.c_str();

	

	uint digits = 0;
	uint aux = scoreNum;

	if (aux < 0) digits = 1; 
	while (aux) {
		aux /= 10;
		digits++;
	}

	for (uint i = 0; i < 8 - digits; i++)
	{
		scoreString += aux0;
	}
	scoreString += charnum;

	scoreNumTex = LoadMessatgeTex(GothicFont12, scoreString.GetString(), { 255,255,255,255 });

	scoreString.Clear();
	stringnum.clear();
	
}

void ModuleFonts::SubstractLifes()
{
	if (lifes >= 0)
	{
		lifes -= 1;
	}

}

void ModuleFonts::ReStartGame()
{
	if (lifes>0)
	{
		App->scene_play->ball->body->SetTransform({ (float)PIXEL_TO_METERS(294),(float)PIXEL_TO_METERS(440) }, 0.0f);
		App->scene_play->Playertraveling = false;
		App->scene_play->PlayerArrivedTele = false;
		App->scene_play->PlayerEntereTele = false;
		App->scene_play->ball->body->SetAngularVelocity(0.0f);
		App->scene_play->ball->body->SetLinearVelocity({ 0,0 });

		b2Filter filter;
		filter.categoryBits = (uint16)COLLISION_FILTER::BALL;
		filter.maskBits = (uint16)COLLISION_FILTER::FOREGROUND;
		App->scene_play->ball->body->GetFixtureList()->SetFilterData(filter);

	}

}

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
	//PlayAgainTex--------------------------------------------------------------
	backgroundCircles = App->textures->Load("sprites/images/BackgroundBlueCircles.png");
	gameTex = App->textures->Load("sprites/images/Game.png");
	overTex = App->textures->Load("sprites/images/over.png");
	playTex = App->textures->Load("sprites/images/play.png");
	againTex = App->textures->Load("sprites/images/again.png");


	//Fonts-------------------------------------------------------------------
	VAGFont12 = TTF_OpenFont("sprites/fonts/463_VAG Rounded Std Light.ttf", 12);
	GothicFont12 = TTF_OpenFont("sprites/fonts/38_TradeGothic Bold.ttf", 12);
	 candyFont = TTF_OpenFont("sprites/fonts/463_VAG Rounded Std Light.ttf", 12);
	 FuturaFont = TTF_OpenFont("sprites/fonts/463_VAG Rounded Std Light.ttf", 12);
	 playAgainScreenFontNum = TTF_OpenFont("sprites/fonts/38_TradeGothic Bold.ttf", 24);
	 playAgainScreenFontTex = TTF_OpenFont("sprites/fonts/463_VAG Rounded Std Light.ttf", 24);

	//Images-------------------------------------------------------------
	scoreRect = App->textures->Load("sprites/images/score.png");
	lifeRectTex = App->textures->Load("sprites/images/ballsCount.png");
	ballTex = App->textures->Load("sprites/images/lifes.png");
	rectBigger = App->textures->Load("sprites/images/RectBigger.png");

	scoreTex = LoadMessatgeTex(VAGFont12, "score", { 255,255,255,255 });
	scoreNumTex = LoadMessatgeTex(GothicFont12, "00000000", { 255,255,255,255 });
	ballstexTex = LoadMessatgeTex(FuturaFont, "Balls", { 255,255,255,255 });
	highScoreText = LoadMessatgeTex(FuturaFont, "hi score", { 254,152,51,255 });
	hiScoreTexNum= LoadMessatgeTex(GothicFont12, "00000000", { 254,152,51,255 });

	return true;
}
bool ModuleFonts::CleanUp()
{
	App->textures->Unload(scoreRect);
	App->textures->Unload(lifeRectTex);
	App->textures->Unload(ballTex);

	SDL_DestroyTexture(scoreTex);
	SDL_DestroyTexture(scoreNumTex);
	SDL_DestroyTexture(ballstexTex);
	SDL_DestroyTexture(highScoreText);

	TTF_Quit();
	return true;
}

update_status ModuleFonts::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_R))
	{
		enterOnPlayAgain = false;
		isOnPlayAgain = false;
		previusScore = scoreNum;
		lifes = 3;
		scoreNum = 0;
		AddScore(0);

		ReStartGame();
	}
	if (lifes == 0 )
	{
		enterOnPlayAgain = true;
		

	}
	if (hiScore < scoreNum)
	{
		hiScore = scoreNum;
		SetHighScore();
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleFonts::PostUpdate()
{
	if(scoreRect !=nullptr)
	App->renderer->Blit(scoreRect, 9, 455);
	App->renderer->Blit(scoreRect, 500, 455,NULL,1.0f,0.0f,NULL,NULL,SDL_FLIP_HORIZONTAL);
	App->renderer->Blit(scoreTex, 15, 460);
	App->renderer->Blit(scoreNumTex,16,473);
	App->renderer->Blit(lifeRectTex, 310, 458);
	App->renderer->Blit(ballstexTex, 318, 464);
	App->renderer->Blit(highScoreText, 530, 460);
	App->renderer->Blit(hiScoreTexNum, 517, 473);

	if (lifes > 0)
	{
		App->renderer->Blit(ballTex, 336, 477);
		if (lifes > 1)
		{
			App->renderer->Blit(ballTex, 325, 477);
			if (lifes == 3)
			{
				App->renderer->Blit(ballTex, 315, 477);
			}
		}
	}
	if (enterOnPlayAgain && !isOnPlayAgain)
	{
		enterOnPlayAgain = false;
		scoreEnd = CreateNumTex(scoreEnd, scoreNum, playAgainScreenFontNum, { 255,255,255,255 });
		highScore = CreateNumTex(scoreEnd, hiScore, playAgainScreenFontNum, { 249,155,60,255 });
		scorePrevios = CreateNumTex(scoreEnd, previusScore, playAgainScreenFontNum, { 255,255,255,255 });
		ScoreTexPlayAgain = LoadMessatgeTex(playAgainScreenFontTex, "Score", { 255,255,255,255 });
		HiScoTexPlayAgain = LoadMessatgeTex(playAgainScreenFontTex, "Hi Score", { 255,255,255,255 });
		LastTexPlayAgain = LoadMessatgeTex(playAgainScreenFontTex, "Pre Score", { 255,255,255,255 });

		isOnPlayAgain = true;
	}
	if (isOnPlayAgain)
	{
		App->renderer->Blit(backgroundCircles, 93, 50);
		App->renderer->Blit(gameTex, 129, 4);
		App->renderer->Blit(overTex, 258, 68);
		App->renderer->Blit(playTex, 172, 330);
		App->renderer->Blit(playTex, 284, 334);
		App->renderer->Blit(rectBigger, 118, 178);
		App->renderer->Blit(rectBigger, 300, 178, NULL, 1.0f, 0.0f, NULL, NULL, SDL_FLIP_HORIZONTAL);
		App->renderer->Blit(rectBigger, 200, 255);
		

		App->renderer->Blit(ScoreTexPlayAgain, 130, 190);
		App->renderer->Blit(scoreEnd, 132, 207);

		App->renderer->Blit(HiScoTexPlayAgain,360 , 190);
		App->renderer->Blit(highScore, 321, 209);

		App->renderer->Blit(LastTexPlayAgain, 210, 265);
		App->renderer->Blit(scorePrevios, 219, 286);



	}
	return update_status::UPDATE_CONTINUE;
}





SDL_Texture* ModuleFonts::LoadMessatgeTex(TTF_Font* thisfont,const char * text, SDL_Color Color)
{
	SDL_Texture *textTex = nullptr;
	SDL_Surface* textSurf=nullptr;

	if (thisfont != nullptr)
		textSurf = TTF_RenderText_Solid(thisfont, text, Color);
	else
	{
		LOG("%s", TTF_GetError())
		return nullptr;
	}
		
		

	if (textSurf != nullptr)
	{
		
		SDL_Rect textRect;
		
		textTex = SDL_CreateTextureFromSurface(App->renderer->renderer, textSurf);
		if (textTex == nullptr)
			LOG("%s", SDL_GetError());

		SDL_QueryTexture(textTex, NULL, NULL, &textRect.w, &textRect.h);
		App->renderer->Blit(textTex, 0, 0);
		SDL_FreeSurface(textSurf);
		
	}

	return textTex;
}

SDL_Texture * ModuleFonts::CreateNumTex(SDL_Texture * destroyTex, int num, TTF_Font* thisfont, SDL_Color Color)
{
	SDL_Texture * TexNum = nullptr;

	if(destroyTex!=nullptr)
	SDL_DestroyTexture(destroyTex);


	std::string auxString;

	auxString = std::to_string(num);
	const char* charnum = auxString.c_str();

	uint digits = 0;
	uint aux = num;

	if (aux < 0) digits = 1;
	while (aux) {
		aux /= 10;
		digits++;
	}
	p2SString auxCerosString;
	for (uint i = 0; i < 8 - digits; i++)
	{
		auxCerosString += aux0;
	}
	auxCerosString += charnum;

	TexNum = LoadMessatgeTex(thisfont, auxCerosString.GetString(), Color);

	auxCerosString.Clear();
	auxString.clear();



	return TexNum;
}

void ModuleFonts::SetHighScore()
{
	SDL_DestroyTexture(hiScoreTexNum);
	
	stringnumhiScore = std::to_string(hiScore);
	const char* charnum = stringnumhiScore.c_str();

	

	uint digits = 0;
	uint aux = scoreNum;

	if (aux < 0) digits = 1; // remove this line if '-' counts as a digit
	while (aux) {
		aux /= 10;
		digits++;
	}

	for (uint i = 0; i < 8 - digits; i++)
	{
		hiScoreString += aux0;
	}
	hiScoreString += charnum;

	hiScoreTexNum = LoadMessatgeTex(GothicFont12, hiScoreString.GetString(), { 254,152,51,255 });

	hiScoreString.Clear();
	stringnumhiScore.clear();
}



