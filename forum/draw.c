#include <draw.h>
#include <game.h>
#include <stdio.h>
#include <screen.h>
#include <particle.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

extern pionek** army;
extern int select;
extern pionek_type attr[MAX_TYPE];
particle *part[MAX_PARTICLE];

SDL_Surface* screen;//ekran
SDL_Surface* draw_table_army_type[MAX_TYPE];
SDL_Surface* draw_table_army_color[2];//nie sądzę że będzie więcej graczy niż 2.
SDL_Surface* background;//tlo
SDL_Surface* button_angle,*button_orbit;//przyciski
SDL_Surface* select_friendly,*select_enemy;//'obwódki' zaznaczenia jednostek
SDL_Surface* anim[MAX_TYPE_PARTICLE][4];//particles
SDL_Surface* health_bar[6],*reload_bar[6];//paski

SDL_Surface* load_imageAlpha( const char* filename ) { //wczytuje obrazek z pliku
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image using SDL_image
    loadedImage = IMG_Load( filename );

    //If the image loaded
    if( loadedImage != NULL ) {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    } else
        fprintf(stderr,"ERR:Unable to load file %s: %s\r\n",filename, IMG_GetError());


    //Return the optimized image
    return optimizedImage;
}

SDL_Surface* load_image( const char* filename ) { //wczytuje obrazek z pliku
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image using SDL_image
    loadedImage = IMG_Load( filename );

    //If the image loaded
    if( loadedImage != NULL ) {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    } else
        fprintf(stderr,"ERR:Unable to load file %s: %s\r\n",filename, IMG_GetError());


    //Return the optimized image
    return optimizedImage;
}

int draw_sprite(int x,int y, SDL_Surface* image) {
    SDL_Rect offset;

    //kordynacje
    offset.x = x;
    offset.y = y;

    //dodanie do screen
    SDL_BlitSurface( image, NULL, screen, &offset );
}

int load_files(void) { //wczytywanie plików i generacja
    char adres_color[] = "image/color/-.png";
    char adres_type[] = "image/type/-.png";
    char adres_anim[] = "image/anim/-_-.png";
    char adres_health[] = "image/bar/health_-.png";
    char adres_reload[] = "image/bar/reload_-.png";
    int color[2] = { 0xFF44228F, 0xFFFFFF8F };

    background = load_image("image/tlo.png");
    button_angle = load_imageAlpha("image/select/angle.png");
    button_orbit = load_imageAlpha("image/select/orbit.png");
    select_friendly = load_imageAlpha("image/select/friendly.png");
    select_enemy = load_imageAlpha("image/select/enemy.png");


    for(int i=0; i != 2; ++i) {
        adres_color[12] = i+48;
        draw_table_army_color[i] = load_imageAlpha(adres_color);
    }

    for(int i=0; i != MAX_TYPE; ++i) {
        adres_type[11] = i+48;
        draw_table_army_type[i] = load_imageAlpha(adres_type);
    }
    for(int k=0; k != MAX_TYPE_PARTICLE ; ++k){//ładowanie particles
        adres_anim[11] = 'a' + k;
        for(int i=0; i != 4; ++i) {
            adres_anim[13] = i + 48;
            anim[k][i] = load_imageAlpha(adres_anim);
        }
    }
    for(int i=0; i != 6; ++i) {
        adres_health[17] = i+48;
        adres_reload[17] = i+48;
        health_bar[i] = load_imageAlpha(adres_health);
        reload_bar[i] = load_imageAlpha(adres_reload);
    }


    //generowanie
    //interface jednostek

    return 0;
}

int draw_init(void) { //wczytuje wszystko
    screen = NULL;
    if (SDL_Init( SDL_INIT_VIDEO ) ) { //uruchamia SDL
        fprintf(stderr,"ERR:Unable to init SDL: %s\r\n", SDL_GetError() );//zrzucanie bledu na ekran
        return -1;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );//tworzy okno z grą
    if (!screen)
        return -1;
    SDL_WM_SetCaption( "Marticos", NULL );

    for(int i=0; i != MAX_PARTICLE ; ++i)
        part[i] = NULL;

    if ( load_files() )
        return -1;

//        SDL_SaveBMP(background,"image/lol.bmp");

    return 0;
}

