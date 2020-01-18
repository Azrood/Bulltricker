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
void display(piece **A,SDL_Renderer* render,SDL_Rect *rect,Point **Poi,SDL_Window *window,SDL_Texture **F)
{
    for(int i=0; i<DIM_PLAT ; i++)
    {
        for(int j=0 ; j<DIM_PLAT ; j++)
        {
            if(A[i][j].type != VIDE)
            {
                if(i%2 == 0 && j%2 == 1)//piece horizontale
                {
                    if(A[i][j].type == PION) //CAS PION
                    {
                        if(A[i][j].color == BLANCHE) //BLANCHE
                        {
                            //texture=CreateTexture(PIONBH,render);
                            SDL_ChargementTexture(window,render,F[ind_PIONBH],rect);
                            SDL_AfficherTexture(window,render,F[ind_PIONBH],rect,Poi[i][j].x,Poi[i][j].y);
                        }else if(A[i][j].color == NOIRE) // NOIRE
                        {
                            //texture=CreateTexture(PIONNH,render);
                            SDL_ChargementTexture(window,render,F[ind_PIONNH],rect);
                            SDL_AfficherTexture(window,render,F[ind_PIONNH],rect,Poi[i][j].x,Poi[i][j].y);
                        }
                    }
                    else if(A[i][j].type == DAME) // CAS DAME
                    {
                        if(A[i][j].color == BLANCHE) // BLANCHE
                        {
                            //texture=CreateTexture(DAMEBH,render);
                            SDL_ChargementTexture(window,render,F[ind_DAMEBH],rect);
                            SDL_AfficherTexture(window,render,F[ind_DAMEBH],rect,Poi[i][j].x,Poi[i][j].y);
                        }else if(A[i][j].color == NOIRE) // NOIRE
                        {
                            //texture=CreateTexture(DAMENH,render);
                            SDL_ChargementTexture(window,render,F[ind_DAMENH],rect);
                            SDL_AfficherTexture(window,render,F[ind_DAMENH],rect,Poi[i][j].x,Poi[i][j].y);
                        }
                    }
                }
                else if(i%2 == 1 && j%2 == 0) //piece VERTICALE
                {
                    if(A[i][j].type == PION) //CAS PION
                    {
                        if(A[i][j].color == BLANCHE) //BLANCHE
                        {
                            //texture=CreateTexture(PIONBV,render);
                            SDL_ChargementTexture(window,render,F[ind_PIONBV],rect);
                            SDL_AfficherTexture(window,render,F[ind_PIONBV],rect,Poi[i][j].x,Poi[i][j].y);
                        }else if(A[i][j].color == NOIRE) // NOIRE
                        {
                            //texture=CreateTexture(PIONNV,render);
                            SDL_ChargementTexture(window,render,F[ind_PIONNV],rect);
                            SDL_AfficherTexture(window,render,F[ind_PIONNV],rect,Poi[i][j].x,Poi[i][j].y);
                        }
                    }
                    else if(A[i][j].type == DAME) // CAS DAME
                    {
                        if(A[i][j].color == BLANCHE) // BLANCHE
                        {
                            //texture=CreateTexture(DAMEBV,render);
                            SDL_ChargementTexture(window,render,F[ind_DAMEBV],rect);
                            SDL_AfficherTexture(window,render,F[ind_DAMEBV],rect,Poi[i][j].x,Poi[i][j].y);
                        }else if(A[i][j].color == NOIRE) // NOIRE
                        {
                            //texture=CreateTexture(DAMENV,render);
                            SDL_ChargementTexture(window,render,F[ind_DAMENV],rect);
                            SDL_AfficherTexture(window,render,F[ind_DAMENV],rect,Poi[i][j].x,Poi[i][j].y);
                        }
                    }
                }
                else if(i%2 == 1 && j%2 == 1) //piece VERTICALE
                {
                    if(A[i][j].type == ROI) //CAS PION
                    {
                        if(A[i][j].color == BLANCHE) //BLANCHE
                        {
                            //texture=CreateTexture(ROIB,render);
                            SDL_ChargementTexture(window,render,F[ind_ROIB],rect);
                            SDL_AfficherTexture(window,render,F[ind_ROIB],rect,Poi[i][j].x,Poi[i][j].y);
                        }else if(A[i][j].color == NOIRE) // NOIRE
                        {
                            //texture=CreateTexture(ROIN,render);
                            SDL_ChargementTexture(window,render,F[ind_ROIN],rect);
                            SDL_AfficherTexture(window,render,F[ind_ROIN],rect,Poi[i][j].x,Poi[i][j].y);
                        }
                    }
                }

            }


        }
    }
}
