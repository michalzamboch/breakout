#include "include.h"

/*
- Název - Breakout
1. start
2. obtinost
3. exit
*/

/********************************************************************************/

extern void pockejNaStiskKlavesy();

extern void breakout(obtiznost *obtiznostVar, SDL_Renderer *vykresleni);
extern void vypisText(int x, int y, char *text, SDL_Renderer *vykresleni);
extern void smazObrazovku(SDL_Renderer *vykresleni);

void menu(SDL_Renderer *vykresleni);
static int menuTemplate(int x, int y, char *moznosti[], int pocetMoznosti, SDL_Renderer *vykresleni);

static void nastavUkazatel(int pozice, int startY, ukazatel *point);
static void vykresliUkazatel(ukazatel *point, SDL_Renderer *vykresleni);
static void smazUkazatel(ukazatel *point, SDL_Renderer *vykresleni);

static obtiznost *vytvorObtiznost(urovneObtiznosti urovenX);
static void nastavObtiznost(urovneObtiznosti urovenX, obtiznost *menenaObtiznost);
static void uvolniObtiznost(obtiznost *mazanaObtiznost);

/********************************************************************************/

void menu(SDL_Renderer *vykresleni)
{
	obtiznost *obtiznostVar = vytvorObtiznost(stredni);
	int x = radkovani;
	int y = x;

	bool odejit = false;

	while (odejit == false)
	{
		char *mainMenuStrings[] = {"Start", "Obtiznost", "Konec"};
		int mainMenuNavrat = menuTemplate(x, y, mainMenuStrings, 3, vykresleni);
		if (mainMenuNavrat == 1)
		{
			breakout(obtiznostVar, vykresleni);
		}
		else if (mainMenuNavrat == 2)
		{
			char *volbaObtiznostiStrings[] = {"Lehka", "Stredni", "Tezka"};
			int volbaObtiznostiNavrat = menuTemplate(x, y, volbaObtiznostiStrings, 3, vykresleni);
			switch (volbaObtiznostiNavrat)
			{
			case 1:
				nastavObtiznost(lehka, obtiznostVar);
				break;
			case 2:
				nastavObtiznost(stredni, obtiznostVar);
				break;
			case 3:
				nastavObtiznost(tezka, obtiznostVar);
				break;
			}
		}
		else if (mainMenuNavrat == 3)
		{
			char *odchodStrings[] = {"Ano", "Ne"};
			int odchodNavrat = menuTemplate(x, y, odchodStrings, 2, vykresleni);
			if (odchodNavrat == 1)
			{
				odejit = true;
			}
		}
		else
		{
			exit(3);
		}
	}

	uvolniObtiznost(obtiznostVar);
}

static int menuTemplate(int x, int y, char *moznosti[], int pocetMoznosti, SDL_Renderer *vykresleni)
{
	int i;
	for (i = 0; i < pocetMoznosti; i++)
	{
		/*-> vypis moznosti*/
		int pozY = y + i * radkovani - radkovani / 2 + 5;
		int pozX = x + radkovani / 2;
		vypisText(pozX, pozY, moznosti[i], vykresleni);
	}

	bool ukoncit = false;
	SDL_Event udalost;

	int pozice = 1;
	ukazatel menuUkazatel;
	nastavUkazatel(pozice, 40, &menuUkazatel);
	vykresliUkazatel(&menuUkazatel, vykresleni);

	while (ukoncit == false)
	{
		SDL_WaitEvent(&udalost);
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if ((state[SDL_SCANCODE_UP]) && (pozice > 1))
		{
			smazUkazatel(&menuUkazatel, vykresleni);
			pozice--;
			nastavUkazatel(pozice, 40, &menuUkazatel);
			vykresliUkazatel(&menuUkazatel, vykresleni);
		}
		else if ((state[SDL_SCANCODE_DOWN]) && (pozice < pocetMoznosti))
		{
			smazUkazatel(&menuUkazatel, vykresleni);
			pozice++;
			nastavUkazatel(pozice, 40, &menuUkazatel);
			vykresliUkazatel(&menuUkazatel, vykresleni);
		}
		else if (state[SDL_SCANCODE_RETURN])
		{
			ukoncit = true;
		}
	}

	smazObrazovku(vykresleni);
	return pozice;
}

static void nastavUkazatel(int pozice, int startY, ukazatel *point)
{
	point->souradnice.x = 30;
	point->souradnice.y = startY + ((pozice - 1) * 40);
	point->souradnice.h = strana_ukazatele;
	point->souradnice.w = strana_ukazatele;
}

static void vykresliUkazatel(ukazatel *point, SDL_Renderer *vykresleni)
{
	SDL_SetRenderDrawColor(vykresleni, 255, 255, 255, 255);
	SDL_RenderFillRect(vykresleni, &point->souradnice);
	SDL_RenderPresent(vykresleni);
}

static void smazUkazatel(ukazatel *point, SDL_Renderer *vykresleni)
{
	SDL_SetRenderDrawColor(vykresleni, 0, 0, 0, 0);
	SDL_RenderFillRect(vykresleni, &point->souradnice);
	SDL_RenderPresent(vykresleni);
}

/***************************** OBTIZNOST ************************************/

static void nastavObtiznost(urovneObtiznosti urovenX, obtiznost *menenaObtiznost)
{
	switch (urovenX)
	{
	case lehka:
		menenaObtiznost->sirkaPlosiny = 80;
		menenaObtiznost->zivoty = 6;
		break;
	case stredni:
		menenaObtiznost->sirkaPlosiny = 60;
		menenaObtiznost->zivoty = 4;
		break;
	case tezka:
		menenaObtiznost->sirkaPlosiny = 40;
		menenaObtiznost->zivoty = 2;
		break;
	default:
		exit(2);
		break;
	}
}

static obtiznost *vytvorObtiznost(urovneObtiznosti urovenX)
{
	obtiznost *vytvorenaObtiznost = (obtiznost *)malloc(sizeof(obtiznost));
	if (vytvorenaObtiznost == NULL)
	{
		exit(1);
	}

	nastavObtiznost(urovenX, vytvorenaObtiznost);

	return vytvorenaObtiznost;
}

static void uvolniObtiznost(obtiznost *mazanaObtiznost)
{
	free(mazanaObtiznost);
	mazanaObtiznost = NULL;
}
