#include "DataManager.h"
#include <string.h>

/* Variables pseudo statiques du gestionnaire de fichiers */
int fd;
char * filename;

/**
* Initialise la lecture du fichier
*/

void initFileRead(char * s, int d){

	filename = malloc((strlen(s) + 1) * sizeof(char));
	filename = s;
	fd = d;
}

/**
* Vérifie si le fichier est ok
*/

int is_opened(){

	int r = 0;
	if(fd != -1){
		r=1;
	}
	return r;
	
}



/**
* Détermine l'existence d'un fichier à partir d'une chaine de caractères passée en paramètre
*/

int file_exists(char * f){

	int response = 1;
	
	if((response = open(f, O_RDWR)) == -1){
		response = 0;
	}
	else{
		close(response);
	}
	
	return response;
}

/**
* Lit le bloc n d'un fichier
*/
char * readBloc(int n){

	int t = 0;
	char * buffer = malloc(sizeof(char) * (BLOC_SIZE+1));
	
	lseek(fd, n * BLOC_SIZE, SEEK_SET);
	
	t = read(fd, buffer,BLOC_SIZE);
	if(t < BLOC_SIZE){
		buffer[t] = -1;
	}
	return buffer;
}

/**
* Clos le fichier
*/
void fileClose(){
	close(fd);
}


/**
* Retourne la taille du fichier
**/
int getFileSize(){
	lseek(fd, 0, SEEK_SET);
	return lseek(fd, 0, SEEK_END);

}

/**
* Retourne le nom du fichier
**/
char * getFileName(){
	return filename;
}

/**
* Sauvegarde le bloc dans le fichier
*/

void modifyBloc(int n_bloc, char *s){
	int t = 0;
	
	lseek(fd, n_bloc * BLOC_SIZE, SEEK_SET);
	
	t = write(fd, s, BLOC_SIZE);
	
	t =1;t++;  /*sinon warning car d non utilisé*/
}

/**
* Modifie l'octet n du bloc n_bloc de taille bloc_size avec la valeur value
*/

void modifyOctet(int n_bloc, int n, int value){
	int t = 0;
	int pos =  n_bloc * BLOC_SIZE;

	char * buffer = malloc(sizeof(char) * BLOC_SIZE);
	
	lseek(fd, pos, SEEK_SET);
	
	t = read(fd, buffer, BLOC_SIZE);
	buffer[n] = (char) value;
	
	lseek(fd, pos, SEEK_SET);
	
	t = write(fd, buffer, BLOC_SIZE);
	
	t =1;t++;  /*sinon warning car d non utilisé*/
	
	free(buffer);
}

/**
* "Supprime" l'octet n du bloc n_bloc de taille bloc_size
*/
void delOctet(int n_bloc, int n){
	int pos =  n_bloc * BLOC_SIZE;
	int t = 0;
	char * buffer = malloc(sizeof(char) * BLOC_SIZE);

	lseek(fd, pos, SEEK_SET);
	
	t = read(fd, buffer,BLOC_SIZE);
	buffer[n] = '.';
	
	lseek(fd, pos, SEEK_SET);
	
	t = write(fd, buffer, BLOC_SIZE);
	t =1;t++;  /*sinon warning car d non utilisé*/
		
	free(buffer);

}

/**
* "Supprime" l'octet n du bloc n_bloc de taille bloc_size
*/
/*
void delOctetv2(int n_bloc, int n){
	int pos =  n_bloc * BLOC_SIZE;
	int t = 0;
	int fd2 = 0;
	int z;
	int i = 0, j = 0;
	int ec = 0;
	char * buffer = malloc(sizeof(char) * BLOC_SIZE);

	lseek(fd, pos, SEEK_SET);
	
	t = read(fd, buffer,BLOC_SIZE);
	
	Création d'un deuxième fichier pour stocker le cache 
	if(file_exists("cache.bin") != 1){
		fd2 = open("cache.bin", O_CREAT);
		lseek(fd2, 0, SEEK_SET);
		
		Stockage de buffer n à buffer n+1
		i = n+1;
		while(i < BLOC_SIZE){
			z = write(fd2, buffer[i], 1);
			i++;
			ec ++;
		}
		
		 Stockage des buffers ultérieurs 
		
		j = n_bloc + 1;
		while(j*BLOC_SIZE <= getFileSize()){
			t = read(fd, buffer,BLOC_SIZE);
			z = write(fd2, buffer, t);
			ec += t;
		}
	
		Troncage fichier 1
		
		ftruncate(fd, ec);
		
		 Insertion données fichier 2
		
		lseek(fd, pos, SEEK_SET);
		lseek(fd2, 0, SEEK_SET);
		
		j = 0;
		while(j*BLOC_SIZE <= ec/BLOC_SIZE){
			t = read(fd2, buffer,BLOC_SIZE);
			z = write(fd, buffer, t);
		}
	}
	z ++;
	close(fd2);
	free(buffer);

}
*/
