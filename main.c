#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <strings.h>
#include "moves.h"
#include "checks.h"
#include "tools.h"

#define BOARD "images/Board.bmp"
#define DAMEBV "images/DameB.bmp"
#define DAMEBH "images/Dame2B.bmp"
#define PIONBV "images/PionB.bmp"
#define PIONBH "images/Pion2B.bmp"
#define ROIB   "images/RoiB.bmp"
#define DAMENV "images/Dame.bmp"
#define DAMENH "images/Dame2.bmp"
#define PIONNV "images/Pion.bmp"
#define PIONNH "images/Pion2.bmp"
#define ROIN   "images/Roi.bmp"
#define MENU   "images/belltricker_menu.bmp"

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

const int LARG_FENETRE = 648;
const int HAUT_FENETRE = 648;
typedef struct Point {
    int x;
    int y;
} Point;

void RemplirPoint(Point **P)
{
    P[1][0].x = 47;
    P[1][0].y = 67;
    for(int j=2 ; j<15 ; j+=2){
            P[1][j].x =  P[1][j-2].x + 77;
            P[1][j].y = 67;
    }
    for(int i=3 ; i<15 ; i+=2)//chargement des coordonées  des piece verticale
    {
        P[i][0].x = 47;
        P[i][0].y = P[i-2][0].y + 77;
        for(int j=2 ; j<15 ; j+=2)
        {
            P[i][j].x = P[i][j-2].x + 77;
            P[i][j].y = P[i][0].y;
        }

    }

    P[0][1].x = 67;
    P[0][1].y = 47;
    for(int j=3 ; j<15 ; j+=2){
            P[0][j].x =  P[0][j-2].x + 77;
            P[0][j].y = 47;
    }
    for(int i=2 ; i<15 ; i+=2)//chargement des coordonées  des piece Horizontale
    {
        P[i][1].x = 67;
        P[i][1].y = P[i-2][1].y + 77;
        for(int j=3 ; j<15 ; j+=2)
        {
            P[i][j].x = P[i][j-2].x + 77;
            P[i][j].y = P[i][1].y;
        }

    }

    P[1][1].x = 77;
    P[1][1].y = 77;
    for(int j=3 ; j<15 ; j+=2){
            P[1][j].x =  P[1][j-2].x + 77;
            P[1][j].y = 77;
    }
    for(int i=3 ; i<15 ; i+=2)//chargement des coordonées  des cases royales
    {
        P[i][1].x = 77;
        P[i][1].y = P[i-2][1].y + 77;
        for(int j=3 ; j<15 ; j+=2)
        {
            P[i][j].x = P[i][j-2].x + 77;
            P[i][j].y = P[i][1].y;
        }

    }
}

char * SavoirLocationX(int x)
{
    char *pos=(char *)malloc(2);

    if(x <= 604 && x >= 46)
    {
        if(x <= 64 && x >= 46)   strcpy(pos,"V1");
        if(x <= 121 && x >= 64)  strcpy(pos,"1");
        if(x <= 159 && x >= 123) strcpy(pos,"V2");
        if(x <= 198 && x >= 141) strcpy(pos,"2");
        if(x <= 218 && x >= 200) strcpy(pos,"V3");
        if(x <= 275 && x >= 218) strcpy(pos,"3");
        if(x <= 295 && x >= 277) strcpy(pos,"V4");
        if(x <= 352 && x >= 295) strcpy(pos,"4");
        if(x <= 372 && x >= 354) strcpy(pos,"V5");
        if(x <= 429 && x >= 372) strcpy(pos,"5");
        if(x <= 449 && x >= 431) strcpy(pos,"V6");
        if(x <= 506 && x >= 449) strcpy(pos,"6");
        if(x <= 526 && x >= 508) strcpy(pos,"V7");
        if(x <= 583 && x >= 526) strcpy(pos,"7");
        if(x <= 603 && x >= 585) strcpy(pos,"V8");
    }

    //printf("%s\n",pos);
    return pos;
}
char * SavoirLocationY(int y)
{
    char *pos = (char *)malloc(2);
    if(y <= 604 && y>= 46)
    {

        if(y <= 67 && y >= 46) strcpy(pos,"H1");
        if(y <= 114 && y >= 78) strcpy(pos,"A");
        if(y <= 143 && y >= 123) strcpy(pos,"H2");
        if(y <= 191 && y >= 155) strcpy(pos,"B");
        if(y <= 220 && y >= 200) strcpy(pos,"H3");
        if(y <= 268 && y >= 232) strcpy(pos,"C");
        if(y <= 297 && y >= 277) strcpy(pos,"H4");
        if(y <= 345 && y >= 309) strcpy(pos,"D");
        if(y <= 374 && y >= 354) strcpy(pos,"H5");
        if(y <= 422 && y >= 386) strcpy(pos,"E");
        if(y <= 451 && y >= 431) strcpy(pos,"H6");
        if(y <= 499 && y >= 463) strcpy(pos,"F");
        if(y <= 528 && y >= 508) strcpy(pos,"H7");
        if(y <= 576 && y >= 540) strcpy(pos,"G");
        if(y <= 604 && y >= 585) strcpy(pos,"H8");

    }
    return pos;
}

