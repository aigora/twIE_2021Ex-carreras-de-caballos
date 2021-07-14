#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Funcionesp.h"

typedef struct
{
    char nombre[50];
    float puntuacion;
}registro_jugadores;

void ranking (registro_jugadores registro[], int dim);

int main (int argc, char* argv[])
{
    char instrucciones[]=" Juego multijugador, de dos a cuatro jugadores\n para avanzar tendras que pulsar de manera intermitente\n el boton asignado a cada jugador, con la opcion de cambiar\n de carriles con dos botones asignados,un total de tres botones por jugador.\n Ganara el que menos tiempo tarde en llegar al otro lado de la pantalla\n Si un caballo empuja a otro por atras, lo aturdira para el resto de la partida\n y no podra seguir avanzando, con lo que no se contara su tiempo en el transcurso de la carrera\n Jugador1:\n Espacio para avanzar\n N carril de la izquierda\n B carril de la derecha\n Jugador2:\n A para avanzar\n Q carril de la izquierda\n Z carril de la derecha\n Jugador3:\n Flecha hacia arriba(UP) para avanzar\n Flecha hacia la izquierda(LEFT) carril de la izquierda\n Flecha hacia la derecha(RIGHT) carril de la derecha\n Jugador4:\n 6 para avanzar\n 5 carril de la izquierda\n 7 carril de la derecha";
    char aux;
    int casos,nlineas=0,i=0;
    int numero_jugadores;
    float *tiempo;
    int menu_on=1;
    registro_jugadores *registro;
    registro_jugadores *registrar;

    FILE *registro_partidas;

    registro_partidas=fopen("Registro.txt","r");
    fclose(registro_partidas);


    printf("Carrera de caballos\n\n");

    do
    {

        printf("1.- Instrucciones\n2.- Jugar (2-4 personas)\n3.- Ver puntuaciones\n4.- Salir\n");
        scanf("%i",&casos);

        switch (casos)
        {
        case 1:
            printf("%s\n\n",instrucciones);
            break;
        case 2:
            printf("%cNumero de jugadores?\n",168);
            scanf("%i",&numero_jugadores);
            tiempo=malloc(sizeof(float)*numero_jugadores);
            registrar=malloc(sizeof(registro_jugadores)*numero_jugadores);

            for (int i=0;i<numero_jugadores;i++)
            {
                printf("Nombre jugador %i:\n",i+1);
                scanf("%50s",registrar[i].nombre);
            }

            multijugador(numero_jugadores,tiempo);

            for (int i=0;i<numero_jugadores;i++)
                printf("Jugador %i: %.3f s\n",i+1,tiempo[i]);

            registro_partidas=fopen("Registro.txt","a");

            for (int i=0;i<numero_jugadores;i++)
                fprintf(registro_partidas,"%s: %.3f\n",registrar[i].nombre,tiempo[i]);

            fclose(registro_partidas);
            free(tiempo);
            free(registrar);
            break;
        case 3:
            registro_partidas = fopen("Registro.txt","r");
            while(fscanf(registro_partidas,"%c",&aux)!=EOF)
                if (aux=='\n')
                    nlineas++;

            fseek(registro_partidas,0,SEEK_SET);
            registro = malloc(sizeof(registro_jugadores)*nlineas);

            if (registro==NULL)
            {
                printf("Error");
                exit(-1);
            }

            while(fscanf(registro_partidas,"%[^:]: %f\n",registro[i].nombre,&registro[i].puntuacion)!=EOF)
                i++;

            ranking(registro,nlineas);
            for (int i=0;i<nlineas;i++)
                printf("%s: %.3f\n",registro[i].nombre,registro[i].puntuacion);
            printf("\n");
            nlineas=0;
            i=0;
            free(registro);
            fclose(registro_partidas);
            break;
        case 4:
            menu_on=0;
            break;
        default:
            break;

        }

    }while(menu_on);


    return 0;
}

void ranking (registro_jugadores registro[], int dim)
{
    float aux;
    char name_aux[50];

    for (int i=0;i<dim-1;i++)
    {
        for (int j=i+1;j<dim;j++)
        {
            if (registro[i].puntuacion<registro[j].puntuacion)
            {
                aux=registro[i].puntuacion;
                strcpy(name_aux,registro[i].nombre);
                registro[i].puntuacion=registro[j].puntuacion;
                strcpy(registro[i].nombre,registro[j].nombre);
                registro[j].puntuacion=aux;
                strcpy(registro[j].nombre,name_aux);
            }
        }
    }
}
