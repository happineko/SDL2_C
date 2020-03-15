//Question 6

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h> //On appelle la librairie SDL2 dans le projet

int main(int argc, char** argv) //argc signifie le nombre d'argument qui sera renseign� argv est la liste des argument qu'il recevra
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) //Dans ce cas on initialise le sous systeme video, si l'initialisation �choue on arrete le programme avec un code erreur
    {
        fprintf(stdout,"�chec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }


    SDL_Quit(); //On libere le sous systeme une fois qu'on a terminer le programme (lib�re la m�moire)

    return 0;
}
