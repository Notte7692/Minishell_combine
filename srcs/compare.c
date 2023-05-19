/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:59:42 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/17 15:40:17 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	compare(char *word, char *tmp)
{
	int	i;

	i = 0;
	if (tmp == NULL)
		return (1);
	while (word[i] != '\0' && tmp[i] != '\0')
	{
		if (word[i] != tmp[i])
			return (1);
		i++;
	}
	if (word[i] != tmp[i])
		return (1);
	return (0);
}