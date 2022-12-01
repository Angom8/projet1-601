# projet1-601
Petit projet (qui bug un peu) et pouvant facilement être optimisé avec plus d'inspection

== PROJET INFO0601 - Editeur hexadécimal primitif ==

-- Utilisation :
	* Projet avec un makefile (donc "make" pour executer, "make clean" pour nettoyer)
	* Plusieurs fichiers tests fournis (2 binaires directement issus d'un jeu, 1 créé pour l'occasion, en excluant le LisezMoi ;) )
	* Pour executer une fois compilé : "./main nomdufichier" (exemple : "./main Items.ma3)
	* Les interactions utilisateurs correspondent au cahier de projet

-- Fonctionnalités intégrées :

	==== UI ====
	* Déroulage de la fenetre 1 : Impossible de faire fonctionner le scroll via ncurses. La fenetre se vide donc au bout de 5 messages
	* Format de la fenetre 2 et de la fenetre 2 : OK
	* Afficher un bloc sous format hexadécimal : Bug avec les accents, OK sinon
	* Afficher un bloc sous format ASCII : Critère ultra sélectif pour l'affichage, OK sinon
	* Traitement cas dernier bloc : OK
	
	==== Interactions ====
	* Coloration lors du choix d'un octet (et du char) : OK
	* UP/DOWN pour changer de bloc : OK
	* F2 pour quitter : OK
	* DEL pour supprimer : OK
	* Ecrire dans la fenetre 1 : OK
	* (?) Ecrire directement (saisie clavier) dans la fenetre 1 : OK
	* Affichage de la position : OK
	* Affichage de l'octet/char sélectionné : OK
	* Traitement cas dernier bloc : OK

	==== Fichiers ====
	* Lire le nième bloc de X octets d'un fichier : OK
	* Modifier un octet dans le fichier : OK
	* Suppression d'un octet : Remplacé par un point, j'ai tenté le décalage, mais même avec adaptation des macros, changement de version de c, test sur une VM (pas celle de la fac, cf difficultés rencontrées), impossible de faire fonctionner la fonction.
	

-- Problèmes connus :
	* L'affichage des caractères accentués ou avec une valeur sur 2 octets dérange l'affichage. Pas de problème en terme de technique (il est possible de les éditer, les supprimer, etc).
	* La fenetre 1 est un faux-défilement
	* La position est parfois incohérente par rapport à la position réelle de la souris (pas de problème technique en dehors de l'affichage)
	* Des caractères se coincent lors du werase


-- Organisation du code (il y en a une oui...) :
	* ncursesController : Gestion et Initialisation globale de ncurses (codes fournis avec le sujet)
	* main : Boucle principale et initialisation
	* dataManager : Lecture et ecriture fichier
	* windowActions : Interactions avec la fenetre et entre-deux boucleprincipale-fichiers. (pourrait être simplifié)
	* Chaque fichier possède un set de variables globales afin d'éviter d'avoir à les réinserer à chaque appel de fonction => pourrait être optimisé.


-- Difficultés rencontrées / Commentaires :
	* Gestion fichier : open et read ne voulaient pas fonctionner correctement sur mon installation linux et mon réseau semble incompatible pour la VM de la fac (4G free avec ip instable ?)
	* Temps : Je travaille désormais à côté de la fac et c'est le premier projet que je fais en étant vraiment 50/50 avec.
	* Paramètres du makefile : Un mal pour un bien. Par exemple, impossible de déclarer une variable en milieu de code. Résultat (normalement) : Aucune erreur et code légérement plus propre (mais pas trop non plus)
	* Temps2 : Même si j'ai bossé dessus pendant les vacances, j'ai pas mal procrastiné et mis le projet "en deuxième plan" par rapport à d'autres (TP de 603, 604). 
	* C'était très satisfaisant de faire fonctionner l'interface
	* 9 cafés ont suffis
	* Pourcentage de complétion estimé : 91% (tout est fait, il est encore possible d'améliorer)
