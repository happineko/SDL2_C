#include <stdlib.h>
#include <stdio.h>
#include <SDL2\SDL.h>

int main(int argc, char** argv) //argc signifie le nombre d'argument qui sera renseign� argv est la liste des argument qu'il recevra
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) //Dans ce cas on initialise le sous systeme video, si l'initialisation �choue on arrete le programme avec un code erreur
    {
        fprintf(stdout,"�chec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Cr�ation de la fen�tre */
        SDL_Window* pWindow = NULL; //On cr�e une variable fenetre de type SDL_Window
        SDL_Renderer* renderer;//D�claration du renderer
        SDL_Point cercleV, cercleP; //On d�clare un point qu'on pourra utiliser plus tard dans le programme
        SDL_Rect rectangle, carV, carP, rTemp; //On declare un rectangle qu'on pourra utiliser plus tard dans le programme
        SDL_Surface *surface, *temp = NULL; //D�claration d'une surface
        SDL_Texture *texture; //Declaration de la texture
        int nLargeur=1280;
        int nHauteur=720;

        //Pour cr�er la fentre on utilise la fonction SDL_CreateWindow qui attend en parametre un nom,une position x, une position y, une largeur, une hauteur et un ou plusieurs flags (disponible sur le site de SDL dans ce cas la on veut just afficher la fen�tre)
        pWindow = SDL_CreateWindow("Fenetre SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  nLargeur,
                                                                  nHauteur,
                                                                  SDL_WINDOW_SHOWN);

        if( pWindow ) //si la fenetre a bien �t� cr�ee
        {

            if(renderer == NULL)//gestion des erreurs
            {
                printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
                return EXIT_FAILURE;
            }

                SDL_DestroyWindow(pWindow); //On "d�truit" la fenetre
                SDL_DestroyRenderer(renderer);
            }
            else
            {
                fprintf(stderr,"Erreur de cr�ation de la fen�tre: %s\n",SDL_GetError()); //sinon on retourne un code erreur
            }
        }

    SDL_Quit(); //On libere le sous systeme une fois qu'on a terminer le programme (lib�re la m�moire)

    return 0;
}
