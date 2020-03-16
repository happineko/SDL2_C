//Question 26/27

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h> //On appelle la librairie SDL2 dans le projet

//J'utilise une procedure permettant de créer un cercle point par point sachant qu'il n'existe pas de fonction pour créer un cercle directement via SDL (comme par exemple SDL_Rect)
//Il attend en parametre le renderer, un centre de type point, et un rayon
void draw_circle(SDL_Renderer * renderer, SDL_Point centre, int radius)
{
   int diameter = (radius * 2);

   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      //  Chacun des éléments suivants corrspond a un octant du cercle
      SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
      SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y);
      SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
      SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y);
      SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
      SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x);
      SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
      SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x);

      //On redeplace le point pour former petit a petit le cercle
      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;

      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);


      }
   }
}

//J'utilise une procedure permettant de créer un cercle plein
//Il attend en parametre le renderer, un centre de type point, et un rayon
void fill_circle(SDL_Renderer *renderer, SDL_Point center, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);


            }
        }
    }
}

int main(int argc, char** argv) //argc signifie le nombre d'argument qui sera renseigné argv est la liste des argument qu'il recevra
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) //Dans ce cas on initialise le sous systeme video, si l'initialisation échoue on arrete le programme avec un code erreur
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Création de la fenêtre */
        SDL_Window* pWindow = NULL; //On crée une variable fenetre de type SDL_Window
        SDL_Renderer* renderer;//Déclaration du renderer
        SDL_Point cercleV, cercleP; //On déclare un point qu'on pourra utiliser plus tard dans le programme
        SDL_Rect rectangle, carV, carP, rTemp; //On declare un rectangle qu'on pourra utiliser plus tard dans le programme
        SDL_Surface *surface, *temp = NULL; //Déclaration d'une surface
        SDL_Texture *texture; //Declaration de la texture
        int nLargeur=1280;
        int nHauteur=720;

        //Pour créer la fentre on utilise la fonction SDL_CreateWindow qui attend en parametre un nom,une position x, une position y, une largeur, une hauteur et un ou plusieurs flags (disponible sur le site de SDL dans ce cas la on veut just afficher la fenêtre)
        pWindow = SDL_CreateWindow("Fenetre SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  nLargeur,
                                                                  nHauteur,
                                                                  SDL_WINDOW_SHOWN);

        if( pWindow ) //si la fenetre a bien été créee
        {
            SDL_GetWindowSize(pWindow,&nLargeur,&nHauteur);
            renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer
            cercleV.x = 310;
            cercleV.y = 70;
            cercleP.x = 430;
            cercleP.y = 70;
            rectangle.x = 0;
            rectangle.y = 0;
            rectangle.w = nLargeur;
            rectangle.h = nHauteur;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer,&rectangle);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            carV.x = 20;
            carV.y = 20;
            carV.h = 100;
            carV.w = 100;
            carP.x = 140;
            carP.y = 20;
            carP.h = 100;
            carP.w = 100;
            draw_circle(renderer,cercleV,50);
            fill_circle(renderer,cercleP,50);
            SDL_RenderFillRect(renderer,&carP);
            SDL_RenderDrawRect(renderer, &carV);
            SDL_RenderPresent(renderer);

            SDL_Delay(3000); //On attend trois secondes, que l'utilisateur voit la fenêtre

            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);

            SDL_SetRenderTarget(renderer,NULL); //On definit la texture a rendre
            SDL_Surface *bmp = SDL_LoadBMP("duck.bmp");
            texture = SDL_CreateTextureFromSurface(renderer,bmp);
            SDL_FreeSurface(bmp);
            SDL_Rect imagebmp;
            imagebmp.x = 0;
            imagebmp.y = 0;
            SDL_QueryTexture(texture,NULL,NULL,&imagebmp.w,&imagebmp.h);
            SDL_RenderCopy(renderer,texture,NULL,&imagebmp);
            SDL_RenderPresent(renderer);

            SDL_Delay(3000);

        if(renderer == NULL)//gestion des erreurs
        {
            printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
            return EXIT_FAILURE;
        }

            SDL_DestroyWindow(pWindow); //On "détruit" la fenetre
            SDL_DestroyRenderer(renderer);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError()); //sinon on retourne un code erreur
        }
    }

    SDL_Quit(); //On libere le sous systeme une fois qu'on a terminer le programme (libère la mémoire)

    return 0;
}
