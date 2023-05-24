/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:14:28 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/24 14:54:59 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	commande_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf ("%s\n", env[i]);
		i++;
	}
}

void	commande_export(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf ("declare -x ");
		printf ("%s\n", env[i]);
		i++;
	}
}

void	commande_unset(char **env, char *word)
{
	int	j;
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (env[i] != NULL)
	{
		if (compare(env[i], word) == 0)
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found)
	{
		j = i;
		while (env[j] != NULL)
		{
			env[j] = env[j + 1];
			j++;
		}
	}
}

// void	printf_exit2(void)
// {
// 	printf ("bash: exit: too many arguments\n");
// 	return ;
// }

// void	printf_exit(char *arg)
// {
// 	printf ("bash: exit: %s: numeric argument required\n", arg);
// 	exit (0);
// }

void	commande_exit(char *input)
{
	char	arg[2000];
	int		i;
	int		count;
	int		j;

	j = 0;
	count = 0;
	i = 0;
	while (input[i] != ' ')
		i++;
	i++;
	j = i;
	while (input[j])
	{
		if (input[j] == ' ')
			printf_exit2();
		j++;
	}
	j = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			break ;
		arg[j] = input[i];
		j++;
		i++;
	}
	arg[j] = '\0';
	printf ("exit\n");
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == ' ')
			j++;
		if (arg[i] >= '0' || arg[i] <= '9')
			count++;
		if ((arg[i] >= 'a' && arg[i] <= 'z')
			|| (arg[i] >= 'A' && arg[i] <= 'Z'))
			printf_exit(arg);
		i++;
	}
	if (j >= 2)
		printf_exit2();
	if (count != i || count >= 20)
		printf_exit(arg);
	exit (0);
}
