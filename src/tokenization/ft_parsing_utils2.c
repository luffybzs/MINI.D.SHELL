/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:49:24 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/02 14:46:53 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isredirect(int token)
{
	if (token == R_RED || token == RR_RED || token == L_RED || token == LL_RED)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	ft_is_file(int token)
{
	if (token == RR_RED)
		return (APPEND);
	else if (token == R_RED)
		return (OUTFILE);
	else if (token == L_RED)
		return (INFILE);
	else if (token == LL_RED)
		return (END_OF_FILE);
	return (-1);
}
