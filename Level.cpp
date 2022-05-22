#include <SDL2/SDL.h>

#include <stdio.h> //DEBUG

#include "Level.h"
#include "Character.h"
#include "geometry.h"
#include "Camera2D.h"

Level::Level(Square* tab_square, Character* tab_character[], int nb_square, int nb_character)
{
    this->tab_square = tab_square;
    this->nb_square = nb_square;
    this->tab_character = tab_character;
    this->nb_character = nb_character ; 
    this->selected_character = 0;
    this->current_character = tab_character[this->selected_character]; 
    this->nb_character_end = 0;
}

Character* Level::get_current_character(){  
    return this->current_character;
}

int Level::get_nb_character(){  
    return this->nb_character;
}

void Level::set_nb_character_end(int nb_character_end)
{
    this->nb_character_end = nb_character_end;
}

void Level::set_current_character(int new_current)
{
    this->current_character = tab_character[new_current];
}

void Level::draw()
{
    this->level_cam.set_position(current_character->current_pos);
    this->current_character->draw_character(1);
    
    glPushMatrix();
    glTranslatef(-level_cam.pos.x,-level_cam.pos.y*0.2,0);

    for (int i=0 ; i<this->selected_character-1 ; i++){
        (this->tab_character[i])->draw_character(1); 
    }
    for (int i=selected_character+1; i<this->nb_character; i++){
        (this->tab_character[i])->draw_character(1); 
    }
    for (int i=0 ; i<this->nb_square ; i++){
        this->tab_square[i].drawSquare(); 
    }
    glPopMatrix();
    
}

void Level::manageEvents(SDL_Event e)
{   
    if (e.key.keysym.sym == SDLK_SPACE) {
        this->selected_character = (this->selected_character+1)%this->nb_character; 
        this->set_current_character(this->selected_character);
    }else {
        this->current_character->manageEvents(e);
    }
    
}

