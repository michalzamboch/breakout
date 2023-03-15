#include "include.h"

extern SDL_Color nastvavBarvu(int r, int g, int b);

void vykresliJedenBlok(blok *bx, SDL_Renderer *vykresleni);
void vykresliVsechnnyBloky(blok *bx, int pocet, SDL_Renderer *vykresleni);
void smazJedenBlok(blok *bx, SDL_Renderer *vykresleni);

void vykresliPlosinku(plosinka pl, SDL_Renderer *vykresleni);
void smazPlosinku(plosinka pl, SDL_Renderer *vykresleni);

void vykresliBalonek(balonek ball, SDL_Renderer *vykresleni);
void smazBalonek(balonek ball, SDL_Renderer *vykresleni);

void vypisText(int x, int y, char *text, SDL_Renderer *vykresleni);

/*****************************************************************/

void vykresliJedenBlok(blok *bx, SDL_Renderer *vykresleni)
{
    /*bx->aktivni = true;*/
    SDL_SetRenderDrawColor(vykresleni, bx->barva.r, bx->barva.g, bx->barva.b, bx->barva.a);
    SDL_RenderFillRect(vykresleni, &bx->souradnice);
    SDL_RenderPresent(vykresleni);
}

void vykresliVsechnnyBloky(blok *bx, int pocet, SDL_Renderer *vykresleni)
{
    int i;
    for (i = 0; i < pocet; i++)
    {
        vykresliJedenBlok(bx, vykresleni);
        bx++;
    }
    bx -= pocet;
}

void smazJedenBlok(blok *bx, SDL_Renderer *vykresleni)
{
    bx->aktivni = false;
    SDL_SetRenderDrawColor(vykresleni, 0, 0, 0, 0);
    SDL_RenderFillRect(vykresleni, &bx->souradnice);
    SDL_RenderPresent(vykresleni);
}

/*****************************************************************/

void vykresliPlosinku(plosinka pl, SDL_Renderer *vykresleni)
{
    SDL_SetRenderDrawColor(vykresleni, pl.barva.r, pl.barva.g, pl.barva.b, pl.barva.a);
    SDL_RenderFillRect(vykresleni, &pl.souradnice);
    SDL_RenderPresent(vykresleni);
}

void smazPlosinku(plosinka pl, SDL_Renderer *vykresleni)
{
    SDL_SetRenderDrawColor(vykresleni, 0, 0, 0, 0);
    SDL_RenderFillRect(vykresleni, &pl.souradnice);
    SDL_RenderPresent(vykresleni);
}

/*****************************************************************/

void vykresliBalonek(balonek ball, SDL_Renderer *vykresleni)
{
    SDL_SetRenderDrawColor(vykresleni, ball.barva.r, ball.barva.g, ball.barva.b, ball.barva.a);
    SDL_RenderFillRect(vykresleni, &ball.souradnice);
    SDL_RenderPresent(vykresleni);
}

void smazBalonek(balonek ball, SDL_Renderer *vykresleni)
{
    SDL_SetRenderDrawColor(vykresleni, 0, 0, 0, 0);
    SDL_RenderFillRect(vykresleni, &ball.souradnice);
    SDL_RenderPresent(vykresleni);
}

/*****************************************************************/

void vypisText(int x, int y, char *text, SDL_Renderer *vykresleni)
{
    TTF_Font *Sans = TTF_OpenFont("fonts/OpenSans-Semibold.ttf", 30);
    if (Sans == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        getchar();
        exit(-5);
    }

    SDL_Color White = nastvavBarvu(255, 255, 255);
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, text, White);

    SDL_Texture *Message = SDL_CreateTextureFromSurface(vykresleni, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = x;
    Message_rect.y = y;
    Message_rect.h = 40;
    Message_rect.w = strlen(text) * 20;

    SDL_RenderCopy(vykresleni, Message, NULL, &Message_rect);
    SDL_RenderPresent(vykresleni);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

/*****************************************************************/

void smazObrazovku(SDL_Renderer *vykresleni)
{
    SDL_SetRenderDrawColor(vykresleni, 0, 0, 0, 0);
    SDL_RenderClear(vykresleni);
    SDL_RenderPresent(vykresleni);
}

void vykresliObjekt(dokresleni objekt, SDL_Renderer *vykresleni)
{
    SDL_SetRenderDrawColor(vykresleni, objekt.barva.r, objekt.barva.g, objekt.barva.b, objekt.barva.a);
    SDL_RenderFillRect(vykresleni, &objekt.souradnice);
    SDL_RenderPresent(vykresleni);
}