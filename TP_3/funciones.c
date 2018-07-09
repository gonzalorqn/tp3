#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#define OCUPADO 1
#define LIBRE 0

EMovie* movie_init(int tam)
{
    EMovie* aux = NULL;
    int i;
    if(tam > 0)
    {
        aux = (EMovie*) malloc(sizeof(EMovie)*tam);
    }
    if(aux!=NULL)
    {
        for(i=0; i<tam; i++)
        {
            (aux+i)->estado = LIBRE;
            (aux+i)->id = 0;
        }
    }
    return aux;
}

int movie_add(EMovie* lista, int tam)
{
    int ret = -1;
    int guardar;
    int indice;
    int id;
    char titulo[51];
    char genero[21];
    int duracion;
    char descripcion[251];
    int puntaje;
    char linkImagen[251];

    if(lista!=NULL && tam>0)
    {
        ret = -2;
        indice = movie_buscarLugarLibre(lista,tam);
        if(indice >= 0)
        {
            system("cls");
            ret = -3;
            id = movie_generarId(lista, tam);

            if(id >= 0)
            {
                ret = -4;

                do
                {
                    printf("-Ingrese titulo (hasta 50 caracteres): ");
                    fflush(stdin);
                    gets(titulo);
                }while(strlen(titulo) >= 50);

                do
                {
                    printf("-Ingrese genero (hasta 20 caracteres): ");
                    fflush(stdin);
                    gets(genero);
                }while(strlen(genero) >= 20);

                do
                {
                    printf("-Ingrese duracion en minutos (hasta 250 min): ");
                    scanf("%d", &duracion);
                }while(!(duracion > 0 && duracion <= 250));

                do
                {
                    printf("-Ingrese descripcion (hasta 250 caracteres): ");
                    fflush(stdin);
                    gets(descripcion);
                }while(strlen(descripcion) >= 250);

                do
                {
                    printf("-Ingrese puntaje entre 0 y 10: ");
                    scanf("%d", &puntaje);
                }while(!(puntaje >= 0 && puntaje <= 10));

                do
                {
                    printf("-Ingrese link de imagen (hasta 250 caracteres): ");
                    fflush(stdin);
                    gets(linkImagen);
                }while(strlen(linkImagen) >= 250);

                (lista+indice)->id = id;
                (lista+indice)->duracion = duracion;
                (lista+indice)->puntaje = puntaje;
                (lista+indice)->estado = OCUPADO;
                strcpy((lista+indice)->titulo, titulo);
                strcpy((lista+indice)->genero, genero);
                strcpy((lista+indice)->descripcion, descripcion);
                strcpy((lista+indice)->linkImagen, linkImagen);

                ret = 0;

                guardar = movie_guardarArchivo(lista, tam);

                if(guardar == 0)
                {
                    printf("\nSe guardo archivo correctamente\n");
                }
                else
                {
                    printf("\nError al guardar archivo\n");
                }
            }
        }
    }
    return ret;
}

int movie_buscarLugarLibre(EMovie* lista,int limite)
{
    int retorno = -1;
    int i;
    if(lista!=NULL && limite>0)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if((lista+i)->estado == LIBRE)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int movie_generarId(EMovie* lista, int limite)
{
    int retorno = -1;
    int i;

    if(lista!=NULL && limite>0)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if((lista+i)->estado == OCUPADO && (lista+i)->id > retorno)
            {
                retorno = (lista+i)->id;
            }
        }
        retorno++;
    }
    return retorno;
}

int movie_guardarArchivo(EMovie* lista, int limite)
{
    int retorno = -1;
    FILE* pFile;
    int i;

    if(lista!=NULL && limite > 0)
    {
        retorno = -2;
        pFile = fopen("movies.bin", "wb");

        if(pFile!=NULL)
        {
            retorno = 0;
            for(i=0;i<limite;i++)
            {
                if((lista+i)->estado == OCUPADO)
                {
                    fwrite((lista+i), sizeof(EMovie), 1, pFile);
                }
            }
            fclose(pFile);
        }
    }
    return retorno;
}

int movie_cargarArchivo(EMovie* lista, int limite)
{
    int retorno = -1;
    FILE* pFile;
    int indice;
    EMovie movie;
    int cant;

    if(lista!=NULL && limite > 0)
    {
        retorno = -2;
        pFile = fopen("movies.bin", "rb");

        if(pFile!=NULL)
        {
            retorno = 0;

            while(!feof(pFile))
            {
                indice = movie_buscarLugarLibre(lista,limite);

                cant = fread(&movie, sizeof(EMovie), 1, pFile);
                if(cant!=1)
                {
                    if(feof(pFile))
                        break;
                    else
                    {
                        printf("\nError al leer ultimo registro");
                        break;
                    }
                }
                *(lista+indice) = movie;
            }
            fclose(pFile);
        }
    }
    return retorno;
}

int movie_remove(EMovie* lista,int tam)
{
    int retorno = -1;
    int idRemove;
    int index;
    char confirmar;
    int guardar;

    if(lista!=NULL && tam>0)
    {
        retorno = -2;
        movie_mostrarTitulos(lista,tam);
        printf("\nIngrese ID de la pelicula para eliminar: ");
        scanf("%d",&idRemove);

        index = movie_buscarId(lista,tam,idRemove);
        if(index >= 0)
        {
            retorno = -3;
            printf("\nSeguro que desea eliminar esta pelicula?(s/n): ");
            fflush(stdin);
            scanf("%c",&confirmar);
            if(confirmar == 's')
            {
                retorno = 0;
                (lista+index)->estado = LIBRE;
                guardar = movie_guardarArchivo(lista, tam);

                if(guardar == 0)
                {
                    printf("\nSe guardo archivo correctamente\n");
                }
                else
                {
                    printf("\nError al guardar archivo\n");
                }
            }
        }
    }
    return retorno;
}

