/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:32 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/12 19:48:39 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commande_echo(char **word)
{
	bool	new_line;
	
	new_line = true;
	if (ft_strncmp(*word, "echo", ft_strlen(*word)) != 0)
		return (EXIT_FAILURE);
	word++;
	if (*word && ft_strncmp(*word, "-n", ft_strlen("-n") + 1) == 0)
	{
		new_line = false;
		word++;
	}
	while (*word)
	{
		write(1, *word, ft_strlen(*word));
		word++;
		if (word != NULL)
			write (1, " ", 1);
	}
	if (new_line)
		write(1, "\n", 1);
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
