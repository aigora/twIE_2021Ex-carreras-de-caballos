#include <stdio.h>
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Funciones_principales.h"
#include <sys/time.h>
#include <stdlib.h>

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

void movimiento_jugador(variables_jugador jugador[], int numero_jugador, int *tiempo)//Permite al usuario interactuar con su jugador
{
    const Uint8 *captura=SDL_GetKeyboardState(NULL);//Necesario para poder usar SDL_Scancode
    int velocidad_movimiento=5;
    SDL_Scancode tecla;

    if(numero_jugador==0)//En funcion del jugador en cuestion usara las teclas asdw o las flechas
    tecla=SDL_SCANCODE_SPACE;
    if(numero_jugador==1)
    tecla=SDL_SCANCODE_LSHIFT;
    if(numero_jugador==2)
    tecla=SDL_SCANCODE_RSHIFT;
    if(numero_jugador==3)
    tecla=SDL_SCANCODE_6;

    if(captura[teclas])//Detecta si el una tecla esta pulsada, entoces se ejecuta la condicion
        {
            jugador[numero_jugador].recortar_animacion.y=jugador[numero_jugador].alto_animacion/4;
            jugador[numero_jugador].posicion_animacion.x+=velocidad_movimiento;//Mueve la animacion por el plano de la pantalla
            *tiempo+=1;
            if(*tiempo>=5)//Este if sirve para crear la animacion, el tiempo simplemente sirve para que no la ejecute demasiado rapido
            {
                jugador[numero_jugador].recortar_animacion.x+=jugador[numero_jugador].ancho_animacion/5;//Pasa a recortar la siguiente fase de la animacion
                if(jugador[numero_jugador].recortar_animacion.x>=jugador[numero_jugador].ancho_animacion)
                    jugador[numero_jugador].recortar_animacion.x=0;//Cuando llega a la ultima fase de la animacion vuelve a la primera fase
                *tiempo=0;
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


void generar_jugador(variables_jugador jugador[], int numero_jugador, SDL_Renderer *escenario, _Bool cargar)//Establece valores predeterminados al jugador indicado
{
    int posicion_animacion,posicion_vidas,posicion_municion;
    if (numero_jugador==0) //En funcion del jugador aparecera en un lugar u otro de la pantalla
    {
        posicion_animacion=500;
        posicion_vidas=700;
        posicion_municion=600;
    }
    else
    {
        posicion_animacion=300;
        posicion_vidas=200;
        posicion_municion=100;
    }
    jugador[numero_jugador].animacion=cargar_texturas("Animation.png",escenario);

    SDL_QueryTexture(jugador[numero_jugador].animacion,NULL,NULL,&jugador[numero_jugador].ancho_animacion,&jugador[numero_jugador].alto_animacion);

    jugador[numero_jugador].recortar_animacion.x=jugador[numero_jugador].recortar_animacion.y=0; //Indica donde comenzara a recortarse la animacion
    jugador[numero_jugador].recortar_animacion.w=jugador[numero_jugador].ancho_animacion/5;
    jugador[numero_jugador].recortar_animacion.h=jugador[numero_jugador].alto_animacion/4;
    jugador[numero_jugador].posicion_animacion.x=jugador[numero_jugador].posicion_animacion.y=posicion_animacion;//Posicion inicial de la animacion
    jugador[numero_jugador].posicion_animacion.w=jugador[numero_jugador].posicion_animacion.h=50;

}
void copiar_atributos(variables_jugador jugador[], int numero_jugador, SDL_Renderer *escenario)//Copia los atributos de un jugador sobre el render
{
    SDL_RenderCopy(escenario,jugador[numero_jugador].animacion,&jugador[numero_jugador].recortar_animacion,&jugador[numero_jugador].posicion_animacion);
}

void destruir_atributos(variables_jugador jugador[], int numero_jugador)//Destruye los atributos de un jugador
{
    SDL_DestroyTexture(jugador[numero_jugador].animacion);
}

void fichero (variables_jugador jugador[], int numero_jugador, char nombre_partida[])
{
    FILE *datos_partida;
    int i;

    datos_partida=fopen(nombre_partida,"w");

    if (datos_partida==NULL)
    {
        printf("Error al guardar el juego");
    }

    else
    {
        for (i=0; i<=1;i++)
        fprintf(datos_partida,"%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i ",
                jugador[i].posicion_animacion.x,jugador[i].posicion_animacion.y,jugador[i].posicion_animacion.w,jugador[i].posicion_animacion.h,
                jugador[i].recortar_animacion.x,jugador[i].recortar_animacion.y,jugador[i].recortar_animacion.w,jugador[i].recortar_animacion.h,
                jugador[i].posicion_vidas.x,jugador[i].posicion_vidas.y,jugador[i].posicion_vidas.w,jugador[i].posicion_vidas.h,
                jugador[i].recortar_vidas.x,jugador[i].recortar_vidas.y,jugador[i].recortar_vidas.w,jugador[i].recortar_vidas.h,
                jugador[i].numero_vidas,jugador[i].contador_bala);

        fprintf(datos_partida,"\n\n");

        for (i=0;i<=1;i++)
        {
        fprintf(datos_partida,"Numero de jugador %i\n\n",i);

        fprintf(datos_partida,"Numero de vidas: %i\n",jugador[i].numero_vidas);
        fprintf(datos_partida,"Balas usadas: %i\n",jugador[i].contador_bala);

        fprintf(datos_partida,"Recargando, intersecan, balas existe: %i %i %i\n",jugador[i].recargando,jugador[i].intersecan,jugador[i].bala_existe);

        fprintf(datos_partida,"Posicion bala: x:%i y:%i w:%i h:%i\n",jugador[i].posicion_bala.x,jugador[i].posicion_bala.y,jugador[i].posicion_bala.w,jugador[i].posicion_bala.h);

        fprintf(datos_partida,"Posicion animacion: x:%i y:%i w:%i h:%i\n",jugador[i].posicion_animacion.x,jugador[i].posicion_animacion.y,jugador[i].posicion_animacion.w,jugador[i].posicion_animacion.h);
        fprintf(datos_partida,"Recortar animacion: x:%i y:%i w:%i h:%i\n",jugador[i].recortar_animacion.x,jugador[i].recortar_animacion.y,jugador[i].recortar_animacion.w,jugador[i].recortar_animacion.h);

        fprintf(datos_partida,"Posicion municion: x:%i y:%i w:%i h:%i\n",jugador[i].posicion_municion.x,jugador[i].posicion_municion.y,jugador[i].posicion_municion.w,jugador[i].posicion_municion.h);
        fprintf(datos_partida,"Recortar municion: x:%i y:%i w:%i h:%i\n",jugador[i].recortar_municion.x,jugador[i].recortar_municion.y,jugador[i].recortar_municion.w,jugador[i].recortar_municion.h);

        fprintf(datos_partida,"Posicion vidas: x:%i y:%i w:%i h:%i\n",jugador[i].posicion_vidas.x,jugador[i].posicion_vidas.y,jugador[i].posicion_vidas.w,jugador[i].posicion_vidas.h);
        fprintf(datos_partida,"Recortar vidas: x:%i y:%i w:%i h:%i\n",jugador[i].recortar_vidas.x,jugador[i].recortar_vidas.y,jugador[i].recortar_vidas.w,jugador[i].recortar_vidas.h);

        fprintf(datos_partida,"Trampa cargada: %i\n",jugador[i].interseca_trampa);

        fprintf(datos_partida,"\n\n");
        }
    }

    fclose(datos_partida);
}

void cargar_partida(variables_jugador jugador[], int numero_jugador, _Bool cargar, SDL_Renderer *escenario, char nombre_partida[])
{
    FILE *puntero_datos;
    int i=0;

    if (cargar)
    {
    puntero_datos=fopen(nombre_partida,"r");
    for (i=0;i<2;i++)
    fscanf(puntero_datos,"%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i ",
            &jugador[i].posicion_animacion.x,&jugador[i].posicion_animacion.y,&jugador[i].posicion_animacion.w,&jugador[i].posicion_animacion.h,
            &jugador[i].recortar_animacion.x,&jugador[i].recortar_animacion.y,&jugador[i].recortar_animacion.w,&jugador[i].recortar_animacion.h,
            &jugador[i].posicion_vidas.x,&jugador[i].posicion_vidas.y,&jugador[i].posicion_vidas.w,&jugador[i].posicion_vidas.h,
            &jugador[i].recortar_vidas.x,&jugador[i].recortar_vidas.y,&jugador[i].recortar_vidas.w,&jugador[i].recortar_vidas.h,
            &jugador[i].numero_vidas,&jugador[i].contador_bala);

    fclose(puntero_datos);
    }
}

void datos_partida(char nombre_partida[50])
{
    FILE *puntero_datos;

    char aux;
    char funciona=1;

    puntero_datos=fopen(nombre_partida,"r");

    fseek(puntero_datos,0,SEEK_SET);
    while(fscanf(puntero_datos,"%c",&aux)!=EOF && funciona)
        if (aux=='\n')
        funciona=0;

    while(fscanf(puntero_datos,"%c",&aux)!=EOF)
        printf("%c",aux);


    fclose(puntero_datos);
}



void multijugador(_Bool cargar, char nombre_partida[], int victorias[],int numero_victoria, _Bool revancha, int numero_mapa,int)
{
    int tiempo_jugador1;
    int tiempo_jugador2;
    int tiempo_jugador3;
    int tiempo_jugador4;
    int control=0;
    long int segundos;
    long int microsegundos;
    struct timeval begin,end;
    int n;

    SDL_Window *ventanaprincipal=NULL;//Ventana donde se ejecuta el juego
    SDL_Surface *superficieprincipal=NULL;//Superficie para la ventana, como si fuera un lienzo
    SDL_Renderer *escenario=NULL;//Representa cosas sobre la superficie, como si fuese la pintura


    SDL_Event evento; //Pulsar una tecla, mover el mouse... son eventos
    _Bool ejecutando=1; //Si el programa esta en proceso

    SDL_Init(SDL_INIT_EVERYTHING);//Inicializa la biblioteca SDL (no vamos a hacer comprobaciones de errores, por ahora)

    ventanaprincipal=SDL_CreateWindow("CarreraCaballos",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1200,750,NULL);//Crea una ventana, centrada, de dimensiones 1200x750
    superficieprincipal=SDL_GetWindowSurface(ventanaprincipal);//Aporta una superficie a la ventana
    escenario=SDL_CreateRenderer(ventanaprincipal,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);//Crea un render (necesario definirlo de esta forma para que funcione bien)

SDL_Texture *texto_ganador=NULL;
SDL_Rect posicion_texto; //La posicion en la que estara el texto al finalizar el programa
posicion_texto.x=300;
posicion_texto.y=150;
posicion_texto.w=posicion_texto.h=0;

variables_jugador *jugador;//Se define un puntero del tipo variables_jugador

printf("Introduzca el numero de jugadores(de 2 a 4)\n");
scanf("%i",&n);

jugador=malloc(sizeof(variables_jugador)*n);//Indicamos para cuantos jugadores necesitamos espacio

if (jugador==NULL)//Comprobacion de error
{
    SDL_Log("Error");
    exit(-1);
}

else//Genera los jugadores con las funciones definidas de antes
{
    switch(n)
    {
case 2:
    generar_jugador(jugador,0,escenario,cargar);
    generar_jugador(jugador,1,escenario,cargar);
break;
case 3:
    generar_jugador(jugador,0,escenario,cargar);
    generar_jugador(jugador,1,escenario,cargar);
    generar_jugador(jugador,2,escenario,cargar);
break;
case 4:
    generar_jugador(jugador,0,escenario,cargar);
    generar_jugador(jugador,1,escenario,cargar);
    generar_jugador(jugador,2,escenario,cargar);
    generar_jugador(jugador,3,escenario,cargar);
break;
    }
}

   while(ejecutando)//El programa principal es un bucle que se reproduce infinitamente hasta que cambiemos el valor de ejecutando
    {
        gettimeofday(&begin, 0);

        while(SDL_PollEvent(&evento)!=0)//Procesa los eventos que se producen cada vez que se produce el bucle
        {                               //Finaliza el bucle cuando no queden eventos por procesar
            if(evento.type==SDL_QUIT)//Si el evento es quit (darle a la cruz roja) se sale del bucle y termina el juego
            {
                ejecutando=0;
            }
        switch(n)
        {
        case 2:
        movimiento_jugador(jugador,0,&tiempo_jugador1);//Para mover los jugadores
        movimiento_jugador(jugador,1,&tiempo_jugador2);
        limites_mapa(jugador,0);//Donde se pueden mover
        limites_mapa(jugador,1);
        break;
        case 3:
        movimiento_jugador(jugador,0,&tiempo_jugador1);//Para mover los jugadores
        movimiento_jugador(jugador,1,&tiempo_jugador2);
        movimiento_jugador(jugador,2,&tiempo_jugador3);
        limites_mapa(jugador,0);//Donde se pueden mover
        limites_mapa(jugador,1);
        limites_mapa(jugador,2);
        break;
        case 4:
        movimiento_jugador(jugador,0,&tiempo_jugador1);//Para mover los jugadores
        movimiento_jugador(jugador,1,&tiempo_jugador2);
        movimiento_jugador(jugador,2,&tiempo_jugador3);
        movimiento_jugador(jugador,3,&tiempo_jugador4);
        limites_mapa(jugador,0);//Donde se pueden mover
        limites_mapa(jugador,1);
        limites_mapa(jugador,2);
        limites_mapa(jugador,3);
        break;        
        }
        SDL_RenderClear(escenario);//Limpia lo que haya en el escenario

        copiar_atributos(jugador,0,escenario); //Pega en el escenario las caracteristicas de cada jugador tras acabar el bucle
        copiar_atributos(jugador,1,escenario);

        SDL_RenderPresent(escenario);//Presenta el render sobre la ventana principal

        gettimeofday(&end, 0);
        segundos = end.tv_sec - begin.tv_sec;
        microsegundos = end.tv_usec - begin.tv_usec;
        tiempo_mina+= segundos + microsegundos*1e-6;

        if (jugador[0].numero_vidas==0 || jugador[1].numero_vidas==0)
        {
            if (jugador[0].numero_vidas==0)
            {
                texto_ganador=cargar_texturas("Player2 wins.png", escenario);
                victorias[1]++;
            }

            if (jugador[1].numero_vidas==0)
            {
               texto_ganador=cargar_texturas("Player1 wins.png",escenario);
               victorias[0]++;
            }

            SDL_RenderClear(escenario);
            for (int i=0;i<300;i++)
            {
                control++;
                posicion_texto.h++;
                posicion_texto.w++;
                switch(control)
                {
                case 2:
                    posicion_texto.x+=20;
                    break;
                case 4:
                    posicion_texto.y+=20;
                    break;
                case 6:
                    posicion_texto.x-=20;
                    break;
                case 8:
                    posicion_texto.y-=20;
                    break;
                case 10:
                    control=0;
                    break;
                }

                SDL_RenderCopy(escenario,texto_ganador,NULL,&posicion_texto);
                SDL_RenderPresent(escenario);
            }
                ejecutando=0;
        }

    }//Fin del bucle principal y por tanto de la partida

    if (revancha==0)
    fichero(jugador,0,nombre_partida);

    free(barrera);
    free(jugador);//Libera lo reservado con malloc anteriormente
    SDL_DestroyTexture(texto_ganador);//Destruye todas las texturas creadas, la ventana, el render y lasuperficie
    destruir_atributos(jugador,0);
    destruir_atributos(jugador,1);
    SDL_DestroyRenderer(escenario);
    SDL_DestroyWindow(ventanaprincipal);
    ventanaprincipal=NULL; //Apunta todos los punteros a NULL
    superficieprincipal=NULL;

    for (int i=0;i<2;i++)
    jugador[i].municion=jugador[i].vidas=jugador[i].animacion=jugador[i].bala=NULL;

    SDL_Quit();//Sale de la libreria SDL
}