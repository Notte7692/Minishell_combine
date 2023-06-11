/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:14:28 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/11 14:41:50 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commande_env(char **tab)
{
	int		i;
	t_env	*envar;

	envar = get_envar();
	if (envar == NULL || envar->env_var == NULL)
		return (EXIT_FAILURE);
	if (tab != NULL && tab[1] != NULL)
	{
		if (access(tab[1], F_OK) == 0)
		{
			ft_fprintf(STDERR_FILENO, "env: %s: Permission denied\n", tab[1]);
			return (126);
		}
		ft_fprintf(2, "env: %s: No such file or directory\n", tab[1]);
		return (127);
	}
	i = 0;
	while (envar->env_var && envar->env_var[i] != NULL)
	{
		if (ft_printf("%s\n", envar->env_var[i++]) == 0)
			return (EXIT_FAILURE);
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

/////////////////////// unset///////////////////

static char	*ft_get_var(t_env *envar, int i)
{
	char	**split;
	char	*var;

	split = ft_split(envar->env_var[i], '=');
	if (split == NULL)
		return (NULL);
	var = ft_strdup(split[0]);
	ft_free_str_array(&split);
	return (var);
}

static void	ft_suppr_var(t_env *envar, int i)
{
	int	j;

	ft_free_str(&envar->env_var[i]);
	j = i;
	while (envar->env_var[j + 1])
	{
		envar->env_var[j] = envar->env_var[j + 1];
		j++;
		if (envar->env_var[j + 1] == NULL)
			envar->env_var[j] = NULL;
		i = ft_str_arr_len(envar->env_var);
	}
}

static int	norm_unset(char **tab, t_env *envar, int i, int j)
{
	char	*var;

	var = NULL;
	if (ft_strcmp(envar->env_var[i], tab[j]) == 0
			|| ft_strcmp(envar->env_var[i], tab[j]) == 61)
	{
		var = ft_get_var(envar, i);
		if (var == NULL)
			return (EXIT_FAILURE);
		if (ft_strncmp(var, tab[j], ft_strlen(var)) != 0
				|| ft_strncmp(var, tab[j], ft_strlen(tab[j]) != 0))
		{
			ft_free_str(&var);
			return (2);
		}
		ft_suppr_var(envar, i);
	}
	ft_free_str(&var);
	return (EXIT_SUCCESS);
}

int	commande_unset(char **tab)
{
	int		i;
	int		j;
	int		out;
	t_env	*envar;

	j = 1;
	envar = get_envar();
	if (tab[j] == NULL)
		return (EXIT_SUCCESS);
	while (tab[j])
	{
		i = 0;
		while (envar->env_var)
		{
			out = norm_unset(tab, envar, i, j);
			if (out == 2)
				break ;
			else if (out == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

/////////// EXIT ///////////////

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