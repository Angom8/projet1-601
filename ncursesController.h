#include "ncurses.h"
#include "string.h"
#include <ncurses.h>   /* Pour toutes les fonctions/constantes ncurses */
#include <stdlib.h>    /* Pour exit, EXIT_FAILURE */


#define LARGEUR 60/*Largeur de la fenêtre la plus grande*/
#define HAUTEUR 30/*Hauteur de la fenêtre*/
#define POSX    1 /* Position horizontale de la fenêtre */
#define POSY    1/*Position verticale de la fenêtre*/

#define NB_L 16/*Nombre de lignes à afficher pour F2 et F3*/
#define NB_L_F1 5 /*Nombre de lignes à afficher pour F1*/

#define F1_W LARGEUR/*Largeur de la fenêtre 1*/
#define F1_H 7/*Hauteur de la fenêtre 1*/

#define F2_W 35/*Largeur de la fenêtre 2*/
#define F2_H 18/*Hauteur de la fenêtre 2*/

#define F3_W 10/*Largeur de la fenêtre 3*/
#define F3_H 18/*Hauteur de la fenêtre 3*/

#define NB_OCTET 8 /*Nombre d'octets à afficher par ligne */
#define F2F3_PADDING 2
#define BLOC_SIZE 128
#define OCTET_FORMAT 3

/**
 * Initialisation de ncurses.
 */
void ncurses_initialiser();
/**
 * Fin de ncurses.
 */
void ncurses_stopper();

/**
 * Initialisation des couleurs.
 */
void ncurses_couleurs();

/**
 * Initialisation des palettes de couleur.
 */
void ncurses_palette();

/**
 * Vérificaition du terminal
 */
void checkOutput();

/**
 * Initialisation de la souris.
 */
void ncurses_souris();


/**
 * Recupere la position x et y de la souris.
 * @param[out] x la position en x
 * @param[out] y la position en y
 * @param[out] bouton l'évenement associé au clic (ou NULL)
 * @return OK si reussite
 */
int souris_getpos(int *x, int *y, int *bouton);


