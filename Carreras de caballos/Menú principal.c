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
    int puntuacion;
}registro_jugadores;

void ranking (registro_jugadores registro[], int dim);

int main (int argc, char* argv[])
{
    char instrucciones[]="Aqui instrucciones";
    char aux;
    int casos,nlineas=0,i=0;
    int numero_jugadores;
    float *tiempo;
    _Bool menu_on=1;
    registro_jugadores *registro;

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
            multijugador(numero_jugadores,tiempo);
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

            while(fscanf(registro_partidas,"%[^:]: %i\n",registro[i].nombre,&registro[i].puntuacion)!=EOF)
                i++;

            ranking(registro,nlineas);
            for (int i=0;i<nlineas;i++)
                printf("%s: %i\n",registro[i].nombre,registro[i].puntuacion);
            printf("\n");
            fclose(registro_partidas);
            break;
        case 4:
            break;
        default:
            break;

        }
        for (int i=0;i<numero_jugadores;i++)
            printf("Jugador %i: %.3f s\n",i+1,tiempo[i]);
        free(tiempo);

    }while(menu_on);


    return 0;
}

void ranking (registro_jugadores registro[], int dim)
{
    int aux;
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
