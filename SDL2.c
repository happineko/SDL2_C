//Question 12

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h> //On appelle la librairie SDL2 dans le projet

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
        SDL_Point point; //On déclare un point qu'on pourra utiliser plus tard dans le programme
        SDL_Rect rectangle; //On declare un rectangle qu'on pourra utiliser plus tard dans le programme
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
            rectangle.x = 0;
            rectangle.y = 0;
            rectangle.w = nLargeur;
            rectangle.h = nHauteur;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer,&rectangle);
            SDL_RenderPresent(renderer);
            SDL_Delay(3000); //On attend trois secondes, que l'utilisateur voit la fenêtre

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
