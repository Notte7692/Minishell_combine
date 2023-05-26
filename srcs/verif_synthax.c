/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:04:32 by nsalhi            #+#    #+#             */
/*   Updated: 2023/05/26 10:57:17 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_elem_char(char *rline, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (rline[i])
	{
		if (rline[i] == '\'')
			while (rline[++i] && rline[i] != '\'')
				;
		if  (rline[i] == '\"')
			while (rline[++i] && rline[i] != '\"')
				;
		if (rline[i] == c)
			count++;
		if (rline[i])
			i++;
	}
	return (count);
}

bool is_correct_subshell(char *rline, int i)
{
	while (i > 0 && rline[i] && rline[i] != '(')
		i--;
	if (i >= 0 && rline[i] != '(')
		return (false);
	return (true);
}

bool	bracket_closed(char *rline, int i)
{
	while (i > 0 && rline[i] != '(')
		i--;
	if (i >= 0 && rline[i] != '(')
		return (false);
	return (true);
}

bool	valid_synthax(char	*rline)
{
	int	i;

	i = 0;
	if (count_elem_char(rline, '(') != count_elem_char(rline, ')'))
		return (false);
	while (rline[i])
	{
		if (rline[i] == '\'')
			while (rline[++i] && rline[i] != '\'')
				;
		if (rline[i] == '\"')
			while (rline[++i] && rline[i] != '\"')
				;
		if (rline[i] == '(')
			if (!is_correct_subshell(rline, i - 1))
				return (false);
		if (rline[i] == ')')
			if (!bracket_closed(rline, i))
				return (false);
		if (rline[i] == ';' || rline[i] == '\\')
			return (false);
		if (rline[i])
			i++;
	}
	return (true);
}