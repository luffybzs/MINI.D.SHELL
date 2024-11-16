/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:49:24 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/16 16:23:18 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_isredirect(int token)
{
	if (token == R_RED || token == RR_RED || token == L_RED || token == LL_RED 
		|| token == PIPE)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}