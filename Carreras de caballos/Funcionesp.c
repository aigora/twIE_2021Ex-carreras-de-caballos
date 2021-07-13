#include <stdio.h>
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Funcionesp.h"
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

SDL_Texture *cargar_texturas (char ruta[50],SDL_Renderer *render)//Crea una textura a traves de una imagen (necesaria la ruta)
{
    SDL_Surface *superficie= IMG_Load(ruta);//Necesita una superficie y un render para crear la textura (SDL_CreateTextureFromSurface lo requiere asi)
    SDL_Texture *imagen= SDL_CreateTextureFromSurface(render,superficie);

    SDL_FreeSurface(superficie);//Liberamos la memoria que ocupa la superfice

    return imagen;//Devuelve la textura
}

void you_win(SDL_Rect *posicion_texto, int numero_vidas, SDL_Renderer *escenario, SDL_Texture *texto)//Se muestra un texto al finalizar la partida
{
    for (int i=0;i<100;i++)
    {
        posicion_texto->w+=5;//El tamaño del texto aumenta progresivamente
        posicion_texto->h+=2;
        SDL_RenderCopy(escenario,texto,NULL,&posicion_texto);
        SDL_RenderPresent(escenario);
    }
}

void movimiento_jugador(variables_jugador jugador[], int numero_jugador, int *tiempo,int *contador)//Permite al usuario interactuar con su jugador
{
    const Uint8 *captura=SDL_GetKeyboardState(NULL);//Necesario para poder usar SDL_Scancode
    int velocidad_movimiento=5;
    SDL_Scancode tecla;

   switch(numero_jugador)
    {
    case 0:
        tecla=SDL_SCANCODE_SPACE;
        break;
    case 1:
        tecla=SDL_SCANCODE_A;
        break;
    case 2:
        tecla=SDL_SCANCODE_L;
        break;
    case 3:
        tecla=SDL_SCANCODE_6;
        break;
    }

    if(captura[tecla])//Detecta si el una tecla esta pulsada, entoces se ejecuta la condicion
        {
            /*srand(time(NULL));
            velocidad_movimiento=rand()%10;*/
            jugador[numero_jugador].recortar_animacion.y=jugador[numero_jugador].alto_animacion/4;

            if(*contador==0)
                jugador[numero_jugador].posicion_animacion.x+=velocidad_movimiento;

            *tiempo+=1;
            *contador+=1;
            if(*tiempo>=5)//Este if sirve para crear la animacion, el tiempo simplemente sirve para que no la ejecute demasiado rapido
            {
                jugador[numero_jugador].recortar_animacion.x+=jugador[numero_jugador].ancho_animacion/4;//Pasa a recortar la siguiente fase de la animacion
                if(jugador[numero_jugador].recortar_animacion.x>=jugador[numero_jugador].ancho_animacion)
                    jugador[numero_jugador].recortar_animacion.x=0;//Cuando llega a la ultima fase de la animacion vuelve a la primera fase
                *tiempo=0;
            }
        }
    else
	*contador=0;
}
void carril(variables_jugador jugador[],int n,int numero_jugador)
{
int i,j;
int carril[4];
const Uint8 *captura=SDL_GetKeyboardState(NULL);//Necesario para poder usar SDL_Scancode
SDL_Scancode tecla[2];
switch(n)
{
case 2:
carril[0]=150;
carril[1]=400;
break;
case 3:
carril[0]=100;
carril[1]=300;
carril[2]=500;
break;
case 4:
carril[0]=25;
carril[1]=225;
carril[2]=425;
carril[3]=625;
break;
}
    if(numero_jugador==0)//En funcion del jugador en cuestion usara las teclas asdw o las flechas
    {
    tecla[0]=SDL_SCANCODE_B;
    tecla[1]=SDL_SCANCODE_N;
    }
    if(numero_jugador==1)
    {
    tecla[0]=SDL_SCANCODE_W;
    tecla[1]=SDL_SCANCODE_Z;
    }
    if(numero_jugador==2)
    {
    tecla[0]=SDL_SCANCODE_LEFT;
    tecla[1]=SDL_SCANCODE_RIGHT;
    }
    if(numero_jugador==3)
    {
    tecla[0]=SDL_SCANCODE_5;
    tecla[1]=SDL_SCANCODE_7;
    }
if(captura[tecla[0]])
{
    for(j=0;j<n;j++)
        {
        if(jugador[numero_jugador].posicion_animacion.y==carril[j])
        {
         if(j-1<0);
         //se queda gilipollas
         else
         {
         for(i=0;i<n;i++)
         {
         if(carril[j-1]==jugador[i].posicion_animacion.y)
         {
         if((jugador[numero_jugador].posicion_animacion.x<jugador[i].posicion_animacion.x&&
             (jugador[numero_jugador].posicion_animacion.x+jugador[numero_jugador].posicion_animacion.w)<jugador[i].posicion_animacion.x)||
            (jugador[numero_jugador].posicion_animacion.x>jugador[i].posicion_animacion.x&&
             (jugador[numero_jugador].posicion_animacion.x+jugador[numero_jugador].posicion_animacion.w)>jugador[i].posicion_animacion.x))
         jugador[numero_jugador].posicion_animacion.y=carril[j-1];
         }
         }
         }
        }
        }
}
if(captura[tecla[1]])
{
switch (n)
{
case 2:
for(j=0;j<n;j++)
{
    if(jugador[numero_jugador].posicion_animacion.y==carril[j])
    {
        if(j+1>1);
         //se queda gilipollas
        else
        {
         for(i=0;i<n;i++)
         {
         if(carril[j+1]==jugador[i].posicion_animacion.y)
         {
         if((jugador[numero_jugador].posicion_animacion.x<jugador[i].posicion_animacion.x&&
             (jugador[numero_jugador].posicion_animacion.x+jugador[numero_jugador].posicion_animacion.w)<jugador[i].posicion_animacion.x)||
            (jugador[numero_jugador].posicion_animacion.x>jugador[i].posicion_animacion.x&&
             (jugador[numero_jugador].posicion_animacion.x+jugador[numero_jugador].posicion_animacion.w)>jugador[i].posicion_animacion.x))
         jugador[numero_jugador].posicion_animacion.y=carril[j+1];
         }
         }
        }
    }
}
break;
case 3:
for(j=0;j<n;j++)
{
    if(jugador[numero_jugador].posicion_animacion.y==carril[j])
    {
        if(j+1>2);
         //se queda gilipollas
        else
        {
         for(i=0;i<n;i++)
         {
         if(carril[j+1]==jugador[i].posicion_animacion.y)
         {
         if((jugador[numero_jugador].posicion_animacion.x<jugador[i].posicion_animacion.x&&
             (jugador[numero_jugador].posicion_animacion.x+jugador[numero_jugador].posicion_animacion.w)<jugador[i].posicion_animacion.x)||
            (jugador[numero_jugador].posicion_animacion.x>jugador[i].posicion_animacion.x&&
             (jugador[numero_jugador].posicion_animacion.x+jugador[numero_jugador].posicion_animacion.w)>jugador[i].posicion_animacion.x))
         jugador[numero_jugador].posicion_animacion.y=carril[j+1];
         }
         }
        }
    }
}
break;
case 4:
for(j=0;j<n;j++)
{
    if(jugador[numero_jugador].posicion_animacion.y==carril[j])
    {
        if(j+1>3);
         //se queda gilipollas
        else
        {
         for(i=0;i<n;i++)
         {
         if(carril[j+1]==jugador[i].posicion_animacion.y)
         {
         if((jugador[numero_jugador].posicion_animacion.x<jugador[i].posicion_animacion.x&&
             (jugador[numero_jugador].posicion_animacion.x+jugador[numero_jugador].posicion_animacion.w)<jugador[i].posicion_animacion.x)||
            (jugador[numero_jugador].posicion_animacion.x>jugador[i].posicion_animacion.x&&
             (jugador[numero_jugador].posicion_animacion.x+jugador[numero_jugador].posicion_animacion.w)>jugador[i].posicion_animacion.x))
         jugador[numero_jugador].posicion_animacion.y=carril[j+1];
         }
         }
        }
    }
}
break;
}
}
}
void limites_mapa(variables_jugador jugador[],int numero_jugador)//Limita el movimiento del jugador al plano de la pantalla
{
    const int velocidad_movimiento=2;

    if(jugador[numero_jugador].posicion_animacion.x>=1200)//Si el jugador llega a la posicion en cuestion avanzara 2 ya que se esta moviendo, pero retrocedera 2 al haber llegado al limite
        jugador[numero_jugador].posicion_animacion.x-=velocidad_movimiento;//En consecuencia el jugador no se mueve

    if (jugador[numero_jugador].posicion_animacion.x<=0)//Repetimos lo mismo en los lugares que nos interesan para definir el mapa
        jugador[numero_jugador].posicion_animacion.x+=velocidad_movimiento;

    if(jugador[numero_jugador].posicion_animacion.y<=0)
        jugador[numero_jugador].posicion_animacion.y+=velocidad_movimiento;

    if(jugador[numero_jugador].posicion_animacion.y>=750)
        jugador[numero_jugador].posicion_animacion.y-=velocidad_movimiento;

}


