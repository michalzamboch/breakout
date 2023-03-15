#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define vyska_d 600
#define sirka_d 400

#define strana_balonku 8
#define start_x_balonek 200
#define start_y_balonek 550

#define max_x (sirka_d - strana_balonku)
#define min_x 0
#define max_y vyska_d
#define min_y 60

#define vyska_bloku 30
#define sirka_bloku 40

#define vyska_plosinky 10
#define zakladni_posunuti 10

#define prictene_body 50

#define strana_ukazatele 10

#define radkovani 40

typedef struct
{
	SDL_Rect souradnice;
	SDL_Color barva;
	bool aktivni;
} blok;

typedef struct
{
	SDL_Rect souradnice;
	SDL_Color barva;
	int posunutiPlosinky;
} plosinka;

typedef enum
{
	up,
	down,
	right,
	left
} smer;

typedef struct
{
	int zivoty;
	int body;
} hrac;

typedef struct
{
	int sirkaPlosiny;
	int zivoty;
} obtiznost;

typedef enum
{
	lehka,
	stredni,
	tezka
} urovneObtiznosti;

typedef struct
{
	SDL_Color barva;
	SDL_Rect souradnice;
	int rychlostX;
	int rychlostY;
} balonek;

typedef enum
{
	nahore,
	dole,
	vpravo,
	vlevo
} mistoKolize;

typedef struct
{
	unsigned int interval;
	unsigned int soucasnaHodnota;
} interval;

typedef struct
{
	SDL_Rect souradnice;
	int pozice;
} ukazatel;

typedef struct
{
	SDL_Color barva;
	SDL_Rect souradnice;
} dokresleni;
