#include "breakout.h"

/*
vykrestli
posun balonek
vyhodnot kolize - zmena rychlostX a rychlostY
pokud je to nutne - proved upravy hry - ???
*/
void breakout(obtiznost *obtiznostVar, SDL_Renderer *vykresleni)
{
    int pocetBloku = 50;
    printf("Game start...\n");

    blok *herniBloky = vytvorPoleBloku(pocetBloku);
    hrac *hracVar = vytvorHrace(obtiznostVar->zivoty);
    balonek *balonekVar = vytvorBalonek(start_x_balonek, start_y_balonek, startXRychlost(), startYRychlost());
    plosinka *plosinkaVar = vytvorPlosinku(190, 570, zakladni_posunuti, obtiznostVar->sirkaPlosiny);

    interval cyklusCas = nastvavInterval(55);
    bool odejit = false;

    vykresliVsechnnyBloky(herniBloky, pocetBloku, vykresleni);
    vykresliPlosinku(*plosinkaVar, vykresleni);
    vykresliBalonek(*balonekVar, vykresleni);
    aktualizujInfoHrace(hracVar, vykresleni);

    while (odejit == false)
    {
        if (prekrocilCas(&cyklusCas) == true)
        {
            kontrolaKolizi(balonekVar, plosinkaVar, hracVar, herniBloky, pocetBloku, vykresleni);
            odejit = kontrolaHry(hracVar, herniBloky, pocetBloku, vykresleni);
            if (odejit == true)
            {
                break;
            }

            odejit = ovladani(plosinkaVar, vykresleni);

            smazBalonek(*balonekVar, vykresleni);
            posunBalonek(balonekVar);
            vykresliBalonek(*balonekVar, vykresleni);
        }
    }

    uvolniPlosinku(plosinkaVar);
    uvolniBalonek(balonekVar);
    uvolniHrace(hracVar);
    uvolniVsechnyBloky(herniBloky);

    smazObrazovku(vykresleni);
}

static bool ovladani(plosinka *plosinkaVar, SDL_Renderer *vykresleni)
{
    bool odejit = false;
    SDL_Event udalost;

    SDL_PollEvent(&udalost);
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_RIGHT])
    {
        smazPlosinku(*plosinkaVar, vykresleni);
        posunPlosinku(plosinkaVar->posunutiPlosinky, plosinkaVar);
        vykresliPlosinku(*plosinkaVar, vykresleni);
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        smazPlosinku(*plosinkaVar, vykresleni);
        posunPlosinku(plosinkaVar->posunutiPlosinky * (-1), plosinkaVar);
        vykresliPlosinku(*plosinkaVar, vykresleni);
    }
    if (state[SDL_SCANCODE_ESCAPE])
    {
        odejit = true;
    }

    return odejit;
}

/*****************************************************************/

SDL_Color nastvavBarvu(int r, int g, int b)
{
    SDL_Color barva;

    barva.r = r;
    barva.g = g;
    barva.b = b;
    barva.a = 255;

    return barva;
}

SDL_Rect nastvavSouradnice(int x, int y, int w, int h)
{
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}

/******************************* BLOKY **********************************/

static void nastavBlok(int x, int y, bool aktivita, SDL_Color barva, blok *blokX)
{
    blokX->barva = barva;
    blokX->aktivni = aktivita;
    blokX->souradnice.x = x;
    blokX->souradnice.y = y;
    blokX->souradnice.h = vyska_bloku;
    blokX->souradnice.w = sirka_bloku;
}

static blok *vytvorPoleBloku(int pocet)
{
    blok *tmpBloky = (blok *)malloc(pocet * sizeof(blok));
    kontrola((void *)tmpBloky, "Nastala chyba, pri konstruovani bloku\n");

    int i;
    int tmpX = 0;
    int tmpY = (vyska_bloku + 1) * 3;
    SDL_Color tmpBarva = nastvavBarvu(nahodneCislo(0, 255), nahodneCislo(0, 255), nahodneCislo(0, 255));
    int delitel = 10;
    for (i = 0; i < pocet; i++)
    {
        nastavBlok(tmpX, tmpY, true, tmpBarva, tmpBloky);
        tmpX += sirka_bloku;

        if (((i + 1) % delitel) == 0)
        {
            tmpBarva = nastvavBarvu(nahodneCislo(0, 255), nahodneCislo(0, 255), nahodneCislo(0, 255));
            tmpY += vyska_bloku + 1;
            tmpX = 0;
        }

        tmpBloky++;
    }
    tmpBloky -= pocet;

    return tmpBloky;
}

static int pocetAktivnichBloku(blok *bloky, int pocetVsechBloku)
{
    int i;
    int pocet = 0;
    for (i = 0; i < pocetVsechBloku; i++)
    {
        if (bloky[i].aktivni == true)
        {
            pocet++;
        }
    }

    return pocet;
}

static void uvolniVsechnyBloky(blok *bloky)
{
    free(bloky);
    bloky = NULL;
}

/****************************** PLO�INA ***********************************/

