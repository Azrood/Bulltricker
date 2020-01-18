#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <strings.h>
#include "moves.h"
#include "checks.h"
#include "tools.h"
#include "graphic.h"

#define ind_DAMEBV 0
#define ind_DAMEBH 1
#define ind_PIONBV 2
#define ind_PIONBH 3
#define ind_ROIB   4
#define ind_DAMENV 5
#define ind_DAMENH 6
#define ind_PIONNV 7
#define ind_PIONNH 8
#define ind_ROIN   9

int played;

int main( int argc, char * argv[] )
{

    Point **Poi;
    Poi = (Point **) malloc(15*sizeof(Point *));
    for (int i=0;i<15;i++) Poi[i]=(Point *) malloc(15*sizeof(Point));
    RemplirPoint(Poi);
    int i;
    int lost_player;
    piece **A=(piece **)malloc(DIM_PLAT*sizeof(piece *));
    for(i=0;i<DIM_PLAT;i++){
        A[i]=(piece *)malloc(DIM_PLAT*sizeof(piece));
    }
    position *Tab;
    Tab = (position *)malloc(SIZE_TAB*sizeof(position));
    initialplateau(A);
    affichage(A);
    printf("\n");

    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect rect;
    int x=0, y=0;
    SDL_Texture **F;
    F = (SDL_Texture**) malloc(10*sizeof(SDL_Texture*));


    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        SDL_ExitErreur("Initialisation SDL");
    }
    if((window=SDL_CreateWindow("Bulltricker",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARG_FENETRE,HAUT_FENETRE,SDL_WINDOW_SHOWN))==NULL){
        SDL_ExitErreur("Creation de la fenetre");
    }
    if((render=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED))==NULL){
        SDL_ExitErreur("Creation du renderer");
    }
    // affichage de board
    texture=CreateTexture(MENU,render);
    SDL_ChargementTexture(window,render,texture,&rect);
    SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);

    SDL_RenderPresent(render);
    ///------------------- Gestion des evenements ----------------/
    SDL_bool program_lunched = SDL_TRUE;
    int start = 1; // 1 pour page menu 0 pour le jeu
    int credits = 0; // 1 si l'user dans la page credit 0 sinon
    while(program_lunched)
    {
        movement moves;
        piece playedpiece;
        char positionstr[10];
        fflush(stdin);
        FlushTab(&Tab);

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
                                F[ind_DAMENV]=CreateTexture(DAMENV,render);
                                SDL_ChargementTexture(window,render,F[ind_DAMENV],&rect);
                                x = 47; y = 67;
                                for(int i=0 ; i<8 ; i++)
                                {
                                    SDL_AfficherTexture(window,render,F[ind_DAMENV],&rect,x,y);
                                    x = x + 77;
                                }

                                // affichage des pions verticales noire
                                F[ind_PIONNV]=CreateTexture(PIONNV,render);
                                SDL_ChargementTexture(window,render,F[ind_PIONNV],&rect);
                                x = 47; y = 144;
                                for(int i=0 ; i<8 ; i++)
                                {
                                    SDL_AfficherTexture(window,render,F[ind_PIONNV],&rect,x,y);
                                    x = x + 77;
                                }

                                // affichage des pions horizontale noire
                                F[ind_PIONNH]=CreateTexture(PIONNH,render);
                                SDL_ChargementTexture(window,render,F[ind_PIONNH],&rect);
                                x = 68; y = 124;
                                for(int i=0 ; i<7 ; i++)
                                {
                                    SDL_AfficherTexture(window,render,F[ind_PIONNH],&rect,x,y);
                                    x = x + 77;
                                }
                                // affichage du roi noire
                                F[ind_ROIN]=CreateTexture(ROIN,render);
                                SDL_ChargementTexture(window,render,F[ind_ROIN],&rect);
                                SDL_AfficherTexture(window,render,F[ind_ROIN],&rect,308,78);


                                // affichage des dames blanche
                                F[ind_DAMEBV]=CreateTexture(DAMEBV,render);
                                SDL_ChargementTexture(window,render,F[ind_DAMEBV],&rect);
                                x = 47; y = 529;
                                for(int i=0 ; i<8 ; i++)
                                {
                                    SDL_AfficherTexture(window,render,F[ind_DAMEBV],&rect,x,y);
                                    x = x + 77;
                                }

                                // ************** charge PION BLANCHE VERTICALE
                                F[ind_PIONBV]=CreateTexture(PIONBV,render);
                                SDL_ChargementTexture(window,render,F[ind_PIONBV],&rect);
                                x = 47; y = 453;
                                for(int i=0 ; i<8 ; i++)
                                {
                                    SDL_AfficherTexture(window,render,F[ind_PIONBV],&rect,x,y);
                                    x = x + 77;
                                }

                                // ************** charge PION BLANCHE HORIZONTALE
                                F[ind_PIONBH]=CreateTexture(PIONBH,render);
                                SDL_ChargementTexture(window,render,F[ind_PIONBH],&rect);
                                x = 68; y = 509;
                                for(int i=0 ; i<7 ; i++)
                                {
                                    SDL_AfficherTexture(window,render,F[ind_PIONBH],&rect,x,y);
                                    x = x + 77;
                                }

                                // ************** charge ROI BLANCHE
                                F[ind_ROIB]=CreateTexture(ROIB,render);
                                SDL_ChargementTexture(window,render,F[ind_ROIB],&rect);
                                SDL_AfficherTexture(window,render,F[ind_ROIB],&rect,308,540);

                                start = 0;
                            }
                            if(event.button.x<437 && event.button.x>198 && event.button.y<618 && event.button.y>572) // l'user click sur exit
                            {
                                program_lunched = SDL_FALSE;
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
                        if(start == 0)
                        {
                            printf("(%d , %d )\n",event.button.x,event.button.y);
                            // stocker les indices du piece a jouer apres 1er click
                            strcpy(positionstr , SavoirLocationY(event.button.y));
                            strcat(positionstr , SavoirLocationX(event.button.x));
                            moves.initialmove = ConvertirLocation(positionstr);
                            playedpiece = A[moves.initialmove.line][moves.initialmove.column];
                            fflush(stdin);
                        }


                    }
                    if(event.button.button == SDL_BUTTON_RIGHT && start == 0)
                    {
                        // stocker les indices du position finale apres 2eme click
                        printf("(%d , %d )\n",event.button.x,event.button.y);
                        strcpy(positionstr , SavoirLocationY(event.button.y));
                        strcat(positionstr , SavoirLocationX(event.button.x));
                        moves.finalmove = ConvertirLocation(positionstr);
                        if(playedpiece.type == PION) MovePion(A,moves,playedpiece,Tab);
                        if(playedpiece.type == DAME) MoveDame(A,moves,playedpiece,Tab);
                        if(playedpiece.type == ROI) MoveKing(A,moves,playedpiece);
                        affichage(A);
                        //charger le board a nouveau
                        texture=CreateTexture(BOARD,render);
                        SDL_ChargementTexture(window,render,texture,&rect);
                        SDL_AfficherTexture(window,render,texture,&rect,(LARG_FENETRE-rect.w)/2,(HAUT_FENETRE-rect.h)/2);
                        //cette boucle test le type couleur position du piece(verticale ou horizontale)
                        //pour cree une texture avec la bonne position
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
                                                texture=CreateTexture(PIONBH,render);
                                                SDL_ChargementTexture(window,render,texture,&rect);
                                                SDL_AfficherTexture(window,render,texture,&rect,Poi[i][j].x,Poi[i][j].y);
                                            }else if(A[i][j].color == NOIRE) // NOIRE
                                            {
                                                texture=CreateTexture(PIONNH,render);
                                                SDL_ChargementTexture(window,render,texture,&rect);
                                                SDL_AfficherTexture(window,render,texture,&rect,Poi[i][j].x,Poi[i][j].y);
                                            }
                                        }
                                        else if(A[i][j].type == DAME) // CAS DAME
                                        {
                                            if(A[i][j].color == BLANCHE) // BLANCHE
                                            {
                                                texture=CreateTexture(DAMEBH,render);
                                                SDL_ChargementTexture(window,render,texture,&rect);
                                                SDL_AfficherTexture(window,render,texture,&rect,Poi[i][j].x,Poi[i][j].y);
                                            }else if(A[i][j].color == NOIRE) // NOIRE
                                            {
                                                texture=CreateTexture(DAMENH,render);
                                                SDL_ChargementTexture(window,render,texture,&rect);
                                                SDL_AfficherTexture(window,render,texture,&rect,Poi[i][j].x,Poi[i][j].y);
                                            }
                                        }
                                    }
                                    else if(i%2 == 1 && j%2 == 0) //piece VERTICALE
                                    {
                                        if(A[i][j].type == PION) //CAS PION
                                        {
                                            if(A[i][j].color == BLANCHE) //BLANCHE
                                            {
                                                texture=CreateTexture(PIONBV,render);
                                                SDL_ChargementTexture(window,render,texture,&rect);
                                                SDL_AfficherTexture(window,render,texture,&rect,Poi[i][j].x,Poi[i][j].y);
                                            }else if(A[i][j].color == NOIRE) // NOIRE
                                            {
                                                texture=CreateTexture(PIONNV,render);
                                                SDL_ChargementTexture(window,render,texture,&rect);
                                                SDL_AfficherTexture(window,render,texture,&rect,Poi[i][j].x,Poi[i][j].y);
                                            }
                                        }
                                        else if(A[i][j].type == DAME) // CAS DAME
                                        {
                                            if(A[i][j].color == BLANCHE) // BLANCHE
                                            {
                                                texture=CreateTexture(DAMEBV,render);
                                                SDL_ChargementTexture(window,render,texture,&rect);
                                                SDL_AfficherTexture(window,render,texture,&rect,Poi[i][j].x,Poi[i][j].y);
                                            }else if(A[i][j].color == NOIRE) // NOIRE
                                            {
                                                texture=CreateTexture(DAMENV,render);
                                                SDL_ChargementTexture(window,render,texture,&rect);
                                                SDL_AfficherTexture(window,render,texture,&rect,Poi[i][j].x,Poi[i][j].y);
                                            }
                                        }
                                    }
                                    else if(i%2 == 1 && j%2 == 1) //piece VERTICALE
                                    {
                                        if(A[i][j].type == ROI) //CAS PION
                                        {
                                            if(A[i][j].color == BLANCHE) //BLANCHE
                                            {
                                                texture=CreateTexture(ROIB,render);
                                                SDL_ChargementTexture(window,render,texture,&rect);
                                                SDL_AfficherTexture(window,render,texture,&rect,Poi[i][j].x,Poi[i][j].y);
                                            }else if(A[i][j].color == NOIRE) // NOIRE
                                            {
                                                texture=CreateTexture(ROIN,render);
                                                SDL_ChargementTexture(window,render,texture,&rect);
                                                SDL_AfficherTexture(window,render,texture,&rect,Poi[i][j].x,Poi[i][j].y);
                                            }
                                        }
                                    }

                                }


                            }
                        }
                        continue;
                    }


                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE : //exit si l'user click sur echap
                            program_lunched = SDL_FALSE;
                            break;
                        case SDLK_a :
                            printf("vous avez tapez A\n");
                            continue;
                        default : continue;
                    }
                case SDL_QUIT :
                    program_lunched = SDL_FALSE;
                    break;
                default :
                    break;

            }
            SDL_RenderPresent(render);//mise a jour de rendu
        }
    }
    //------------------ Fermeture ----------------/

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return EXIT_SUCCESS;
}
