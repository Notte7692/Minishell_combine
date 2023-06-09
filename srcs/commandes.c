/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:32 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/09 16:26:01 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commande_echo(char **word)
{
	int	i;

	i = 1;
	if (word[0] == NULL)
		return (EXIT_FAILURE);
	if (word[2] == NULL)
		ft_printf ("%s\n", word[1]);
	else
	{
		if (ft_strcmp(word[1], "-n") == 0)
			i = 2;
		while (word[i])
		{
			ft_printf("%s", word[i]);
			if (word[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(word[1], "-n") != 0)
			write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}

int	commande_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("PWD");
		return (EXIT_FAILURE);
	}
}

int	commande_cd(char **word)
{
	if (chdir(word[1]) != 0)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
