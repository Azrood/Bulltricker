#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <SDL.h>
#include "moves.h"
#include "checks.h"
#include "tools.h"
#include "graphic.h"


void SDL_DestroywindowEtrender(SDL_Window *window,SDL_Renderer *render)
{
    if(window)
        SDL_DestroyWindow(window);
    if(render)
        SDL_DestroyRenderer(render);
    return;
}

void SDL_ExitErreur(char * messageErreur)
{
    SDL_Log("Erreur %s : %s\n",messageErreur,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

SDL_Texture * CreateTexture(const char * text,SDL_Renderer *render)
{
	SDL_Surface *background =SDL_LoadBMP(text);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(render, background);
	SDL_FreeSurface(background);
	return texture;
}

void SDL_ChargementTexture(SDL_Window * window,SDL_Renderer* render ,SDL_Texture * texture,SDL_Rect *rect)
{
    if((SDL_QueryTexture(texture,NULL,NULL,&rect->w,&rect->h))!=0)
    {
        SDL_DestroywindowEtrender(window,render);//pour detruire la window et le renderer
        SDL_DestroyTexture(texture);//pour detruire l texture
        SDL_ExitErreur("Chargement texture");//afficher le message d'erreur e quitter SDL avec SDL_QUIT;
    }
}

void SDL_AfficherTexture(SDL_Window * window,SDL_Renderer* render ,SDL_Texture * texture,SDL_Rect *rect,int x,int y)
{
    rect->x=x;
    rect->y=y;
    if((SDL_RenderCopy(render,texture,NULL,rect))!=0)
    {
        SDL_DestroywindowEtrender(window,render);
        SDL_DestroyTexture(texture);
        SDL_ExitErreur("Affichage de l'image");
    }
}