/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:14:28 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/08 18:26:45 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commande_env(char **env)
{
	int	i;

	i = 0;
	if (env == NULL || *env == NULL)
		return (EXIT_FAILURE);
	while (env[i] != NULL)
	{
		printf ("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	commande_export(char **env)
{
	int	i;

	i = 0;
	if (env == NULL || *env == NULL)
		return (EXIT_FAILURE);
	while (env[i] != NULL)
	{
		printf ("declare -x ");
		printf ("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	commande_unset(char **env, char *word)
{
	int	j;
	int	i;
	int	found;

	i = 0;
	found = 0;
	if (env == NULL || *env == NULL)
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}

static bool	valid_exit(char **tab)
{
	int	i;
	int	j;
	
	i = 0;
	while(tab && tab[i])
	{
		j = 0;
		while(tab[i][j])
		{
			if (ft_issign(tab[i][j]))
				j++;
			if (!ft_isdigit(tab[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	commande_exit(char **tab)
{
	long	exit_code;
	int		i;

	i = 0;
	if (ft_strncmp(tab[i], "exit", ft_strlen(tab[i])) != 0)
		return (EXIT_FAILURE);
	i++;
	if (tab[i])
		exit_code = ft_atol(tab[i]);
	else
		exit_code = get_err_code();
	if (!valid_exit(tab + i) || ft_strlen(tab[i]) > 19)
	{
		ft_fprintf(STDERR_FILENO, "exit: not a valid argument\n");
		exit_code = 255;
	}
	else if (tab[i] && tab[++i])
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		ft_fprintf(STDERR_FILENO, "exit\n");
		return (EXIT_FAILURE);
	}
	ft_fprintf(STDERR_FILENO, "exit\n");
	exit(exit_code);
	return (exit_code);
}