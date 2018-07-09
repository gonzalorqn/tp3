#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#define TAM 10


int main()
{
    char seguir='s';
    int opcion=0;
    int index;
    EMovie* listaPeliculas;
    listaPeliculas = movie_init(TAM);
    index = movie_cargarArchivo(listaPeliculas,TAM);
    if(index!=0)
    {
        printf("Error al leer desde archivo");
    }


    while(seguir=='s')
    {
        system("cls");
        printf("1- Agregar pelicula\n");
        printf("2- Borrar pelicula\n");
        printf("3- Modificar pelicula\n");
        printf("4- Generar pagina web\n");
        printf("5- Salir\n");

        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                index = movie_add(listaPeliculas, TAM);
                if(index == 0)
                {
                    printf("\nPelicula agregada correctamente\n");
                }
                else
                {
                    printf("\nError al agregar pelicula\n");
                }
                system("pause");
                break;

            case 2:
                index = movie_remove(listaPeliculas,TAM);
                if(index == 0)
                {
                    printf("\n\nSe elimino la pelicula seleccionada.\n");
                }
                else if(index == -3)
                {
                    printf("\n\nSe cancelo la eliminacion.\n");
                }
                else
                {
                    printf("\nID invalido\n");
                }
                system("pause");
                break;

            case 3:
                system("pause");
               break;

            case 4:
                system("pause");
                break;

            case 5:
                seguir = 'n';
                break;

            default:
                printf("Opcion incorrecta\n\n");
                system("pause");
                break;
        }
    }

    return 0;
}
