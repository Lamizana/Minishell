# Minishell

Interpréteur de commandes (shell) minimaliste en C, réalisé avec **libft** et
la bibliothèque **readline** dans le cadre du projet **42**.

[![Langage C](https://img.shields.io/badge/Langage-C-00599C)](#)
[![Projet 42](https://img.shields.io/badge/Projet-42-000000)](#)
[![Compilateur clang](https://img.shields.io/badge/Compilateur-clang-262D3D)](#)
[![Bibliothèque readline](https://img.shields.io/badge/Biblioth%C3%A8que-readline-7B2CBF)](#)
[![Build Makefile](https://img.shields.io/badge/Build-Makefile-8B0000)](#)

---

## Stack Technique

- **Langage** : C
- **Compilateur** : clang
- **Bibliothèques** : libft (interne), readline
- **Build** : Makefile

---

## Fonctionnalités

- **Builtins** : `echo` (`-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Commandes externes** : résolution via `PATH` (`execve`) et `./exécutable`
- **Pipes** : enchaînement simple et multiple avec `|`
- **Redirection** : redirection simple de sortie `>`
- **Quotes** : simple `'` et double `"`
- **Variables** : expansion `$VAR` et code de sortie `$?`
- **Signaux** : `Ctrl-C` (réaffiche le prompt), `Ctrl-\` ignoré
- **Prompt** : coloré (chemin courant) + historique readline

---

## Installation locale

# Prérequis (Debian/Ubuntu)
sudo apt install clang libreadline-dev

# Prérequis (macOS)
brew install readline

---

## Commandes

Compilation | Description
--- | ---
`make re` | Compiler le projet
`./minishell` | Lancer le shell

---

## Tests

# Vérification des fuites mémoire
valgrind --leak-check=full --show-leak-kinds=all --suppressions=vsupp ./minishell

Note : readline génère environ 215 blocs non libérés (connus, neutralisés via
le fichier de suppressions `vsupp`).

---

## Limitations

- Redirections `>>` et `<` non implémentées (pas de heredoc).
- Quotes : pas de distinction sémantique double/simple, ni d'imbrication.
- Fuites mémoire connues liées à readline (~215 blocs).

---

## À Propos

Développé par **vsaura** & **alamizan** - Étudiants 42.