# Notes d etude - Minishell

Notes d apprentissage du projet (2023), extraites du README d origine pour
garder un README principal concis et professionnel. Ces notes documentent le
fonctionnement des fonctions autorisees et la reflexion autour de la
realisation du shell.

## Sommaire

- [Ressources](#ressources)
- [Fonctions autorisees](#fonctions-autorisees)
- [Realiser un shell avec les commandes de base](#realiser-un-shell-qui-fonctionne-avec-les-commandes-de-bases)
- [Descriptif des fonctions](#descriptif-des-fonctions)

-------------------------------------------------------------------------------
## RESSOURCES:

	- SCL 	--> Shell Command Language.
	- Blog 	--> Pays du 42.
	- 42sh 	--> architecture d un shell.
-------------------------------------------------------------------------------
## FONCTIONS AUTORISEES:

	- readline 	--> obtient une ligne d un utilisateur.
	- add_history 	--> enregistre la commande transmise.
	- access	--> verifie les permissions utilisateur a un fichier.
	- execve	--> execute un programme.
	- fork		--> cree un processus fils.
	- getenv	--> recupere le contenu d une variable d environnement.
	- readdir 	--> consulte un repertoire.
	- open		--> ouvre un fichier ou un descripteur de fichier.
	- read		--> lit des donnees depuis un descripteur de fichier.
	- close		--> ferme un descripteur de fichier.
	- wait		--> attend la fin d un processus fils.
	- waitpid	--> attend la fin d un processus fils specifique.
	- wait3		--> attend un processus fils et recueille les ressources utilisees.
	- wait4		--> attend un processus fils (version de wait3 avec options).

### Entrees / sorties standard:

- Entree standard -> STDIN_FILENO == 0.
> Associe au clavier, lit ce que j ecris dessus.

- Sortie standard -> STDOUT_FILENO == 1.
> Affiche le contenu de notre programme (genre putstr) sur la sortie standard.

- Sortie erreur -> STDERR_FILENO == 2.
> Affiche sur la sortie d erreur.

-------------------------------------------------------------------------------
## REALISER UN SHELL QUI FONCTIONNE AVEC LES COMMANDES DE BASES.

	(1) - PROMPT:
		Afficher 1 prompt qui lit des commandes et qui ne fait rien, puis se re-affiche.

	(2) - LANCER UN PROGRAMME -> RECUPERER LE PATH:

	(3) - LANCER UN PROGRAMME -> FORKER:
		apres avoir lance execve le programme s arrete.
		fork() permet de dupliquer le programme pour eviter l arret du minishell.

	(4) - LANCER UN PROGRAMME -> EXECVE:
-------------------------------------------------------------------------------
## DESCRIPTIF DES FONCTIONS

#### --> execve: 
> #include <unistd.h>
```C
int execve(const char *file, char *const argv[], char *const envp[]);
```
-------------------------------------------------------------------------------
#### -->  fork:

```C
pid_t fork(void);
```
-------------------------------------------------------------------------------
#### --> getenv:
> #include <stdlib.h>

```C
char *getenv(const char *varName);
```
- recupere le contenu d une variable d environnement.
- **varName**: definit le nom de la variable. EX: PATH, USER, ...
- **valeur de retour**: renvoie NULL si varName n existe pas.
-------------------------------------------------------------------------------
#### --> readline:
> #include <stdio.h>

> #include <readline/readline.h>

> #include <readline/history.h>

```C
char *readline(const char *prompt);
```
- Lit une ligne du terminal.
- Valeur de retour: 
	- renvoie le texte.
	- une ligne vide si la chaine est vide,
	- si EOF est rencontre -> NULL
-------------------------------------------------------------------------------
#### --> access:
> #include <unistd.h>

```C
int access(const char *pathname, int mode);
```
- access verifie si le processus appelant peut acceder au fichier pathname.
- mode indique les verifications d accessibilite a effectuer.
- valeur de retour: 
	- renvoie 0 s il reussit.
	- -1 s il echoue.
-------------------------------------------------------------------------------
#### --> readdir:
> #include <dirent.h>

```C
struct dirent *readdir(DIR *dirp);
```
- Lit l entree suivante d un repertoire.
- Valeur de retour: un pointeur sur struct dirent, ou NULL en fin de parcours.
-------------------------------------------------------------------------------
#### --> open:
> #include <fcntl.h>

```C
int open(const char *pathname, int flags, mode_t mode);
```
- Ouvre (et cree si besoin) un fichier.
- Valeur de retour: un descripteur de fichier, ou -1 en cas d erreur.
-------------------------------------------------------------------------------
#### --> read:
> #include <unistd.h>

```C
ssize_t read(int fd, void *buf, size_t count);
```
- Lit count octets depuis le descripteur fd.
- Valeur de retour: le nombre d octets lus, 0 a la fin du fichier, -1 en cas d erreur.
-------------------------------------------------------------------------------
#### --> close:
> #include <unistd.h>

```C
int close(int fd);
```
- Ferme le descripteur de fichier fd.
- Valeur de retour: 0 en cas de succes, -1 en cas d erreur.
-------------------------------------------------------------------------------
#### --> wait:
> #include <sys/wait.h>

```C
pid_t wait(int *status);
```
- Attend la fin d un processus fils.
- Valeur de retour: le PID du fils termine, ou -1 en cas d erreur (aucun fils).
-------------------------------------------------------------------------------
#### --> waitpid:
> #include <sys/wait.h>

```C
pid_t waitpid(pid_t pid, int *status, int options);
```
- Attend la fin d un processus fils specifique (pid).
- Valeur de retour: le PID du fils termine, ou -1 en cas d erreur.
-------------------------------------------------------------------------------
#### --> wait3:
> #include <sys/wait.h>

> #include <sys/resource.h>

```C
pid_t wait3(int *status, int options, struct rusage *rusage);
```
- Attend un processus fils et recueille les ressources utilisees dans rusage.
-------------------------------------------------------------------------------
#### --> wait4:
> #include <sys/wait.h>

> #include <sys/resource.h>

```C
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```
- Version de wait3 permettant de cibler un processus fils precis (pid).
-------------------------------------------------------------------------------
#### --> _kill_:
> #include <sys/types.h>

> #include <signal.h>

```C
int kill(pid_t pid, int sig);
```
- Appel systeme: est utilise pour envoyer n importe quel signal
a n importe quel processus.
- pid est positif -> sig est envoye au processus dont 
l id est indique par pid.
- pid vaut 0 -> sig est envoye a tous les processus appartenant 
au meme groupe que le groupe appelant.
- pid vaut -1 -> sig est envoye a tous les processus,
sauf celui du PID.
- sig vaut 0 -> aucun signal n est envoye mais les conditions 
d erreur sont verifiees.
- Valeur de retour: En cas de reussite -> 0, en cas d echec -> -1.
-------------------------------------------------------------------------------
#### --> _getpid_:
> #include <sys/types.h>

> #include <unistd.h>

```C
pid_t getpid(void);
```
- Renvoie l identifiant du processus appelant.
- Pas de cas d erreur.
-------------------------------------------------------------------------------
#### --> pause:
> #include <unistd.h>

```C
int pause(void);
```
- Force le processus appelant a s endormir jusqu a ce qu un signal soit recu,
qu il le termine ou lui fasse invoquer une fonction de gestionnaire de signal.
- Valeur renvoyee: -1 et errno si le signal a ete intercepte et que le 
gestionnaire s est termine.
-------------------------------------------------------------------------------
#### --> sleep:
> #include <unistd.h>

```C
unsigned int sleep(unsigned int nb_sec);
```
- Endort le processus jusqu a ce que nb_sec soit ecoulee,
ou jusqu a ce que le signal soit interrompu.
- Valeur de retour: renvoie 0 si le temps prevu s est ecoule,
ou le nombre de secondes restantes si l appel a ete interrompu.
-------------------------------------------------------------------------------
#### --> usleep:
> #include <unistd.h>

```C
int usleep(useconds_t usec);
```
- Meme chose que sleep, en microsecondes.
- Valeur de retour: 0 en cas de succes, -1 en cas d erreur.
-------------------------------------------------------------------------------
#### --> sigemptyset:
> #include <signal.h>

```C
int sigemptyset(sigset_t *set);
```
- Initialise l ensemble de signaux pointe par set, de sorte que tous les signaux
definit dans POSIX.1-2008 soient exclus.
- Valeur de retour: renvoie 0 en cas de reussite et -1 en cas d erreur
et definit errno pour indiquer l erreur.
-------------------------------------------------------------------------------
#### --> sigaddset:
```C
int sigaddset(sigset_t *set, int signum);
```
- Ajoute le signal signum a set.
- Valeur de retour: 0 en cas de succes et -1 en cas d erreur.
-------------------------------------------------------------------------------
#### --> sigaction:
> #include <signal.h>

```C
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
```C
struct sigaction
{
	void		(*sa_handler) (int);
	void		(*sa_sigaction) (int, siginfo_t *, void *);
	sigset_t	sa_mask;
	int			sa_flags;
	void		(*sa_restorer) (void);
}
```
	- ATTENTION: initialiser -> struct sigaction sa = {0}
- Appel systeme, sert a modifier l action effectuee par un processus 
a la reception d un signal specifique.
- signum indique le signal concerne.
- Si act est non nul, la nouvelle action est definie par act.
- Si oldact est non nul, l ancienne action est sauvegardee dans oldact.
- sa_handler indique l action affectee au signal signum. Il recoit le numero
de signal comme seul argument.
- sa_flags: specifie un ensemble d attributs qui modifie le comportement
du signal.
- Valeur de retour: 0 s il reussit et -1 s il echoue.

-------------------------------------------------------------------------------