void set_particle(enum e_particle_type type , int x, int y) {
    particle* temp;
    for(int i=0; i != MAX_PARTICLE ; ++i) {
        temp = part[i];
        if(!temp) {
            temp = malloc( sizeof( particle ) );//stworzenie
            part[i] = temp;//zapisywanie do tablicy
            temp->x = x;
            temp->y = y;
            temp->type = type;
            temp->lifetime = 3;
            return;
        }
    }
}

int draw_step(int mod) {

    //rysowanie tla
    draw_sprite( 0, 0 , background );
    //rysowanie jednostek
    pionek* temp,*temp2;
    for(int i=0; i != MAX_ARMY; ++i) {
        temp = army[i];
        if (temp) {
            int health_piece = (int)( temp->hp/attr[ temp->type ].hp  * 6 ) -1;
            if( temp->freeze_action ){
                int reload_piece = (int)( (float)temp->freeze_action/attr[ temp->type ].reload_time  * 6 ) -1;
                draw_sprite( temp->x - 12, temp->y - 6 , reload_bar[ reload_piece ] );//pasek przeładowania
            }
            draw_sprite( temp->x - 12, temp->y - 12 , health_bar[ health_piece ] );//pasek zycia
            draw_sprite( temp->x - 12 , temp->y - 12 , draw_table_army_color[ temp->side ] );//strona [kolor] jednostki
            draw_sprite( temp->x - 12, temp->y - 12 , draw_table_army_type[ temp->type ] );//typ jednostki
           //
           /* boxColor( screen , temp->x - 12 , temp->y - 15 ,
                      temp->x - 12 + 24 * temp->hp / attr[ temp->type ].hp  , temp->y - 13 ,
                      0x00FF00FF );
            // athlanster@gmail.com, me@athlan.pl, athlan@vgroup.pl

                boxColor( screen , temp->x - 12 , temp->y + 15 ,
                          temp->x - 12 + 24 * temp->freeze_action / attr[ temp->type ].reload_time  , temp->y + 13 ,
                          0xFFBB00FF );*/
        }
    }
    //rysowanie zaznaczonych jednostek
    if (select != -1) {
        temp = army[select];
        float x,y,angle;
        const distance = 18;
        draw_sprite( temp->x - 12, temp->y - 12 , select_friendly );
        if (!temp->freeze_move) {
            y = distance * cos(temp->angle);
            x = distance * sin(temp->angle);
            draw_sprite( temp->x - x -6, temp->y - y -6 , button_orbit );
            draw_sprite( temp->x + x -6, temp->y + y -6 , button_orbit );
            draw_sprite( temp->x - y -6, temp->y + x -6 , button_angle );
            draw_sprite( temp->x + y -6, temp->y - x -6 , button_angle );
        }
        if (temp->select != -1 ) {
            temp2 = army[ temp->select ];
            if (temp2)
                draw_sprite( temp2->x - 12, temp2->y - 12 , select_enemy );
            else
                temp->select = -1;
        }
    }
    //particle
    particle* temp_p;
    for(int i=0; i != MAX_PARTICLE ; ++i) {
        temp_p = part[i];
        if (temp_p) {
            draw_sprite( temp_p->x - 8, temp_p->y - 8 , anim[ temp_p->type ][temp_p->lifetime] );
            if (mod % 5  == 0 ) { //czas przesuniecia animacji
                if ( temp_p->lifetime > 0 )
                    --temp_p->lifetime;
                else {
                    free( temp_p );
                    part[i] = NULL;
                }
            }
        }
    }

    SDL_Flip( screen );
    SDL_Delay( 33 );
}

int draw_stop(void) {
    for(int i=0; i != 2; ++i)
        SDL_FreeSurface( draw_table_army_color[i] );
    for(int i=0; i != MAX_TYPE; ++i)
        SDL_FreeSurface( draw_table_army_type[i] );
    //Quit SDL
    SDL_Quit();
}
