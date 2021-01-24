#include "windowActions.h"
	
/**
* Fonction principale
*/
int main(int argc, char * argv[]){

	/*
	
	TODO :
		del fichier avec décalage
	*/
	
	/* Initialisation des variables */
	int i; 					/* Pour le GETCH */
	int sourisX, sourisY, button, resultat;	/* Souris */
	int selected_bloc = 0;				/* Bloc en cours */
	int file_size = 0;				/* Taille du fichier */
	int max_bloc = 0;				/* Nombre maximal de blocs */
	int fd;					/* Descripteur de fichier */
		
		
	if(argc <= 1){
		fprintf(stderr, "Veuillez fournir un chemin relatif vers le fichier à décoder\n");
		return EXIT_FAILURE;
	}
	else if(file_exists(argv[1]) == 0){
		fprintf(stderr, "Erreur de l'ouverture du fichier. Rappel : L'extension doit être précisée.\nFichier saisi : %s\n", argv[1]);
		return EXIT_FAILURE;
	}
		
	/* Initialisation de ncurses */
	ncurses_initialiser();
	ncurses_couleurs();
	ncurses_palette();
	ncurses_souris();
	scrollok(stdscr, TRUE);
	
	/*verification de la taille du terminal*/
	checkOutput();
	
        /* Initialisation du fond */
  	clear();
 	refresh();
 	
 	/* Initialisation des fenetres et de la lecture fichier*/
 	firstInit();
 	fd = open(argv[1], O_RDWR);
 	initFileRead(argv[1], fd);
 	
 	
 	/*Variables fichier-dépendantes*/
	file_size = getFileSize();
	max_bloc = file_size/BLOC_SIZE ;
	
	
 	/* Attente d'un clic dans la fenêtre ou de F2 */
	printw("Cliquez dans la fenetre ; pressez F2 pour quitter...");  
	
	firstPrint(file_size, max_bloc);
	printFenetre1(getFileName());
	printFenetre1("Fichier ouvert");
	refresh();
	

 	genererFenetresFichier(NB_OCTET * OCTET_FORMAT, selected_bloc);
 	/* Boucle principale. F2 pour quitter*/
	while((i = getch()) != KEY_F(2)) {
	
		resultat = souris_getpos(&sourisX, &sourisY, &button);
		/*Si clic dans la fenetre 1 => L'utilisateur peut écrire dans le cadre*/
		/*Souris est dans le cadre de la fenetre 1)*/
		if(resultat == OK && (sourisX > POSX) && (sourisX < POSX + F1_W- 1) && (sourisY > POSY) && (sourisY < POSY + F1_H - 1) && (button & BUTTON1_CLICKED)) {    
				 directWriteFenetre1();
		}
		
		/*Passer au bloc précédent / Suivant */
		if(i == KEY_UP){
			if(selected_bloc > 0){
				selected_bloc--;
				genererFenetresFichier(NB_OCTET * OCTET_FORMAT, selected_bloc);
			}
			else{
				printFenetre1("Erreur : Vous êtes sur le premier bloc !");
			}
		}
		else if (i == KEY_DOWN){
			if(selected_bloc < max_bloc){
				selected_bloc++;
				genererFenetresFichier(NB_OCTET * OCTET_FORMAT, selected_bloc);
			}
			else{
				printFenetre1("Erreur : Vous êtes sur le dernier bloc !");
			}
		}
		/* Pour supprimer un caractère*/
		else if (i == KEY_DC || i == KEY_DL || i == KEY_BACKSPACE ){
			delSelectedChar();
		}

		
		/*Si clic quelque part, affiche la position dans la fenetre 1*/
		/* potentiel : raccourcir en petites fonctions*/
		 if(resultat == OK  && ! ((sourisX > POSX) && (sourisX < POSX + F1_W- 1) && (sourisY > POSY) && (sourisY < POSY + F1_H - 1)) && (button & BUTTON1_CLICKED)) {
		 
		 	/*Si souris dans la fenetre 2 */
			if(((sourisX > POSX) && (sourisX < POSX + F2_W -1)) && (sourisY > POSY + F1_H && (sourisY  < POSY + F1_H + F2_H -1))){
				writePosFenetre1(sourisX, sourisY, 2);
				
			}
			/*Si souris dans la fenetre */
			else if(((sourisX > POSX + F2_W + F2F3_PADDING) && (sourisX < POSX + F2_W + F2F3_PADDING -1 + F3_W)) && (sourisY > POSY + F1_H && (sourisY  < POSY + F1_H + F3_H -1))){
				writePosFenetre1(sourisX, sourisY, 3);
			}
		 	
		 
		 	else{
		 		writePosFenetre1(sourisX, sourisY, 0);
		 	}
		 		
		
		}

	}
	
	
	
 	/*Suppression des fenetres et fin*/
 	stopFenetres();
 	fileClose();
 	emptyBuffer();
	ncurses_stopper();
	
	return EXIT_SUCCESS;	
}


