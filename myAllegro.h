#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

const int display_width	 = 800;
const int display_height = 600;

ALLEGRO_DISPLAY		    *display	    = NULL;
ALLEGRO_FONT			*font_menu      = NULL;
ALLEGRO_FONT			*font24			= NULL;
ALLEGRO_EVENT_QUEUE     *event_queue	= NULL;

ALLEGRO_BITMAP *imagePawnWhite			= NULL;
ALLEGRO_BITMAP *imageKnightWhite		= NULL;
ALLEGRO_BITMAP *imageBishopWhite		= NULL;
ALLEGRO_BITMAP *imageRookWhite			= NULL;
ALLEGRO_BITMAP *imageQueenWhite		    = NULL;
ALLEGRO_BITMAP *imageKingWhite			= NULL;						  
ALLEGRO_BITMAP *imagePawnBlack			= NULL;
ALLEGRO_BITMAP *imageRookBlack			= NULL;
ALLEGRO_BITMAP *imageKnightBlack		= NULL;
ALLEGRO_BITMAP *imageBishopBlack		= NULL;
ALLEGRO_BITMAP *imageQueenBlack		    = NULL;
ALLEGRO_BITMAP *imageKingBlack			= NULL;

void init_myAllegro(void);

