#include "windowActions.h"

/* Variables du gestionnaire d'action*/
/* Solution de facilité, mais évite de les ballader partout*/

WINDOW* fenetre1, *fenetre2, *fenetre3;		/* Fenetres ncurses*/
char * current_bloc = NULL;				/* Tableau de données du bloc */
int glob_writing_y = 0;				/* Pour la fenetre 1 (en absence de scrolling) */
/*The chosen one*/
int chosen_octet_x = -1;				/* Position x dans le tableau de données de l'octet sélectionné par l'UI */ 
int chosen_octet_y = -1;				/* Position y dans le tableau de données de l'octet sélectionné par l'UI */
int bloc;						/* Nème bloc*/
int size_current_bloc;					/* Si on est en fin de fichier !*/

/**
* Première création des fenetres
*/
void firstInit(){

	/* Creation de la fenêtre 1 */
	fenetre1 = newwin(F1_H, F1_W, POSX, POSY);
	wbkgd(fenetre1, COLOR_PAIR(1));
	box(fenetre1, 0, 0);
	mvwaddstr(fenetre1, 0, 0, "Saisie :");
	
	
	/* Creation de la fenêtre 2 */
	fenetre2 = newwin(F2_H , F2_W, POSX + F1_H , POSY);
	wbkgd(fenetre2, COLOR_PAIR(2));
	box(fenetre2, 0, 0);
	mvwaddstr(fenetre2, 0, 0, "Hexa :");
	
	
	/* Creation de la fenêtre 3 */
	fenetre3 = newwin(F3_H, F3_W, POSX + F1_H, POSY + F2_W + F2F3_PADDING);
	wbkgd(fenetre3, COLOR_PAIR(3));
	box(fenetre3, 0, 0);
	mvwaddstr(fenetre3, 0, 0, "Char :");
	
	scrollok(fenetre1, TRUE);/*Marche une fois sur 5. Je n'ai visiblement pas été le seul à avoir des pb avec ?*/
  
	/* Création d'un cadre */
	wrefresh(fenetre1);
	wrefresh(fenetre2);
	wrefresh(fenetre3);
}

/**
*Supprime les différentes fenetres
*/
void stopFenetres(){
  	delwin(fenetre1);
  	delwin(fenetre2);
  	delwin(fenetre3);
  	
 }

/**
* Libère le bloc en mémoire
*/
void emptyBuffer(){
	free(current_bloc);
}


/**
* Reset la fenetre 1
*/

void resetFenetre1(){
	werase(fenetre1);
	wbkgd(fenetre1, COLOR_PAIR(1));
	box(fenetre1, 0, 0);
	mvwaddstr(fenetre1, 0, 0, "Saisie :");
}


/**
* Reset la fenetre 2
*/

void resetFenetre2(){
	werase(fenetre2);
	wbkgd(fenetre2, COLOR_PAIR(2));
	box(fenetre2, 0, 0);
	mvwaddstr(fenetre2, 0, 0, "Hexa :");
}

/**
* Reset la fenetre 3
*/

void resetFenetre3(){
	werase(fenetre3);
	wbkgd(fenetre3, COLOR_PAIR(3));
	box(fenetre3, 0, 0);
	mvwaddstr(fenetre3, 0, 0, "Char :");
}


