#include <stdio.h>
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Funciones_principales.h"
#include <sys/time.h>
#include <stdlib.h>

SDL_Texture *cargar_texturas (char ruta[50],SDL_Renderer *render);
void you_win(SDL_Rect *posicion_texto, int numero_vidas, SDL_Renderer *escenario, SDL_Texture *texto);
void movimiento_jugador(variables_jugador jugador[], int numero_jugador, int *tiempo);
void limites_mapa(variables_jugador jugador[],int numero_jugador);
void generar_jugador(variables_jugador jugador[], int numero_jugador, SDL_Renderer *escenario, _Bool cargar);
void copiar_atributos(variables_jugador jugador[], int numero_jugador, SDL_Renderer *escenario);
void destruir_atributos(variables_jugador jugador[], int numero_jugador);
void fichero (variables_jugador jugador[], int numero_jugador, char nombre_partida[]);
void cargar_partida(variables_jugador jugador[], int numero_jugador, _Bool cargar, SDL_Renderer *escenario, char nombre_partida[]);
void datos_partida(char nombre_partida[50]);
void multijugador(_Bool cargar, char nombre_partida[], int victorias[],int numero_victoria, _Bool revancha, int numero_mapa,int);
