#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct
{
    int id;
    char titulo[51];
    char genero[21];
    int duracion;
    char descripcion[251];
    int puntaje;
    char linkImagen[251];
    int estado;
}EMovie;


/**
 *  Genera un archivo html a partir de las peliculas cargadas en el archivo binario.
 * \param lista Puntero a array de peliculas.
 * \param tam Cantidad de peliculas.
 * \return int [-1] si la lista es nula o limite invalido
 *             [-2]
 *             [0]  todo ok
 */
int movie_generarPaginaWeb(EMovie* lista,int tam);


/**
 *  Guarda espacio en memoria para una lista de EMovies de tam peliculas e inicializa id y estado en 0.
 * \param tam Cantidad de peliculas.
 * \return EMovie* Puntero a array de peliculas.
 *
 */
EMovie* movie_init(int tam);


/**
 *  Agrega una nueva pelicula a la lista.
 * \param lista Puntero a array de peliculas.
 * \param tam Cantidad de peliculas.
 * \return int [-1] si la lista es nula o limite invalido
 *             [-2] si no hay lugar
 *             [-3] si hubo error al generar id
 *             [-4] si hubo error al cargar datos
 *             [0]  todo ok
 */
int movie_add(EMovie* lista, int tam);


/**
 *  Obtiene el primer indice libre del array.
 * \param lista Puntero a array de peliculas.
 * \param limite Cantidad de peliculas.
 * \return int [-1] si la lista es nula o limite invalido
 *             [-2] si no hay lugar
 *             [0]  todo ok
 */
int movie_buscarLugarLibre(EMovie* lista,int limite);


/**
 *  Genera ID's autoincrementales
 * \param lista Puntero a array de peliculas.
 * \param limite Cantidad de peliculas.
 * \return int [-1] si la lista es nula o limite invalido
 *             [id] el id libre mas pequenio
 */
int movie_generarId(EMovie* lista, int limite);


/**
 *  Guarda en un archivo binario el array de peliculas
 * \param lista Puntero a array de peliculas.
 * \param limite Cantidad de peliculas.
 * \return int [-1] si la lista es nula o limite invalido
 *             [-2] si hubo error al guardar archivo
 *             [0]  todo ok
  */
int movie_guardarArchivo(EMovie* lista, int limite);


/**
 *  Carga datos de peliculas desde un archivo binario
 * \param lista Puntero a array de peliculas.
 * \param limite Cantidad de peliculas.
 * \return int [-1] si la lista es nula o limite invalido
 *             [-2] si hubo error al cargar archivo
 *             [0]  todo ok
 */
int movie_cargarArchivo(EMovie* lista, int limite);


/**
 *  Elimina una pelicula de la lista.
 * \param lista Puntero a array de peliculas.
 * \param tam Cantidad de peliculas.
 * \return int [-1] si la lista es nula o limite invalido
 *             [-2] si el id es invalido
 *             [-3] si se cancela la operacion
 *             [0]  todo ok
 */
int movie_remove(EMovie* lista,int tam);


/**
 *  Muestra todas las peliculas dadas de alta.
 * \param lista Puntero a array de peliculas.
 * \param limite Cantidad de peliculas.
 * \return void
 *
 */
void movie_mostrar(EMovie* lista,int limite);


/**
 *  Muestra una pelicula.
 * \param mostrar Puntero a la pelicula a mostrar.
 * \return void
 *
 */
void movie_mostrarUno(EMovie* mostrar);


/**
 *  Muestra el id y titulo de las peliculas dadas de alta.
 * \param lista Puntero a array de peliculas.
 * \param limite Cantidad de peliculas.
 * \return void
 *
 */
void movie_mostrarTitulos(EMovie* lista,int limite);


/**
 *  Obtiene el indice del id pasado como parametro.
 * \param lista Puntero a array de peliculas.
 * \param limite Cantidad de peliculas.
 * \param id ID a ser buscado.
 * \return int [-1] si la lista es nula o limite invalido
 *             [-2] si no encontro el id
 *             [id]  todo ok
 */
int movie_buscarId(EMovie* lista,int limite,int id);


/**
 *  Modifica la pelicula seleccionada.
 * \param lista Puntero a array de peliculas.
 * \param tam Cantidad de peliculas.
 * \return int [-1] si la lista es nula o limite invalido
 *             [-2] si el id es invalido
 *             [0]  todo ok
 */
int movie_modificar(EMovie* lista,int tam);

#endif // FUNCIONES_H_INCLUDED
