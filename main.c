#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <SDL.h>

#include "moves.h"
#include "checks.h"
#include "tools.h"
#include "graphic.h"
#include "board.h"



int played;
int main( int argc, char * argv[] )
{
    int move_initialized=0; // si le mouvement est initialisé (1) ou non (0)
    int couleur=BLANCHE; //les blancs commencent
    int k=1; // 1 : tour du blanc, 0 : tour du joueur noir

    // declaration et allocation de mémoire

    Point **Poi = (Point **) malloc(DIM_PLAT*sizeof(Point *)); // tableau d'intervalles de pixels
    piece **A=(piece **) malloc(DIM_PLAT*sizeof(piece *)); // tableau qui représente le plateau de jeu
    position *Tab = (position *) malloc(SIZE_TAB*sizeof(position));; // tableau de positions qui va contenir

    // allocation de memoire pour les sous-tableaux

    for (int i=0;i<DIM_PLAT;i++) Poi[i]=(Point *) malloc(DIM_PLAT*sizeof(Point));
    for (int i=0;i<DIM_PLAT;i++) A[i]=(piece *) malloc(DIM_PLAT*sizeof(piece));

    // initialisation de chaque tableau

    RemplirPoint(Poi);
    initialplateau(A);
    FlushTab(&Tab);
    affichage(A);
    printf("\n");

    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect rect;
    SDL_Texture **F;
    F = (SDL_Texture**) malloc(10*sizeof(SDL_Texture*));

    if (SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        SDL_ExitErreur("Initialisation SDL");
    }
    if ((window=SDL_CreateWindow("Bulltricker",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARG_FENETRE,HAUT_FENETRE,SDL_WINDOW_SHOWN))==NULL)
    {
        SDL_ExitErreur("Creation de la fenetre");
    }
    if ((render=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED))==NULL)
    {
        SDL_ExitErreur("Creation du renderer");
    }
    // affichage de menu
    texture=CreateTexture(MENU,render);
    SDL_ChargementTexture(window,render,texture,&rect);
    SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);
    SDL_RenderPresent(render);

    // remplissage du tableau de texture

    InitialiseTableauTexture(F,render);

    ///------------------- Gestion des evenements ----------------/

    SDL_bool program_launched = SDL_TRUE;
    int start = 1; // 1 pour page menu 0 pour le jeu -1 else
    int credits = 0; // 1 si l'user dans la page credit 0 sinon
    int win = 0; // si l'user dans la page de WIN 1 oui / 0 non
    int lost_player;
    movement *moves=(movement *) malloc(sizeof(movement));
    piece *playedpiece=(piece *) malloc(sizeof(piece));
    while(program_launched)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN :
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {

                        if(start == 1)
                        {

                            if(event.button.x<495 && event.button.x>126 && event.button.y<300 && event.button.y>215)
                            {
                                //tester si l'user click sur nouvelle partie
                                //pour cree board et initialiser les pieces
                                texture=CreateTexture(BOARD,render);
                                SDL_ChargementTexture(window,render,texture,&rect);
                                SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);

                                display(A,render,&rect,Poi,window,F);
                                start = 0;
                            }
                            if(event.button.x<437 && event.button.x>198 && event.button.y<618 && event.button.y>572) // l'user click sur exit
                            {
                                program_launched = SDL_FALSE;
                            }
                            if(event.button.x<514 && event.button.x>153 && event.button.y<521 && event.button.y>441) // user click sur credits
                            {

                                texture=CreateTexture(CREDITS,render);
                                SDL_ChargementTexture(window,render,texture,&rect);
                                SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);
                                credits = 1;
                            }
                            if(credits == 1 && event.button.x<90 && event.button.x>-1 && event.button.y<90 && event.button.y>-1)
                            {
                                texture=CreateTexture(MENU,render);
                                SDL_ChargementTexture(window,render,texture,&rect);
                                SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);
                                credits = 0;
                                start = 1;
                            }
                            SDL_RenderPresent(render);
                        }
                        else if(start == 0)
                        {
                            if(event.button.x<45 && event.button.x>-1 && event.button.y<27 && event.button.y>-1)
                            {
                                //user clic sur button retour dans le jeu
                                texture=CreateTexture(MENU,render);
                                SDL_ChargementTexture(window,render,texture,&rect);
                                SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);
                                start = 1;
                            }
                            if(event.button.x<89 && event.button.x>57 && event.button.y<33 && event.button.y>-1)
                            {
                                // user clic sur sauvgarder

                            }
                            SDL_RenderPresent(render);
                            if(start == 0)
                            {
                                printf("(%d , %d )\n",event.button.x,event.button.y);
                                // stocker les indices du piece a jouer apres 1er click
                                RemplirTab(A,couleur,&Tab);
                                play(A,Tab,moves,playedpiece,event.button,&move_initialized,couleur );
                                if (played == 1)
                                {
                                    if (k%2==1) k=0;
                                    else k=1;

                                    played=0;
                                    FlushTab(&Tab);
                                    couleur = (k%2==1) ? BLANCHE : NOIRE; //determination de la couleur du joueur, si k impair,tour du blanc sinon tour du noir.

                                }
                                affichage(A);
                                texture=CreateTexture(BOARD,render);
                                SDL_ChargementTexture(window,render,texture,&rect);
                                SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);
                                display(A,render,&rect,Poi,window,F);
                                continue;
                            }

                        }
                        else if(start == -1)
                        {
                            if(win == 1)
                            {
                                if(event.button.x<121 && event.button.x>-1 && event.button.y<87 && event.button.y>-1)
                                {
                                    initialplateau(A);
                                    texture=CreateTexture(BOARD,render);
                                    SDL_ChargementTexture(window,render,texture,&rect);
                                    SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);
                                    display(A,render,&rect,Poi,window,F);
                                    start = 0;
                                    win = 0;
                                }
                            }
                        }
                    SDL_RenderPresent(render);
                    }
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE : //exit si l'user click sur echap
                            program_launched = SDL_FALSE;
                            break;
                        case SDLK_a :
                            printf("vous avez tapez A\n");
                            continue;
                        default : continue;
                    }
                case SDL_QUIT :
                    program_launched = SDL_FALSE;
                    break;
                default :
                    break;

            }
            SDL_RenderPresent(render);//mise a jour de rendu
            if(CheckMat(A,&lost_player) == 0)
            {
                int winner = (lost_player == NOIRE) ? BLANCHE : NOIRE; //on récupère la couleur du joueur
                switch(winner)
                {
                    case NOIRE:
                        texture=CreateTexture("images/Black_win.bmp",render);
                        SDL_ChargementTexture(window,render,texture,&rect);
                        SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);
                        win = 1;
                        start = -1;
                        SDL_RenderPresent(render);//mise a jour de rendu
                        break;
                    case BLANCHE:
                    texture=CreateTexture("images/White_win.bmp",render);
                    SDL_ChargementTexture(window,render,texture,&rect);
                    SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);
                    win = 1;
                    start = -1;
                    SDL_RenderPresent(render);//mise a jour de rendu
                    break;
                }
            }
        }
    }
    //------------------ Fermeture ----------------/

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return EXIT_SUCCESS;
}