static void nastavPlosinku(int x, int y, int delka, int posunuti, plosinka *pl)
{
    pl->souradnice.x = x;
    pl->souradnice.y = y;
    pl->souradnice.w = delka;
    pl->souradnice.h = vyska_plosinky;

    pl->posunutiPlosinky = posunuti;

    pl->barva = nastvavBarvu(255, 255, 255);
}

static void posunPlosinku(int posunO, plosinka *pl)
{
    if ((pl->souradnice.x + pl->souradnice.w + posunO) > sirka_d)
    {
        pl->souradnice.x = sirka_d - pl->souradnice.w;
    }
    else if ((pl->souradnice.x + posunO) < 0)
    {
        pl->souradnice.x = 0;
    }
    else
    {
        pl->souradnice.x += posunO;
    }
}

static plosinka *vytvorPlosinku(int x, int y, int posunuti, int delka)
{
    plosinka *tmp = (plosinka *)malloc(sizeof(plosinka));
    kontrola((void *)tmp, "Nastala chyba, pri konstruovani plosinky\n");

    nastavPlosinku(x, y, delka, posunuti, tmp);

    return tmp;
}

static void uvolniPlosinku(plosinka *pl)
{
    free(pl);
    pl = NULL;
}

/***************************** HRAC ************************************/

static void zapisDoHrace(int zivoty, int body, hrac *player)
{
    player->zivoty = zivoty;
    player->body = body;
}

static void prictiBody(hrac *player)
{
    zapisDoHrace(player->zivoty, player->body + prictene_body, player);
}

static void odectiZivot(hrac *player)
{
    zapisDoHrace(player->zivoty - 1, player->body, player);
}

static hrac *vytvorHrace(int zivoty)
{
    hrac *player = (hrac *)malloc(sizeof(hrac));
    kontrola((void *)player, "Chyba pri konstrukci hrace!\n");

    zapisDoHrace(zivoty, 0, player);

    return player;
}

static void uvolniHrace(hrac *player)
{
    free(player);
    player = NULL;
}

/***************************** VYHODNCENI HRY ************************************/

static void zadneZivotyHlaseni(SDL_Renderer *vykresleni)
{
    smazObrazovku(vykresleni);

    int x = 10;
    vypisText(x, 20, "Prohral jsi.", vykresleni);
    vypisText(x, 80, "Dosly ti zivoty.", vykresleni);

    pockejNaStiskKlavesy();
}

static void zadneKostkyHlaseni(SDL_Renderer *vykresleni, int body)
{
    smazObrazovku(vykresleni);

    int x = 20;
    vypisText(x, 20, "Vyhral jsi.", vykresleni);
    vypisText(x, 65, "Kostky zniceny", vykresleni);
    vypisText(x, 110, "Pocet bodu:", vykresleni);

    char bodyStr[10];
    intToString(bodyStr, 10, body);
    vypisText(x, 150, bodyStr, vykresleni);

    pockejNaStiskKlavesy();
}

static bool kontrolaHry(hrac *player, blok *bloky, int pocetBloku, SDL_Renderer *vykresleni)
{
    bool konec = false;
    if (pocetAktivnichBloku(bloky, pocetBloku) <= 0)
    {
        zadneKostkyHlaseni(vykresleni, player->body);
        konec = true;
    }
    if (player->zivoty <= 0)
    {
        zadneZivotyHlaseni(vykresleni);
        konec = true;
    }

    return konec;
}

/***************************** BALÓNEK ************************************/

static int startXRychlost()
{
    return nahodneCisloBez(strana_balonku * (-1) + 1, strana_balonku - 1, 0);
}

static int startYRychlost()
{
    return nahodneCisloBez(strana_balonku * (-1), -4, 0);
}

static void nastavBalonek(int x, int y, int rychlostX, int rychlostY, balonek *ball)
{
    ball->souradnice.x = x;
    ball->souradnice.y = y;
    ball->souradnice.h = strana_balonku;
    ball->souradnice.w = strana_balonku;

    ball->rychlostX = rychlostX;
    ball->rychlostY = rychlostY;

    ball->barva = nastvavBarvu(255, 255, 255);
}

/**********/
static void doluBalonek(balonek *ball)
{
    ball->rychlostY = abs(ball->rychlostY);
}

static void nahoruBalonek(balonek *ball)
{
    ball->rychlostY = abs(ball->rychlostY) * (-1);
}

static void doLevaBalonek(balonek *ball)
{
    ball->rychlostX = abs(ball->rychlostX) * (-1);
}

static void doPravaBalonek(balonek *ball)
{
    ball->rychlostX = abs(ball->rychlostX);
}

static void negaceXBalonek(balonek *ball)
{
    ball->rychlostX = ball->rychlostX * (-1);
}

static void negaceYBalonek(balonek *ball)
{
    ball->rychlostY = ball->rychlostY * (-1);
}
/**********/

static void posunBalonek(balonek *ball)
{
    ball->souradnice.x += ball->rychlostX;
    ball->souradnice.y += ball->rychlostY;
}

