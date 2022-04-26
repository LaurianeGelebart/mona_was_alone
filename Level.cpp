#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "basics.h"
#include "Character.h"
#include "Level.h"


const Uint8* keystate = SDL_GetKeyboardState(NULL);

void Level::init_level(Square* tab_square, Character* tab_character, int nb_character)
{
    this->tab_square = tab_square;
    this->tab_character = tab_character;
    this->nb_character = nb_character ; 
    this->current_character = 0; 
}

void Level::set_nb_character_end(int nb_character_end)
{
    this->nb_character_end = nb_character_end;
}

void Level::set_current_character(int new_current)
{
    this->current_character = new_current;
}

void Level::draw()
{
    for (int i=0 ; i<this->nb_character ; i++){
        (this->tab_character[i]).draw_character(1); 
    }
}

int Level::event()
{
    SDL_Event e;
    while(SDL_PollEvent(&e)) 
    {
        //L'utilisateur ferme la fenetre
        if(e.type == SDL_QUIT) 
        {
            return 0;
            break;
        }

        //L'utilisateur appuie sur Q ou Echap 
        if(	e.type == SDL_KEYDOWN 
            && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
        {
            return 0; 
            break;
        }
        
        switch(e.type) 
        {
            //Event Fenetre 
            case SDL_WINDOWEVENT:
                switch (e.window.event) 
                {
                    //Redimensionnement fenetre
                    case SDL_WINDOWEVENT_RESIZED:
                        onWindowResized(e.window.data1, e.window.data2);                
                        break;

                    default:
                        break; 
                }
                break;

            //Clic souris
            case SDL_MOUSEBUTTONUP:
                printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                break;
            
            //Touche clavier
            case SDL_KEYDOWN:
                printf("touche pressee (code = %d)\n", e.key.keysym.sym);

                if (e.key.keysym.sym == SDLK_UP)
                {
                    this->tab_character[this->current_character].move(0,1);
                }
                break;

            default:
                break;
        }
    }

    /* fin while */

    if (keystate[SDL_SCANCODE_RIGHT])
    {
        this->tab_character[this->current_character].move(1,0);
    }
    else if(keystate[SDL_SCANCODE_LEFT])
    {
        this->tab_character[this->current_character].move(-1,0);
    }

    return 1 ;  
}