/**
* Génère les fenetre 2 et 3 à partir d'un fichier à son x ème bloc
*/
void genererFenetresFichier(int b, int n_bloc){

	/* Variables */
	int i = 0;			/* Pour le parcours de haut en bas des fenetres */
	int j = 0;			/* Pour le parcours de gauche à droite des fenetres */
	int k = 0;			/* Pour parcourir le tableau de données. Une conversion pourrait être aussi faite à partir de i, j comme dans d'autres fonctions */
	int z = 0;			/* Pour parcourir le tableau de données. Une conversion pourrait être aussi faite à partir de i, j comme dans d'autres fonctions */
	int size_tmp;			/* Permet l'affichage "avec pleins de 0" de la position dans le fichier à gauche de la fenetre 2 */

	int loc;
	
	/*On vérifie si le fichier existe toujours. Sinon => STOP */
	if(is_opened() == 1){

		/* On récupère le bloc à lire */
		if(current_bloc != NULL) free(current_bloc);		
		current_bloc = readBloc(n_bloc);
		bloc = n_bloc;
		size_current_bloc = 0;
		while(current_bloc[size_current_bloc] != -1 && size_current_bloc < BLOC_SIZE){
			size_current_bloc++;
		}

		/*TODO VERIF FIN FICHIER*/ /* Relique de l'organisation du développement que je laisse ici par beauté du geste */
		
		/* (Re) Génération de la fenetre 2 sous le format "00000TAILLE - HEX HEX HEX HEX HEX HEX HEX HEX"*/
		resetFenetre2();
		for(i = 1;i<=NB_L;i++){
		
			/* Traitement de la taille (il y, très probablement, plus simple) */
			size_tmp = (n_bloc * BLOC_SIZE + (i-1)*8);
			loc = 1;
			for(j = 1;j<NB_OCTET;j++){
				loc *= 10;
			}
			
			for(j = 0; j< NB_OCTET;j++){
				mvwprintw(fenetre2, i, j+1, "%c", size_tmp/loc + '0');
				size_tmp %=loc; /*On doit l'utiliser une fois tous les centenaires celui-là ...*/
				loc /= 10;
			}
			k=0;
			
			/* On imprime octet par octet avec des espaces tous les 3 (aka OCTET_FORMAT) caractères écrits */
			while(k < b){

				if(k % OCTET_FORMAT == 0){
					mvwaddch(fenetre2, i, NB_OCTET+k+1, ' ');
					
				}
				else{
					if(z<size_current_bloc){
						printOctet(current_bloc[z], i, NB_OCTET+k+1);
					}
					else{
						printOctet('\0', i, NB_OCTET+k+1);
					}
					z++;
					k++;
				}
				k++;
			}
			
			
		}
		
		/* (Re) Génération de la fenetre 2 sous le format "CCCCCCCC"*/
		resetFenetre3();
		k = 0;
		for(i = 0;i< NB_L ;i++){
			for(j = 0;j< NB_OCTET ;j++){
				if(k<size_current_bloc){
					printChar(current_bloc[k], i+1, j+1);
					k++;
				}
				else{
					printChar(' ', i+1, j+1);
				}
			}
		}
		
		wrefresh(fenetre2);
		wrefresh(fenetre3);
	
	}
	
	else{
		ncurses_stopper();
	 	fprintf(stderr, "Erreur lors de l'accès au fichier.\n");
		exit(EXIT_FAILURE);
	}
	

}

/**
* Permet de saisir un caractère à afficher dans la fenetre 1
*/
void directWriteFenetre1(){
	char str[LARGEUR-3];
	printFenetre1("Veuillez saisir un caractère...");
	getnstr(str, LARGEUR-4);
	glob_writing_y++;
	
 	if(glob_writing_y > NB_L_F1){
 		resetFenetre1();
 	        glob_writing_y = 1;
 	        mvwaddstr(fenetre1,glob_writing_y,1, "");
 	        
 	}
 	
	mvwaddstr(fenetre1,glob_writing_y,1, "");
	mvwaddstr(fenetre1, glob_writing_y, 1, str);

	wrefresh(fenetre1);
}

/**
* Permet d'afficher le string s dans la fenetre 1
*/
void printFenetre1(char *s){
	glob_writing_y++;
	
 	if(glob_writing_y > NB_L_F1){
		resetFenetre1();
 	        glob_writing_y = 1;
 	        mvwaddstr(fenetre1,glob_writing_y,1, "");
 	        
 	}
 	
	mvwaddstr(fenetre1,glob_writing_y,1, "");
	mvwaddstr(fenetre1, glob_writing_y, 1, s);

	wrefresh(fenetre1);
}

/**
* Permet d'afficher la taille du fichier et le nb de blocs lord de la première execution
*/
void firstPrint(int filesize, int max_bloc){
	glob_writing_y++;
	
 	if(glob_writing_y > NB_L_F1){
		resetFenetre1();
 	        glob_writing_y = 1;
 	        mvwaddstr(fenetre1,glob_writing_y,1, "");
 	        
 	}
 	
	mvwaddstr(fenetre1,glob_writing_y,1, "");
	mvwprintw(fenetre1, glob_writing_y,1, "Taille du fichier : %d, nombre de blocs : %d", filesize, max_bloc);

	wrefresh(fenetre1);
}