void generar_jugador(variables_jugador jugador[], int numero_jugador, SDL_Renderer *escenario, int numero_jugadores)//Establece valores predeterminados al jugador indicado
{
    int posicion_animacion;

    switch(numero_jugadores)
    {
        case 2:
            switch(numero_jugador)
            {
            case 0:
                posicion_animacion=150;
                break;
            case 1:
                posicion_animacion=400;
                break;
            }
        break;
        case 3:
            switch(numero_jugador)
            {
            case 0:
                posicion_animacion=100;
                break;
            case 1:
                posicion_animacion=300;
                break;
            case 2:
                posicion_animacion=500;
                break;
            }
        break;
        case 4:
            switch(numero_jugador)
            {
            case 0:
                posicion_animacion=25;
                break;
            case 1:
                posicion_animacion=225;
                break;
            case 2:
                posicion_animacion=425;
                break;
            case 3:
                posicion_animacion=625;
                break;
        break;
    }
    }

    jugador[numero_jugador].animacion=cargar_texturas("Animacion.png",escenario);

    SDL_QueryTexture(jugador[numero_jugador].animacion,NULL,NULL,&jugador[numero_jugador].ancho_animacion,&jugador[numero_jugador].alto_animacion);

    jugador[numero_jugador].recortar_animacion.x=jugador[numero_jugador].recortar_animacion.y=0; //Indica donde comenzara a recortarse la animacion
    jugador[numero_jugador].recortar_animacion.w=jugador[numero_jugador].ancho_animacion/4;
    jugador[numero_jugador].recortar_animacion.h=jugador[numero_jugador].alto_animacion/4;
    jugador[numero_jugador].posicion_animacion.x=50;
    jugador[numero_jugador].posicion_animacion.y=posicion_animacion;//Posicion inicial de la animacion
    jugador[numero_jugador].posicion_animacion.w=100;
    jugador[numero_jugador].posicion_animacion.h=75;

    for (int i=0;i<numero_jugadores;i++)
        jugador[i].fin=0;

}
void copiar_atributos(variables_jugador jugador[], int numero_jugadores, SDL_Renderer *escenario)//Copia los atributos de un jugador sobre el render
{
    for (int i = 0; i<numero_jugadores; i++)
        SDL_RenderCopy(escenario,jugador[i].animacion,&jugador[i].recortar_animacion,&jugador[i].posicion_animacion);
}

