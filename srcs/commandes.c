/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:32 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/19 16:46:13 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	commande_echo(char *first, char *word)
{
	int	i;

	i = 0;
	if (word == NULL)
		return ;
	while (first[i])
		i++;
	if (i == 4)
		printf ("%s\n", word);
	else
		printf ("%s", word);
}

//PAS FORCEMENT OPTI
int	commande_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("PWD");
		return (1);
	}
	return (0);
}

int	commande_cd(char *word)
{
	if (chdir(word) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
