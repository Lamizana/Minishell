# Minishell
Creer un  shell similaire à bash
-------------------------------------------------------------------------------
- REGLES:
-------------------------------------------------------------------------------
- Compilation:
	 - valgrind --leak-check=full --show-leak-kinds=all --suppressions=vsupp ./minishell
	 - readline genere 215 block non free.

-------------------------------------------------------------------------------
- RESSOURCES:
-------------------------------------------------------------------------------
	- SCL 	--> Shell Command Language.
	- Blog 	--> Pays du 42.
	- 42sh 	--> architecture d un shell.
  
-------------------------------------------------------------------------------
- FONCTIONS AUTORISEES:
-------------------------------------------------------------------------------
	- readline 	--> obtient une ligne d un utilisateur.
	- add_history --> enregistre la commande transmise.
	- acces		--> verifie les permissions utilisateur a un fichier.
	- execve	--> execute un programme.
	- fork		--> cree un processus fil.
	- getenv	--> recupere le contenue d une variable d environnement.
	- readddir 	--> consulte un repertoire.
	- open		-->
	- read		-->
	- close		-->
	- wait		-->
	- waitpid	-->
	- wait3		-->
	- wait4		-->

- Entree standard -> STDIN_FILENO == 0.
Associer au clavier, lit ce que jecris dessus.

- Sortie standard -> STDOUT_FILENO == 1.
Affiche le contenu de notre programme (genre putstr) sur la sortie standard.

- Sortie erreur -> STDERR_FILENO == 2.
Affiche sur la sortie d erreur.

-------------------------------------------------------------------------------
- REALISER UN SHELL QUI FONCTIONNE AVEC LES COMMANDES DE BASES.
-------------------------------------------------------------------------------
	(1) - PROMPT:
		Afficher 1 prompt qui lit des commandes et qui ne fait rien, puis se raffiche.

	(2) - LANCER UN PROGRAMME -> RECUPERER LE PATH:

	(3) - LANCER UN PROGRAMME -> FORKER:
		apres avoir lancer execve le programme  sarette.
		fork() permet de dupliquer le programme pour eviter l arret du minishell.

	(4) - LANCER UN PROGRAMME -> EXECVE:

-------------------------------------------------------------------------------
- DESCRIPTIF DES FONCTIONS	
-------------------------------------------------------------------------------
--> _execve_:
#include <unistd.h>
- int execve(const char *file, char *const argv[], char *const envp[]);
		
--> _fork_:
- pid_t fork(void);

--> _getenv_:
#include <stdlib.h>
- char *getenv(const char *varName);

	- recupere le contenue d une variable d environnement.
	- varName: definit le nom de la variable. EX: PATH, USER, ...
	- valeur de retour: renvoie NULL si varName n existe pas.

--> _readline_:
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
- char *readline(const char *prompt);

	- Lit une ligne du terminal.
	- Valeur de retour: .renvoie le texte.
						.une ligne vide si la chaine est vide,
						.si EOF est rencontrer -> NULL

--> _acces_:
#include <unisd.h>
- int acces(const char *pathname, int mode);

	- access verifie si le processus appelent peut acceder au fichier pathname.
	- mode indique les verifications d accesssibilite a effectuer.
	- valeur de retour: .renvoie 0 si il reussie.
						.-1 si il echoue.
--> _readdir_:
#include <dirent.h>
  - int readdir(DIR *dir, struct dirent *entry, struct dient **result);

--> _kill_:
#include <sys/types.h>
#include <signal.h>
- int kill(pid_t pid, int sig);

	- Appel systeme: est utiliser pour envoyer n importe quel signal
	  a n importe quel processus.
	- pid est positif -> sig est envoye au processus dont 
	  l id est indiquer par pid.
	- pid vaut 0 -> sig est envoyer a tous les processus appartenant 
	  au meme groupe que le groupe appelant.
	- pid vaut -1 -> sig est envoyer a tous les processus,
	  sauf celui du PID.
	- sig vaut 0 -> aucun signal n est envoyer mais les conditions 
	  d erreur sont verifiees.
	- Valeur retour: En cas de reussite -> 0, en cas d echec -> -1.

--> _getpid_:
#include <sys/types.h>
#include <unistd.h>
- pid_t getpid(void);

	- Renvoie l identifiant du processeur appelant.
	- Pas de cas d erreur.

--> _pause_:
#include <unistd.h>
- int pause(void);

	- Force le processus appelant a s endormir jusqu a ce qu un signal soit recu,
	  qu il le termine ou lui fasse invoquer une fonction de gestionnaire de signal.
	- Valeur renvoye: -1  et errno si le signal a ete interceptee et que le 
	  gestionnaire c est termine.

--> _sleep_:
#include <unistd.h>
- unsigned int sleep(unsigned int nb_sec);

	- Endort le processus jusqu a ce que nb_sec soit ecoulee,
	  ou jusqu a ce que le signal soit interompue.
	- Valeur retour: renvoie 0 si le temps prevu c est ecoule,
	  ou le nombre de secondes restantes si l appel a ete interompue.

--> _usleep_:
#include <unistd.h>
- unsigned int sleep(useconds_t usec);

	- Meme chose que sleep.
	- Valeur retour: en cas de succe -> 0, en cas d erreur -> -1.
-------------------------------------------------------------------------------
--> _sygemptyset_:
#include <signal.h>
- int sygemtyset(sigset_t *set);

	- Initialise l ensemble de signaux pointer par set, de sorte que tous les signaux
	  definit dans POSIX.1-2008 sint exclus.
	- Valeur de retour: renvoie 0 en cas de reussite et -1 en cas d erreur
	  et defini errno pour indiquer l erreur.

--> _sigaddset_: 
- int sigaddset(sigset_t, int signum);

	- Ajoute le signal signum de set.
	- Valeur de retour: 0 en cas de succes et -1 en cas d erreur.

--> _sygaction_:
- int sigaction(int signum, const struc sigaction *act, struct sigaction *oldact);

  struct sigaction{
	void		(*sa_handler) (int);
	void		(*sa_sigaction) (int, siginfo_t *, void *);
	sigset_t	sa_mask;
	int			sa_flags;
	void		(*sa_restorer) (void);
}

	- ATTENTION: initialiser -> struct sigaction sa = {0}
	- Appel systeme, sert a modifier l action effectuee par un processus 
	  a la reception d un signal specifique.
	- signum indique le signal concerner.
	- Si act est non nul, la nouvelle action est definit par act.
	- Si oldact est non nul, l ancienne version est sauvegarder dans oldact.
	- sa_handler indique l action affecte au signal signum. Il recoit le numero
	  de signal comme seul argument.
	- sa_flags: specifie un ensemble d attributs qui modifie le comportement
	  du signal.
	- Valeur de retour: 0 si il reussi et -1 si il echoue.
-------------------------------------------------------------------------------


-------------------------------------------------------------------------------
- MAKEFILE.
-------------------------------------------------------------------------------