void destruir_atributos(variables_jugador jugador[], int numero_jugador)//Destruye los atributos de un jugador
{
    SDL_DestroyTexture(jugador[numero_jugador].animacion);
}


void multijugador(int numero_jugadores, float tiempo[])
{
    int tiempo_jugador1;
    int tiempo_jugador2;
    int tiempo_jugador3;
    int tiempo_jugador4;
    int red,blue,green;
    int contador=0;
    variables_jugador *jugador;

    SDL_Window *ventanaprincipal=NULL;//Ventana donde se ejecuta el juego
    SDL_Surface *superficieprincipal=NULL;//Superficie para la ventana, como si fuera un lienzo
    SDL_Renderer *escenario=NULL;//Representa cosas sobre la superficie, como si fuese la pintura


    SDL_Event evento; //Pulsar una tecla, mover el mouse... son eventos
    _Bool ejecutando=1; //Si el programa esta en proceso

    SDL_Init(SDL_INIT_EVERYTHING);//Inicializa la biblioteca SDL (no vamos a hacer comprobaciones de errores, por ahora)

    ventanaprincipal=SDL_CreateWindow("Carrera de caballos",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1200,750,NULL);//Crea una ventana, centrada, de dimensiones 1200x750
    superficieprincipal=SDL_GetWindowSurface(ventanaprincipal);//Aporta una superficie a la ventana
    escenario=SDL_CreateRenderer(ventanaprincipal,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);//Crea un render (necesario definirlo de esta forma para que funcione bien)

jugador=malloc(sizeof(variables_jugador)*numero_jugadores);//Indicamos para cuantos jugadores necesitamos espacio

if (jugador==NULL)//Comprobacion de error
{
    SDL_Log("Error");
    exit(-1);
}

else//Genera los jugadores con las funciones definidas de antes
{
    switch(numero_jugadores)
    {
    case 2:
        generar_jugador(jugador,0,escenario,numero_jugadores);
        generar_jugador(jugador,1,escenario,numero_jugadores);
    break;
    case 3:
        generar_jugador(jugador,0,escenario,numero_jugadores);
        generar_jugador(jugador,1,escenario,numero_jugadores);
        generar_jugador(jugador,2,escenario,numero_jugadores);
    break;
    case 4:
        generar_jugador(jugador,0,escenario,numero_jugadores);
        generar_jugador(jugador,1,escenario,numero_jugadores);
        generar_jugador(jugador,2,escenario,numero_jugadores);
        generar_jugador(jugador,3,escenario,numero_jugadores);
    break;
    }
}
    if (numero_jugadores==4)
    {
        for (int i=0; i<4;i++)
        {
        red=rand()%256;
        blue=rand()%256;
        green=rand()%256;
        SDL_SetTextureColorMod(jugador[i].animacion,red,blue,green);
        }
    }
    if (numero_jugadores==3)
    {
        for (int i=0; i<3;i++)
        {
        red=rand()%256;
        blue=rand()%256;
        green=rand()%256;
        SDL_SetTextureColorMod(jugador[i].animacion,red,blue,green);
        }
    }
    if (numero_jugadores==2)
    {
        for (int i=0; i<2;i++)
        {
        red=rand()%256;
        blue=rand()%256;
        green=rand()%256;
        SDL_SetTextureColorMod(jugador[i].animacion,red,blue,green);
        }
    }

    clock_t cl=clock();

   while(ejecutando)//El programa principal es un bucle que se reproduce infinitamente hasta que cambiemos el valor de ejecutando
    {

        while(SDL_PollEvent(&evento)!=0)//Procesa los eventos que se producen cada vez que se produce el bucle
        {                               //Finaliza el bucle cuando no queden eventos por procesar
            if(evento.type==SDL_QUIT)//Si el evento es quit (darle a la cruz roja) se sale del bucle y termina el juego
            {
                ejecutando=0;
            }
        }
        switch(numero_jugadores)
        {

        case 2:
        carril(jugador,numero_jugadores,0);
        carril(jugador,numero_jugadores,1);
        movimiento_jugador(jugador,0,&tiempo_jugador1,&contador);//Para mover los jugadores
        movimiento_jugador(jugador,1,&tiempo_jugador2,&contador);
        break;

        case 3:
        movimiento_jugador(jugador,0,&tiempo_jugador1,&contador);//Para mover los jugadores
        movimiento_jugador(jugador,1,&tiempo_jugador2,&contador);
        movimiento_jugador(jugador,2,&tiempo_jugador3,&contador);
        break;

        case 4:
        movimiento_jugador(jugador,0,&tiempo_jugador1,&contador);//Para mover los jugadores
        movimiento_jugador(jugador,1,&tiempo_jugador2,&contador);
        movimiento_jugador(jugador,2,&tiempo_jugador3,&contador);
        movimiento_jugador(jugador,3,&tiempo_jugador4,&contador);
        break;
        }
        for (int i=0;i<numero_jugadores;i++)
        {
            if (jugador[i].posicion_animacion.x>=900&&jugador[i].fin==0)
            {
                tiempo[i]=(clock()-cl)*1000/CLOCKS_PER_SEC;
                tiempo[i]/=1000;
                jugador[i].fin=1;

            }
        }
        SDL_RenderClear(escenario);//Limpia lo que haya en el escenario
        copiar_atributos(jugador,numero_jugadores,escenario);
        SDL_RenderPresent(escenario);//Presenta el render sobre la ventana principal


    }//Fin del bucle principal y por tanto de la partida

    free(jugador);
    destruir_atributos(jugador,0);
    destruir_atributos(jugador,1);
    SDL_DestroyRenderer(escenario);
    SDL_DestroyWindow(ventanaprincipal);
    ventanaprincipal=NULL; //Apunta todos los punteros a NULL
    superficieprincipal=NULL;

    SDL_Quit();//Sale de la libreria SDL
}
