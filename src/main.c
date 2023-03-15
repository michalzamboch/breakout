#include "include.h"

extern void menu(SDL_Renderer *vykresleni);

int nahodneCislo(int from, int to);
void kontrola(void *soubor, char report[]);
void pockejNaStiskKlavesy();
bool prekrocilCas(interval *porovnavany);
interval nastvavInterval(unsigned int jakDlouho);

int main(int argc, char *args[])
{
    srand((unsigned int)time(NULL));

    SDL_Window *okno = NULL;
    SDL_Renderer *vykresleni = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL se nemohlo inicializovat! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        okno = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sirka_d, vyska_d, SDL_WINDOW_SHOWN);
        if (okno == NULL)
        {
            printf("Chyba! SDL_Error: %s\n", SDL_GetError());
            exit(1);
        }
        else
        {
            vykresleni = SDL_CreateRenderer(okno, -1, 0);
        }
    }

    if (TTF_Init() == -1)
    {
        printf("Nastala chyba pri inicializaci pisma...\n");
        getchar();
        exit(-1);
    }

    /*****/

    menu(vykresleni);

    /*****/

    if (vykresleni)
    {
        SDL_DestroyRenderer(vykresleni);
    }
    if (okno)
    {
        SDL_DestroyWindow(okno);
    }
    TTF_Quit();
    SDL_Quit();

    return 0;
}

/************************** DOPL�KOV� FUNKCE **********************************/

void kontrola(void *soubor, char report[])
{
    if (soubor == NULL)
    {
        printf("%s\n", report);
        getchar();
        exit(EXIT_FAILURE);
    }
}

int nahodneCislo(int from, int to)
{
    if (from > to)
    {
        int temp = from;
        from = to;
        to = temp;
    }

    from = abs(from);
    int generovaneCislo = rand() % (from + to + 1);
    generovaneCislo -= from;

    return generovaneCislo;
}

int nahodneCisloBez(int from, int to, int zakazneCislo)
{
    int genrovaneCislo = 0;

    do
    {
        genrovaneCislo = nahodneCislo(from, to);
    } while (genrovaneCislo == zakazneCislo);

    return genrovaneCislo;
}

void pockejNaStiskKlavesy()
{
    SDL_Event udalost;
    bool odejit = false;
    interval cyklusCas = nastvavInterval(50);

    while (odejit == false)
    {
        SDL_WaitEvent(&udalost);
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        if (prekrocilCas(&cyklusCas) == true)
        {
            if (state[SDL_SCANCODE_RETURN])
            {
                odejit = true;
            }
        }
    }
}

/*******************************************************/

bool prekrocilCas(interval *porovnavany)
{
    if ((SDL_GetTicks() - porovnavany->soucasnaHodnota) > porovnavany->interval)
    {
        porovnavany->soucasnaHodnota = SDL_GetTicks();
        return true;
    }
    else
    {
        return false;
    }
}

interval nastvavInterval(unsigned int jakDlouho)
{
    interval tmp;
    tmp.interval = jakDlouho;
    tmp.soucasnaHodnota = SDL_GetTicks();

    return tmp;
}