void movie_mostrar(EMovie* lista,int limite)
{
    int i;
    if(lista!=NULL && limite>0)
    {
        system("cls");
        for(i=0;i<limite;i++)
        {
            if((lista+i)->estado == OCUPADO)
            {
                movie_mostrarUno(lista+i);
            }
        }
    }
}

void movie_mostrarUno(EMovie* mostrar)
{
    if(mostrar!=NULL)
    {
        printf("ID: %d\nTitulo: %s\nGenero: %s\nDuracion: %d\nDescripcion: %s\nPuntaje: %d\nLink imagen: %s\n\n",mostrar->id,mostrar->titulo,mostrar->genero,mostrar->duracion,mostrar->descripcion,mostrar->puntaje,mostrar->linkImagen);
    }
}

void movie_mostrarTitulos(EMovie* lista,int limite)
{
    int i;
    if(lista!=NULL && limite>0)
    {
        system("cls");
        for(i=0;i<limite;i++)
        {
            if((lista+i)->estado == OCUPADO)
            {
                printf("ID: %d\nTitulo: %s\n\n",(lista+i)->id,(lista+i)->titulo);
            }
        }
    }
}

int movie_buscarId(EMovie* lista,int limite,int id)
{
    int retorno = -1;
    int i;
    if(lista!=NULL && limite>0 && id>=0)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if((lista+i)->estado == OCUPADO && (lista+i)->id == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int movie_modificar(EMovie* lista,int tam)
{
    int retorno = -1;
    int idModificar;
    int index;
    char seguir='s';
    int opcion=0;
    char titulo[51];
    char genero[21];
    int duracion;
    char descripcion[251];
    int puntaje;
    char linkImagen[251];
    int guardar;

    if(lista!=NULL && tam>0)
    {
        retorno = -2;
        movie_mostrar(lista,tam);
        printf("\nIngrese ID de la pelicula para modificar: ");
        scanf("%d",&idModificar);

        index = movie_buscarId(lista,tam,idModificar);
        if(index >= 0)
        {
            retorno = 0;
            while(seguir=='s')
            {
                system("cls");
                printf("1- Modificar titulo\n");
                printf("2- Modificar genero\n");
                printf("3- Modificar duracion\n");
                printf("4- Modificar descripcion\n");
                printf("5- Modificar puntaje\n");
                printf("6- Modificar link de imagen\n");
                printf("7- Salir\n");

                scanf("%d",&opcion);

                switch(opcion)
                {
                    case 1:
                        system("cls");
                        do
                        {
                            printf("-Ingrese titulo (hasta 50 caracteres): ");
                            fflush(stdin);
                            gets(titulo);
                        }while(strlen(titulo) >= 50);

                        strcpy((lista+index)->titulo, titulo);
                        break;

                    case 2:
                        system("cls");
                        do
                        {
                            printf("-Ingrese genero (hasta 20 caracteres): ");
                            fflush(stdin);
                            gets(genero);
                        }while(strlen(genero) >= 20);

                        strcpy((lista+index)->genero, genero);
                        break;

                    case 3:
                        system("cls");
                        do
                        {
                            printf("-Ingrese duracion en minutos (hasta 250 min): ");
                            scanf("%d", &duracion);
                        }while(!(duracion > 0 && duracion <= 250));

                        (lista+index)->duracion = duracion;
                        break;

                    case 4:
                        system("cls");
                        do
                        {
                            printf("-Ingrese descripcion (hasta 250 caracteres): ");
                            fflush(stdin);
                            gets(descripcion);
                        }while(strlen(descripcion) >= 250);

                        strcpy((lista+index)->descripcion, descripcion);
                        break;

                    case 5:
                        system("cls");
                        do
                        {
                            printf("-Ingrese puntaje entre 0 y 10: ");
                            scanf("%d", &puntaje);
                        }while(!(puntaje >= 0 && puntaje <= 10));

                        (lista+index)->puntaje = puntaje;
                        break;

                    case 6:
                        system("cls");
                        do
                        {
                            printf("-Ingrese link de imagen (hasta 250 caracteres): ");
                            fflush(stdin);
                            gets(linkImagen);
                        }while(strlen(linkImagen) >= 250);

                        strcpy((lista+index)->linkImagen, linkImagen);
                        break;

                    case 7:
                        seguir = 'n';
                        break;

                    default:
                    printf("Opcion incorrecta\n\n");
                    system("pause");
                    break;
                }
            }
            guardar = movie_guardarArchivo(lista, tam);

            if(guardar == 0)
            {
                printf("\nSe guardo archivo correctamente\n");
            }
            else
            {
                printf("\nError al guardar archivo\n");
            }
        }
    }
    return retorno;
}

int movie_generarPaginaWeb(EMovie* lista,int tam)
{
    int retorno = -1;
    int i;

    if(lista!=NULL && tam>0)
    {
        retorno = -2;
    }
    return retorno;
}







