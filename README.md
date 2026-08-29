# Minishell

Un shell minimaliste proche de bash, ecrit en C dans le cadre du projet 42.
Il reprend les bases d un vrai shell : prompt interactif, commandes externes,
builtins, pipes et redirections, avec gestion des quotes, des variables
d environnement et des signaux.

-------------------------------------------------------------------------------
## - FONCTIONNALITES

	- Prompt interactif colore (chemin courant) + historique readline.
	- Builtins : echo (-n), cd, pwd, export, unset, env, exit.
	- Commandes externes : resolution via PATH (execve) et ./executable.
	- Pipes : une ou plusieurs commandes chainees avec |.
	- Redirections : redirection simple de sortie >.
	- Quotes : double " et simple ' (suppression des quotes).
	- Variables d environnement : $VAR et code de sortie $?.
	- Signaux : Ctrl-C (nouvelle ligne + re-affichage du prompt), Ctrl-\ ignore.
-------------------------------------------------------------------------------
## - CONFIGURATION:

	Prerequis :
		- make
		- un compilateur C (clang)
		- libreadline-dev (headers de la bibliotheque readline)

	Installation des dependances (Debian/Ubuntu) :
		sudo apt install clang libreadline-dev

	Installation des dependances (macOS) :
		brew install readline
-------------------------------------------------------------------------------
## - LANCEMENT:

	- Compiler : make re
	- Lancer   : ./minishell
-------------------------------------------------------------------------------
## - UTILISATION:

	Quelques exemples de commandes :

		minishell> echo "hello minishell"
		hello minishell

		minishell> ls -la | grep minishell
		(remplit la sortie de ls -la)

		minishell> echo $HOME
		/home/alex

		minishell> echo $?
		0
-------------------------------------------------------------------------------
## - COMPILATION / TESTS:

	Verification des fuites memoires (valgrind) :

		valgrind --leak-check=full --show-leak-kinds=all --suppressions=vsupp ./minishell

	Note : readline genere environ 215 blocs non liberes (connus, neutralises
	via le fichier de suppressions vsupp).
-------------------------------------------------------------------------------
## - STRUCTURE DU PROJET:

	Minishell/
	|-- Makefile
	|-- minishell.h
	|-- *.c            (sources du shell)
	|-- libft/         (bibliotheque interne)
	|-- minishell_tester/ (tests externes du projet 42)
	|-- utils/         (sujets pdf, notes)
	`-- vsupp          (suppressions valgrind pour readline)
-------------------------------------------------------------------------------
## - LIMITATIONS:

	- Redirections >> et < non implementees (pas de heredoc).
	- Quotes : pas de distinction semantique double/simple, ni d imbrication.
	- Fuites memoires connues liees a readline (~215 blocs).
-------------------------------------------------------------------------------
## - AUTEURS:

	- vsaura
	- alamizan
-------------------------------------------------------------------------------