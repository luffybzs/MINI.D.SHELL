/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:41:50 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/04 17:00:48 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include <signal.h>
#include <sys/signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <term.h>
#include <ncurses.h>


/*
Mode Interactif (comme un concert public) :


Ctrl+C (SIGINT) :

Comme un chef qui doit arrêter élégamment la musique pour
 un nouveau départ. Dans votre shell, il faut :

Arrêter la commande en cours si elle existe
Afficher un nouveau prompt sur une nouvelle ligne
Ne pas quitter le shell


Ctrl+\ (SIGQUIT) :

Comme un musicien qui fait une fausse note. Dans ce mode :

Ne rien faire du tout
Continuer l'exécution normale


Ctrl+D (EOF) :

Comme la fin programmée du concert. Il faut :

Quitter proprement le shell
S'assurer que toutes les ressources sont libérées




Mode Non-Interactif (comme une répétition enregistrée) :


Les signaux doivent être gérés de manière plus directe
Le comportement doit être plus proche de celui de 
bash en mode script
Pas d'affichage de prompt
Les erreurs doivent être gérées différemment
*/