/**
* Permet d'afficher la position du clic dans la fenetre1
* @param isInWindow donne la fenetre de référence dans laquelle le main a détecté un clic
*/
void writePosFenetre1(int x, int y, int isInWindow){

        int truex, truey;
        glob_writing_y++;

   
 	if(glob_writing_y > NB_L_F1){
		resetFenetre1();
 	        glob_writing_y = 1;
 	        mvwaddstr(fenetre1,glob_writing_y,1, "");
 	        
 	}
 	
 	mvwaddstr(fenetre1,glob_writing_y,1, "");
 	
 	/* Selon la fenêtre dans laquelle se trouve le clic, on agit différemment*/
	switch(isInWindow){
		/*Fenetre 3*/
		case 3:
			/* truex et truey représente l'octet dans le bloc. Le premier octet d'un bloc est truex=1, truey=1.
				On réduit de 1 pour chercher dans le bloc de données
				truex et truy se calculent à partir de la position absolue fournie en paramètre (x,y), en retirant ensuite les écarts de chaque fenetre
			*/
			truex = x-POSX-F2_W-F2F3_PADDING;
			truey = y-POSY-F1_H;
				
			wprintw(fenetre1, "Position écran - x:%d y:%d | Char - x:%d y:%d", x, y, truex, truey);
			
			/* On a reselectionné le chosen one, on peut donc modifier sa valeur ! */
			if(chosen_octet_x == truex-1 && chosen_octet_y == truey-1){
				saisieOctet(chosen_octet_x, chosen_octet_y);
			}
			else{
				/* A-t-on déjà sélectionné un octet ? ! */
				if(chosen_octet_x != -1 || chosen_octet_y != -1){
					colorOctet(chosen_octet_x+1, chosen_octet_y+1, 0);
					colorChar(chosen_octet_x+1, chosen_octet_y+1, 0);
				}
					
				chosen_octet_x = truex-1;
				chosen_octet_y = truey-1;
				colorOctet(truex, truey, 1);
				colorChar(truex, truey, 1);
					
			}
			
			
			colorChar(truex, truey, 1);
			break;
		case 2:
			/* truex et truey représente l'octet dans le bloc. Le premier octet d'un bloc est truex=1, truey=1.
				On réduit de 1 pour chercher dans le bloc de données
				truex et truy se calculent à partir de la position absolue fournie en paramètre (x,y), en retirant ensuite les écarts de chaque fenetre
			*/		
			truex = x-POSX;
			truey = y-POSY-F1_H;
				
			/*  A-t-on sélectionné la taille ou un espace ? */
			if(truex > NB_OCTET && truex%OCTET_FORMAT != 0 ){
			
				/* Si on a sélectionné le deuxième caractère de l'écriture hexa, on réécrit le truex */
				if((truex+1)%OCTET_FORMAT == 0) truex--;
	
				/* On retire l'écart de la taille (par rapport au bord gauche), avant de définir quel octet est sélectionné par rapport à sa position*/
				truex = (truex-NB_OCTET)/OCTET_FORMAT+1;
			
				wprintw(fenetre1, "Position écran - x:%d y:%d | Octet - x:%d y:%d", x, y, truex , truey);
				
				/* On a reselectionné le chosen one, on peut donc modifier sa valeur ! */
				if(chosen_octet_x == truex-1 && chosen_octet_y == truey-1){
					saisieOctet(chosen_octet_x, chosen_octet_y);
					/*ecriture*/
				
				}
				else{
					
					/* A-t-on déjà sélectionné un octet ? ! */
					if(chosen_octet_x != -1 || chosen_octet_y != -1){
						colorOctet(chosen_octet_x+1, chosen_octet_y+1, 0);
						colorChar(chosen_octet_x+1, chosen_octet_y+1, 0);
					}
					
					chosen_octet_x = truex-1;
					chosen_octet_y = truey-1;
					colorOctet(truex, truey, 1);
					colorChar(truex, truey, 1);
					
				}
				
				
			}
			else
				wprintw(fenetre1, "Position écran - x:%d y:%d", x, y);
			break;
	
		default:

			wprintw(fenetre1, "Position écran - x:%d y:%d", x, y);
			/* A-t-on déjà sélectionné un octet ? ! */
			if(chosen_octet_x != -1 || chosen_octet_y != -1){
					colorOctet(chosen_octet_x+1, chosen_octet_y+1, 0);
					colorChar(chosen_octet_x+1, chosen_octet_y+1, 0);
			}
			chosen_octet_x = -1;
			chosen_octet_y = -1;
			break;
	}
	
	
	
	wrefresh(fenetre1);

}



/**
* Selectionne un octet sur la fenetre, ou le décolorie.
*/
void colorOctet(int truex, int truey, int col){

	/* Si la col est à 1, on veut colorier */
	if(col == 1){
		wattron(fenetre2, COLOR_PAIR(4));
		printOctet(current_bloc[(truey-1)*NB_OCTET +  truex-1], truey, NB_OCTET+((truex)*OCTET_FORMAT)-1);
		wattroff(fenetre2, COLOR_PAIR(4));
	}
	else{
		wattron(fenetre2, COLOR_PAIR(2));
		printOctet(current_bloc[(truey-1)*NB_OCTET +  truex-1], truey, NB_OCTET+((truex)*OCTET_FORMAT)-1);
		wattroff(fenetre2, COLOR_PAIR(2));
	}
	wrefresh(fenetre2);

}

