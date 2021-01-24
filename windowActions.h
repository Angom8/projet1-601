#include "ncursesController.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include "DataManager.h"

/**
* Première création des fenetres
*/
void firstInit();

/**
*Supprime les différentes fenetres
*/
void stopFenetres();

/**
* Libère le bloc en mémoire
*/
void emptyBuffer();

/**
* Reset la fenetre 1
*/
void resetFenetre1();
/**

* Reset la fenetre 2
*/
void resetFenetre2();

/**
* Reset la fenetre 3
*/
void resetFenetre3();

/**
* Génère les fenetre 2 et 3 à partir d'un fichier à son x ème bloc
*/
void genererFenetresFichier(int b, int n_bloc);

/**
* Permet de saisir un caractère à afficher dans la fenetre 1
*/
void directWriteFenetre1();

/**
* Permet d'afficher le string s dans la fenetre 1
*/
void printFenetre1(char *s);

/**
* Permet d'afficher la taille du fichier et le nb de blocs lord de la première execution
*/
void firstPrint(int, int);

/**
* Permet d'afficher la position du clic dans la fenetre1
* @param isInWindow donne la fenetre de référence dans laquelle le main a détecté un clic
*/
void writePosFenetre1(int x, int y, int isInWindow);

/**
* Selectionne un octet sur la fenetre, ou le décolorie.
*/
void colorOctet(int truex, int truey, int col);

/**
* Selectionne un char sur la fenetre, ou le décolorie en ayant sélectionné un octet.
*/
void colorChar(int truex, int truey, int col);

/**
* On rentre une nouvelle valeur pour l'octet choisi, puis on sauvegarde
*/
void saisieOctet(int chosen_octet_x, int chosen_octet_y);

/**
* On réaffiche l'octet à sa position x et y
*/
void printOctet(char octet, int x, int y);

/**
* On réaffiche le car à sa position x et y (avec traitement pour éviter débordement)
*/
void printChar(char car, int x, int y);

/**
* On supprime l'octet choisi, puis on sauvegarde
*/
void delSelectedChar();

/**
* Génère les fenetre 2 et 3 à partir d'un fichier à son x ème bloc
* Différence : On ne refresh pas le bloc de données
* Version condensée, CF CODE PLUS HAUT POUR LES COMMENTAIRES
*/
void regenFenetres(int b);

