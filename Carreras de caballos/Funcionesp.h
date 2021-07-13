#include <stdio.h>
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct
{
        int numero_jugador; //Cantidad de jugadores
        int ancho_animacion, alto_animacion;//Alto, ancho imagen animacion

        SDL_Texture *animacion; //Texturas relacioadas con el jugador
        SDL_Rect recortar_animacion;
        SDL_Rect posicion_animacion;

}variables_jugador;

SDL_Texture *cargar_texturas (char ruta[50],SDL_Renderer *render);
void you_win(SDL_Rect *posicion_texto, int numero_vidas, SDL_Renderer *escenario, SDL_Texture *texto);
void movimiento_jugador(variables_jugador jugador[], int numero_jugador, int *tiempo);
void limites_mapa(variables_jugador jugador[],int numero_jugador);
void generar_jugador(variables_jugador jugador[], int numero_jugador, SDL_Renderer *escenario,int numero_jugadores);
void copiar_atributos(variables_jugador jugador[], int numero_jugadores, SDL_Renderer *escenario);
void destruir_atributos(variables_jugador jugador[], int numero_jugador);
void multijugador(int numero_jugadores);