/**
* Selectionne un char sur la fenetre, ou le décolorie en ayant sélectionné un octet.
*/
void colorChar(int truex, int truey, int col){

	/* Si la col est à 1, on veut colorier */
	if(col == 1){
		wattron(fenetre3, COLOR_PAIR(4));
		printChar(current_bloc[(truey-1)*NB_OCTET + truex-1], truey, truex);
		wattroff(fenetre3, COLOR_PAIR(4));
	}
	else{
		wattron(fenetre3, COLOR_PAIR(3));
		printChar(current_bloc[(truey-1)*NB_OCTET + truex-1], truey, truex);
		wattroff(fenetre3, COLOR_PAIR(3));
	}
	wrefresh(fenetre3);

}

/**
* On rentre une nouvelle valeur pour l'octet choisi, puis on sauvegarde
*/
void saisieOctet(int chosen_octet_x, int chosen_octet_y){

        char str[2];
        char car;
        printFenetre1("Veuillez saisir un caractère...");
        getnstr(str, 1);
        car = str[0];
        
	if (car <= 32 || car >= 127 ){
		car = '.';
	}
	
	printFenetre1(str);
        
        current_bloc[(chosen_octet_y)*NB_OCTET + chosen_octet_x] = car;
	colorOctet(chosen_octet_x+1, chosen_octet_y+1, 0);
	colorChar(chosen_octet_x+1, chosen_octet_y+1, 0);
	
	modifyBloc(bloc, current_bloc);
	genererFenetresFichier(NB_OCTET * OCTET_FORMAT, bloc);

}

/**
* On réaffiche l'octet à sa position x et y
*/
void printOctet(char octet, int x, int y){
	mvwprintw(fenetre2, x, y, "%02X", octet);

}

/**
* On réaffiche le car à sa position x et y (avec traitement pour éviter débordement)
*/
void printChar(char car, int x, int y){


	if (car > 32 && car < 127 ){
		mvwprintw(fenetre3, x, y, "%c", car);
	}
	else{
		mvwprintw(fenetre3,x, y, "%c",  '.');
	}

	
}

/**
* On "supprime" l'octet choisi, puis on sauvegarde
*/
void delSelectedChar(){
	if(chosen_octet_x != -1 || chosen_octet_y != -1){
		printFenetre1("Suppression d'un octet...");
      	 	current_bloc[(chosen_octet_y)*NB_OCTET + chosen_octet_x] = '.';
		colorOctet(chosen_octet_x+1, chosen_octet_y+1, 0);
		colorChar(chosen_octet_x+1, chosen_octet_y+1, 0);
	}
	
	modifyBloc(bloc, current_bloc);
	genererFenetresFichier(NB_OCTET * OCTET_FORMAT, bloc);

}

/**
* Génère les fenetre 2 et 3 à partir d'un fichier à son x ème bloc
* Différence : On ne refresh pas le bloc de données (ce qui a son avantage dans certains cas).
* Version condensée, CF CODE PLUS HAUT POUR LES COMMENTAIRES
*/
void regenFenetres(int b){

	
	int i = 0;
	int j = 0;
	int k = 0;
	int z = 0;
	int size_tmp;

	int loc;
	if(is_opened() == 1){

		/*TODO VERIF FIN FICHIER*/
	
		resetFenetre2();
		for(i = 1;i<=NB_L;i++){
			size_tmp = (bloc * BLOC_SIZE + (i-1)*8);
			loc = 1;
			for(j = 1;j<NB_OCTET;j++){
				loc *= 10;
			}
			for(j = 0; j< NB_OCTET;j++){
				mvwprintw(fenetre2, i, j+1, "%c", size_tmp/loc + '0');
				size_tmp %=loc;
				loc /= 10;
			}
			k=0;
			while(k < b){
				if(k % OCTET_FORMAT == 0){
					mvwaddch(fenetre2, i, NB_OCTET+k+1, ' ');
				}
				else{
					printOctet(current_bloc[z], i, NB_OCTET+k+1);
					z++;
					k++;
				}
				k++;
			}
		}
		resetFenetre3();
		k = 0;
		for(i = 0;i< NB_L ;i++){
			for(j = 0;j< NB_OCTET ;j++){
				printChar(current_bloc[k], i+1, j+1);
				k++;
			}
		}
		wrefresh(fenetre2);
		wrefresh(fenetre3);
	}
	else{
		ncurses_stopper();
	 	fprintf(stderr, "Erreur lors de l'accès au fichier.\n");
		exit(EXIT_FAILURE);
	}

}
