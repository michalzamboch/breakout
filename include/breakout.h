#include "include.h"

extern void kontrola(void *soubor, char report[]);
extern int nahodneCislo(int from, int to);
extern void pockejNaStiskKlavesy();
extern bool prekrocilCas(interval *porovnavany);
extern interval nastvavInterval(unsigned int jakDlouho);
extern int nahodneCisloBez(int from, int to, int zakazneCislo);

/*****************************************************************/

extern void vykresliJedenBlok(blok *bx, SDL_Renderer *vykresleni);
extern void vykresliVsechnnyBloky(blok *bx, int pocet, SDL_Renderer *vykresleni);
extern void smazJedenBlok(blok *bx, SDL_Renderer *vykresleni);

extern void vykresliPlosinku(plosinka pl, SDL_Renderer *vykresleni);
extern void smazPlosinku(plosinka pl, SDL_Renderer *vykresleni);

extern void vykresliBalonek(balonek ball, SDL_Renderer *vykresleni);
extern void smazBalonek(balonek ball, SDL_Renderer *vykresleni);

extern void vypisText(int x, int y, char *text, SDL_Renderer *vykresleni);

extern void smazObrazovku(SDL_Renderer *vykresleni);
extern void vykresliObjekt(dokresleni objekt, SDL_Renderer *vykresleni);

/*****************************************************************/

static bool ovladani(plosinka *plosinkaVar, SDL_Renderer *vykresleni);

static balonek *vytvorBalonek(int x, int y, int rychlostX, int rychlostY);
static void posunBalonek(balonek *ball);
static void doluBalonek(balonek *ball);
static void nahoruBalonek(balonek *ball);
static void doLevaBalonek(balonek *ball);
static void doPravaBalonek(balonek *ball);
static void nastavBalonek(int x, int y, int rychlostX, int rychlostY, balonek *ball);
static void uvolniBalonek(balonek *ball);

static int startXRychlost();
static int startYRychlost();

static hrac *vytvorHrace(int zivoty);
static void zapisDoHrace(int zivoty, int body, hrac *player);
static void prictiBody(hrac *player);
static void odectiZivot(hrac *player);
static void uvolniHrace(hrac *player);

static void zadneZivotyHlaseni(SDL_Renderer *vykresleni);
static void zadneKostkyHlaseni(SDL_Renderer *vykresleni, int body);
static bool kontrolaHry(hrac *player, blok *bloky, int pocetBloku, SDL_Renderer *vykresleni);

static plosinka *vytvorPlosinku(int x, int y, int posunuti, int delka);
static void nastavPlosinku(int x, int y, int delka, int posunuti, plosinka *pl);
static void posunPlosinku(int posunO, plosinka *pl);
static void uvolniPlosinku(plosinka *pl);

static blok *vytvorPoleBloku(int pocet);
static void nastavBlok(int x, int y, bool aktivita, SDL_Color barva, blok *blokX);
static void uvolniVsechnyBloky(blok *bloky);
static int pocetAktivnichBloku(blok *bloky, int pocetVsechBloku);

static void kontrolaKolizi(balonek *ball, plosinka *plosinkaVar, hrac *player, blok *bloky, int pocetBloku, SDL_Renderer *vykresleni);
static dokresleni kolizeSeStenami(balonek *ball, hrac *player, SDL_Renderer *vykresleni);
static dokresleni kolizeSBloky(balonek *ball, hrac *player, blok *bloky, int pocetBloku, SDL_Renderer *vykresleni);
static void mistoKolizeFce(balonek *ball, SDL_Rect mistoStretu);
static dokresleni kolizeSPlosinkou(balonek *ball, plosinka *plosinkaVar, SDL_Renderer *vykresleni);

static void aktualizujInfoHrace(hrac *player, SDL_Renderer *vykresleni);

SDL_Color nastvavBarvu(int r, int g, int b);
SDL_Rect nastvavSouradnice(int x, int y, int w, int h);

/*****************************************************************/

void breakout(obtiznost *obtiznostVar, SDL_Renderer *vykresleni);

/*****************************************************************/