static balonek *vytvorBalonek(int x, int y, int rychlostX, int rychlostY)
{
    balonek *tmp = (balonek *)malloc(sizeof(balonek));
    kontrola((void *)tmp, "Chyba pri kontrukci balonku!\n");

    nastavBalonek(x, y, rychlostX, rychlostY, tmp);

    return tmp;
}

static void uvolniBalonek(balonek *ball)
{
    free(ball);
    ball = NULL;
}

/****************************** KOLIZE ***********************************/

static void kontrolaKolizi(balonek *ball, plosinka *plosinkaVar, hrac *player, blok *bloky, int pocetBloku, SDL_Renderer *vykresleni)
{
    dokresleni tmp;

    kolizeSeStenami(ball, player, vykresleni);
    tmp = kolizeSBloky(ball, player, bloky, pocetBloku, vykresleni);
    vykresliObjekt(tmp, vykresleni);
    tmp = kolizeSPlosinkou(ball, plosinkaVar, vykresleni);
    // vykresliObjekt(tmp, vykresleni);
}

static dokresleni kolizeSeStenami(balonek *ball, hrac *player, SDL_Renderer *vykresleni)
{
    dokresleni x = {nastvavBarvu(0, 0, 0), nastvavSouradnice(0, 0, 0, 0)};
    if (ball->souradnice.x <= min_x)
    {
        doPravaBalonek(ball);
    }
    if (ball->souradnice.x >= max_x)
    {
        doLevaBalonek(ball);
    }
    if (ball->souradnice.y <= min_y)
    {
        doluBalonek(ball);
    }
    if (ball->souradnice.y >= max_y)
    {
        odectiZivot(player);
        nastavBalonek(start_x_balonek, start_y_balonek, startXRychlost(), startYRychlost(), ball);
        aktualizujInfoHrace(player, vykresleni);
    }

    return x;
}

static dokresleni kolizeSBloky(balonek *ball, hrac *player, blok *bloky, int pocetBloku, SDL_Renderer *vykresleni)
{
    SDL_Rect stycnaPlocha;
    dokresleni mazaneBloky;
    mazaneBloky.barva = nastvavBarvu(0, 0, 0);
    mazaneBloky.souradnice = nastvavSouradnice(0, 0, 0, 0);

    bool stretliSe = false;
    int i;
    for (i = 0; i < pocetBloku; i++)
    {
        stretliSe = SDL_IntersectRect(&ball->souradnice, &bloky->souradnice, &stycnaPlocha);
        if ((stretliSe == true) && (bloky->aktivni == true))
        {
            mazaneBloky.souradnice = bloky->souradnice;
            bloky->aktivni = false;
            prictiBody(player);
            aktualizujInfoHrace(player, vykresleni);
            mistoKolizeFce(ball, stycnaPlocha);
            break;
        }
        bloky++;
    }
    bloky -= i;

    return mazaneBloky;
}

static void mistoKolizeFce(balonek *ball, SDL_Rect mistoStretu)
{
    if (mistoStretu.h > mistoStretu.w)
    {
        negaceXBalonek(ball);
    }
    else
    {
        negaceYBalonek(ball);
    }
}

static dokresleni kolizeSPlosinkou(balonek *ball, plosinka *plosinkaVar, SDL_Renderer *vykresleni)
{
    dokresleni dokresleniPlosinky;
    dokresleniPlosinky.barva = nastvavBarvu(255, 255, 255);
    dokresleniPlosinky.souradnice = nastvavSouradnice(0, 0, 0, 0);

    SDL_Rect stycnaPlocha;
    bool stretliSe = SDL_IntersectRect(&ball->souradnice, &plosinkaVar->souradnice, &stycnaPlocha);

    if (stretliSe == true)
    {
        nahoruBalonek(ball);
        dokresleniPlosinky.souradnice = stycnaPlocha;
    }

    return dokresleniPlosinky;
}

/*****************************************************************/

static void aktualizujInfoHrace(hrac *player, SDL_Renderer *vykresleni)
{
    dokresleni objekt;
    objekt.barva = nastvavBarvu(0, 0, 0);
    objekt.souradnice = nastvavSouradnice(0, 0, sirka_d, min_y - 1);
    vykresliObjekt(objekt, vykresleni);

    objekt.barva = nastvavBarvu(255, 255, 255);
    objekt.souradnice = nastvavSouradnice(min_x, min_y - strana_balonku, sirka_d, 1);
    vykresliObjekt(objekt, vykresleni);

    char zivotyStr[3];
    intToString(zivotyStr, 3, player->zivoty);
    vypisText(75, 5, zivotyStr, vykresleni);

    char bodyStr[10];
    intToString(bodyStr, 10, player->body);
    vypisText(250, 5, bodyStr, vykresleni);
}

static void intToString(char *const retezec, const int delka, int cislo)
{
#ifdef _WIN32
    sprintf_s(retezec, delka, "%d", cislo);
#else
    sprintf(retezec, "%d", cislo);
#endif
}