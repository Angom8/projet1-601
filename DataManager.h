#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>

/*

CONSTANTES DU PROJET 

*/

#define BLOC_SIZE 128


/* Il se peut qu'il y ait quelques résidus de TP */


/**
* Initialise la lecture du fichier
*/
void initFileRead(char * s, int d);

/**
* Vérifie si le fichier est ok
*/
int is_opened();

/**
* Détermine l'existence d'un fichier à partir d'une chaine de caractères passée en paramètre
*/
int file_exists(char *);

/**
* Lit le bloc n d'un fichier
*/
char * readBloc(int n);

/**
* Clos le fichier
*/
void fileClose();

/**
* Détermine la taille du fichier en plaçant la tête de lecture à la fin et en retournant le nombre d'octects parcourue par celle-ci
*/
int getFileSize();

/**
* Retourne le nom du fichier
**/
char * getFileName();


/**
* Sauvegarde le bloc dans le fichier
*/

void modifyBloc(int n_bloc, char *s);

/**
* "Supprime" l'octet n du bloc n_bloc de taille bloc_size
*/
void delOctet(int n_bloc, int n);
