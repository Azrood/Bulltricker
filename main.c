#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#define WINDOW_WIDTH 648
#define WINDOW_HEIGHT 648
void SDL_ExitWithError(const char *message)
{
    SDL_Log("Erreur : %s > %s\n",message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_ExitError(const char * message , SDL_Renderer *render , SDL_Window *window)
{
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_ExitWithError(message);
}

void SDL_InserImage(char * URL,SDL_Window *window,SDL_Renderer *render,SDL_Surface *image,
                    SDL_Texture *texture,SDL_Rect rectangle,int x,int y)
{
    image = SDL_LoadBMP(URL);
    if(image == NULL) SDL_ExitError("Impossible de charger l'image",render,window);
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);


    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    rectangle.x = x;
    rectangle.y = y;

    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
}

char * SavoirLocation(int x , int y )
{
    char *pos;
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
    if(x <= 604 && x >= 46)
    {
        if(x <= 64 && x >= 46)   strcat(pos,"V1");
        if(x <= 121 && x >= 64)  strcat(pos,"1");
        if(x <= 159 && x >= 123) strcat(pos,"V2");
        if(x <= 198 && x >= 141) strcat(pos,"2");
        if(x <= 218 && x >= 200) strcat(pos,"V3");
        if(x <= 275 && x >= 218) strcat(pos,"3");
        if(x <= 295 && x >= 277) strcat(pos,"V4");
        if(x <= 352 && x >= 295) strcat(pos,"4");
        if(x <= 372 && x >= 354) strcat(pos,"V5");
        if(x <= 429 && x >= 372) strcat(pos,"5");
        if(x <= 449 && x >= 431) strcat(pos,"V6");
        if(x <= 506 && x >= 449) strcat(pos,"6");
        if(x <= 526 && x >= 508) strcat(pos,"V7");
        if(x <= 583 && x >= 526) strcat(pos,"7");
        if(x <= 603 && x >= 585) strcat(pos,"V8");
    }

    //printf("%s\n",pos);
    return *pos;
}
int main(int argc, char *argv[])
{
    /****************** Déclaration *****************/

    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect rectangle;
    int x,y;
    char *pos;
    /****************** Initialisation *****************/


    if((SDL_Init(SDL_INIT_VIDEO) != 0)) SDL_ExitWithError("Initialisation echoée");
    /*window=SDL_CreateWindow("Bulltricker",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,648,648,SDL_WINDOW_SHOWN);
    if((window == NULL)) SDL_ExitWithError("Creation fenetre echoée");

    render = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
    if(render == NULL) SDL_ExitWithError("Creation render echoée");
    SDL_RenderPresent(render);

    if(SDL_RenderClear(render) != 0) SDL_ExitWithError("clear render echoée");*/

    if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN,&window,&render) != 0)
        SDL_ExitWithError("impossible de cree fenetre et render");
    // ************** charge BOARD
    image = SDL_LoadBMP("images/board.bmp");
    if(image == NULL) SDL_ExitError("Impossible de charger l'image",render,window);
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);


    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    rectangle.x = (WINDOW_WIDTH - rectangle.w) / 2;
    rectangle.y = (WINDOW_HEIGHT - rectangle.h) / 2;

    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    /*texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);


    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    rectangle.x = (WINDOW_WIDTH - rectangle.w) / 2;
    rectangle.y = (WINDOW_HEIGHT - rectangle.h) / 2;

    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }*/

    // ************** charge DAME NOIRE
    image = SDL_LoadBMP("images/Dame.bmp");
    if(image == NULL) SDL_ExitError("Impossible de charger l'image",render,window);
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    rectangle.x = 46;
    rectangle.y = 67;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }

    rectangle.x = 123;
    rectangle.y = 67;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 200;
    rectangle.y = 67;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 277;
    rectangle.y = 67;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 355;
    rectangle.y = 67;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 432;
    rectangle.y = 67;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 509;
    rectangle.y = 67;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 585;
    rectangle.y = 67;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    // ************** charge ROI NOIRE
    image = SDL_LoadBMP("images/Roi.bmp");
    if(image == NULL) SDL_ExitError("Impossible de charger l'image",render,window);
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    rectangle.x = 308;
    rectangle.y = 78;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    // ************** charge PION NOIRE

    image = SDL_LoadBMP("images/Pion.bmp");
    if(image == NULL) SDL_ExitError("Impossible de charger l'image",render,window);
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    // ************** charge PION NOIRE VERTICALE
    rectangle.x = 46;
    rectangle.y = 144;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 123;
    rectangle.y = 144;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 200;
    rectangle.y = 144;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 277;
    rectangle.y = 144;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 355;
    rectangle.y = 144;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 432;
    rectangle.y = 144;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 509;
    rectangle.y = 144;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 585;
    rectangle.y = 144;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    // ************** charge PION NOIRE HORIZONTAL
    image = SDL_LoadBMP("images/Pion2.bmp");
    if(image == NULL) SDL_ExitError("Impossible de charger l'image",render,window);
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    rectangle.x = 68;
    rectangle.y = 124;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 144;
    rectangle.y = 124;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 221;
    rectangle.y = 124;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 298;
    rectangle.y = 124;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 376;
    rectangle.y = 124;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 453;
    rectangle.y = 124;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 530;
    rectangle.y = 124;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }

    // ************** charge DAME BLANCHE
    image = SDL_LoadBMP("images/DameB.bmp");
    if(image == NULL) SDL_ExitError("Impossible de charger l'image",render,window);
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    rectangle.x = 46;
    rectangle.y = 529;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 123;
    rectangle.y = 529;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 200;
    rectangle.y = 529;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 277;
    rectangle.y = 529;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 355;
    rectangle.y = 529;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 432;
    rectangle.y = 529;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 509;
    rectangle.y = 529;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 585;
    rectangle.y = 529;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }

    // ************** charge ROI BLANCHE
    image = SDL_LoadBMP("images/RoiB.bmp");
    if(image == NULL) SDL_ExitError("Impossible de charger l'image",render,window);
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    rectangle.x = 308;
    rectangle.y = 540;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }

    // ************** charge PION BLANCHE

    image = SDL_LoadBMP("images/PionB.bmp");
    if(image == NULL) SDL_ExitError("Impossible de charger l'image",render,window);
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    // ************** charge PION BLANCHE VERTICALE
    rectangle.x = 46;
    rectangle.y = 453;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 123;
    rectangle.y = 453;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 200;
    rectangle.y = 453;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 277;
    rectangle.y = 453;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 355;
    rectangle.y = 453;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 432;
    rectangle.y = 453;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 509;
    rectangle.y = 453;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 585;
    rectangle.y = 453;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }

    // ************** charge PION BLANCHE HORIZONTALE
    image = SDL_LoadBMP("images/Pion2B.bmp");
    if(image == NULL) SDL_ExitError("Impossible de charger l'image",render,window);
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    if(texture == NULL) SDL_ExitError("impossible de cree la texture",render,window);
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
        SDL_ExitError("impossible de charger la texture",render,window);

    rectangle.x = 68;
    rectangle.y = 509;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 144;
    rectangle.y = 509;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 221;
    rectangle.y = 509;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 298;
    rectangle.y = 509;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 376;
    rectangle.y = 509;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 453;
    rectangle.y = 509;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }
    rectangle.x = 530;
    rectangle.y = 509;
    if(SDL_RenderCopy(render,texture,NULL,&rectangle) != 0)
    {
        SDL_DestroyTexture(texture);
        SDL_ExitError("impossible d'afficher la texture",render,window);
    }

    SDL_RenderPresent(render);

    /****************** Code *****************/
    SDL_bool program_lunched = SDL_TRUE;
    while(program_lunched)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN :
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        printf("(%d , %d )\n",event.button.x,event.button.y);
                        puts(SavoirLocation(event.button.x , event.button.y));
                        continue;
                    }
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE :
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
        }
    }

    /****************** Fermeture *****************/
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
