#include "Application.h"
#include "ModuleUI.h"
#include "SDL2_ttf-2.0.14/include/SDL_ttf.h"
#pragma comment(lib, "SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib")
#include "ModuleTextures.h"
#include "ModuleRender.h"

#include "ModuleInput.h"
void ModuleFonts::SetScore(uint addscore)
{
	App->textures->Unload(scoreNumTex);

	scoreNum += addscore;
	stringnum = std::to_string(scoreNum);
	const char* charnum = stringnum.c_str();

	scoreString;


	const char* aux0 = "0";

	uint digits = 0;
	uint aux = scoreNum;

	if (aux < 0) digits = 1; // remove this line if '-' counts as a digit
	while (aux>10) {
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
	if (lifes > 0)
	{
		lifes -= 1;
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

	
	//Fonts-------------------------------------------------------------------
	VAGFont12 = TTF_OpenFont("sprites/fonts/463_VAG Rounded Std Light.ttf", 12);
	GothicFont12 = TTF_OpenFont("sprites/fonts/38_TradeGothic Bold.ttf", 12);
	 candyFont = TTF_OpenFont("sprites/fonts/463_VAG Rounded Std Light.ttf", 12);
	 FuturaFont = TTF_OpenFont("sprites/fonts/463_VAG Rounded Std Light.ttf", 12);

	//Images-------------------------------------------------------------
	scoreRect = App->textures->Load("sprites/images/score.png");
	scoreTex = LoadMessatgeTex(VAGFont12, "score", { 255,255,255,255 });
	scoreNumTex = LoadMessatgeTex(GothicFont12, "00000000", { 255,255,255,255 });
	lifeRectTex = App->textures->Load("sprites/images/ballsCount.png");
	ballstexTex = LoadMessatgeTex(FuturaFont, "Balls", { 255,255,255,255 });
	ballTex= App->textures->Load("sprites/images/lifes.png");

	return true;
}
bool ModuleFonts::CleanUp()
{
	App->textures->Unload(scoreRect);
	App->textures->Unload(scoreTex);
	App->textures->Unload(scoreNumTex);
	TTF_Quit();
	return true;
}

update_status ModuleFonts::PreUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_0))
	{
		SetScore(1000);
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleFonts::PostUpdate()
{
	if(scoreRect !=nullptr)
	App->renderer->Blit(scoreRect, 9, 455);
	App->renderer->Blit(scoreTex, 15, 460);
	App->renderer->Blit(scoreNumTex,16,473);
	App->renderer->Blit(lifeRectTex, 310, 458);
	App->renderer->Blit(ballstexTex, 318, 464);
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

	return update_status::UPDATE_CONTINUE;
}





SDL_Texture* ModuleFonts::LoadMessatgeTex(TTF_Font* thisfont,const char * text, SDL_Color Color)
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