void SDL_DestroywindowEtrender(SDL_Window *window,SDL_Renderer *render)
{
    if(window)
        SDL_DestroyWindow(window);
    if(render)
        SDL_DestroyRenderer(render);
    return;
}

void SDL_ExitErreur(char * messageErreur){
    SDL_Log("Erreur %s : %s\n",messageErreur,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

SDL_Texture * CreateTexture(const char * text,SDL_Renderer *render){
	SDL_Surface *background =SDL_LoadBMP(text);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(render, background);
	SDL_FreeSurface(background);
	return texture;
}

void SDL_ChargementTexture(SDL_Window * window,SDL_Renderer* render ,SDL_Texture * texture,SDL_Rect *rect){
    if((SDL_QueryTexture(texture,NULL,NULL,&rect->w,&rect->h))!=0){
        SDL_DestroywindowEtrender(window,render);//pour detruire la window et le renderer
        SDL_DestroyTexture(texture);//pour detruire l texture
        SDL_ExitErreur("Chargement texture");//afficher le message d'erreur e quitter SDL avec SDL_QUIT;
    }
}

void SDL_AfficherTexture(SDL_Window * window,SDL_Renderer* render ,SDL_Texture * texture,SDL_Rect *rect,int x,int y){
    rect->x=x;
    rect->y=y;
    if((SDL_RenderCopy(render,texture,NULL,rect))!=0){
        SDL_DestroywindowEtrender(window,render);
        SDL_DestroyTexture(texture);
        SDL_ExitErreur("Affichage de l'image");
    }
}
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

    // affichage des dames noire


    /*F[ind_DAMENV]=CreateTexture(DAMENV,render);
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
    SDL_AfficherTexture(window,render,F[ind_ROIB],&rect,308,540);*/

    SDL_RenderPresent(render);
    ///------------------- Gestion des evenements ----------------/
    SDL_bool program_lunched = SDL_TRUE;
    int start = 1; // 1 pour page menu 0 pour le jeu
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

                        if(start == 1)//tester
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
                            if(event.button.x<437 && event.button.x>198 && event.button.y<618 && event.button.y>572)
                            {
                                program_lunched = SDL_FALSE;
                            }
                            SDL_RenderPresent(render);
                        }

                        printf("(%d , %d )\n",event.button.x,event.button.y);
                        // stocker les indices du piece a jouer apres 1er click
                        strcpy(positionstr , SavoirLocationY(event.button.y));
                        strcat(positionstr , SavoirLocationX(event.button.x));
                        moves.initialmove = ConvertirLocation(positionstr);
                        playedpiece = A[moves.initialmove.line][moves.initialmove.column];
                        fflush(stdin);
                        continue;
                    }

                    if(event.button.button == SDL_BUTTON_RIGHT)
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
