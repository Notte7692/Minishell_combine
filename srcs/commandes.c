/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:32 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/17 17:45:32 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	commande_ls(char *word)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;

// 	if (word == NULL)
// 		exit (0);
// 	dir = opendir(word);
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		printf ("%s\n", entry->d_name);
// 	}
// 	closedir(dir);
// }

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

void	commande_pwd(void)
{
	printf ("/mnt/nfs/homes/nbechon/Projects/MiniShell");
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
