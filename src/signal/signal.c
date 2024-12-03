/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:41:50 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/03 17:25:51 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

// int ft_handle_signal(t_shell *shell)
// {


//     return (0);
// }

// void handle_sigint(t_shell *shell)
// {
    
// }

// void handle_sigquit(t_shell *shell)
// {
    
// }

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