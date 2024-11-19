/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:49:24 by ayarab            #+#    #+#             */
/*   Updated: 2024/11/19 22:20:57 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isredirect(int token)
{
	if (token == R_RED || token == RR_RED || token == L_RED || token == LL_RED)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int ft_isnotr_ed(int token)
{
	if (token == RR_RED || token == L_RED || token == LL_RED)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
