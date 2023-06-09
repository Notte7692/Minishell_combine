/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:10:15 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/09 16:44:25 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
void	list_of_command(char *first, char *seconde, char **env, char *input)
{
	if (compare(first, ECHO) == 0 || compare(first, ECHO_N) == 0)
	{
		if (seconde == NULL)
			return ;
		commande_echo(first, seconde);
	}
	if (compare(first, EXIT) == 0)
		commande_exit(input);
	if (compare(first, PWD) == 0)
		commande_pwd();
	if (compare(first, CD) == 0)
		commande_cd(seconde);
	if (compare(first, ENV) == 0)
		commande_env(env);
	if (compare(first, EXPORT) == 0)
		commande_export(env);
	if (compare(first, UNSET) == 0)
		commande_unset(env, seconde);
	free (first);
	free (seconde);
}
*/

static int	exit_core(void *to_free, int exit_status)
{
	char	**args;

	if (exit_status == EXIT_CTRL_D)
	{
		args = ft_calloc(3, sizeof(args));
		args[0] = ft_strdup("exit");
		args[1] = ft_itoa(get_err_code());
		exit_builtin(args);
		ft_free_split(args);
	}
	rl_clear_history();
	free(to_free);
	free_envar(get_envar());
	return (exit_status);
}

static int	core(void)
{
	char	*buff;
	int		exit_code;
	
	while(true)
	{
		buff = readline("minishell$ ");
		if (ft_strlen(buff) > 0)
			add_history(buff);
		if (buff == NULL)
			return (exit_core((void *)buff, EXIT_CTRL_D));
		exit_code = lexer(buff);
		if (exit_code == EXIT_FAILURE)
			return (exit_core((void *)buff, EXIT_FAILURE));
		free(buff);
	}
	return (exit_core((void *)buff, EXIT_FAILURE));
}

static int	manage_flags(int ac, char *av[])
{
	int	exit_code;

	if (ac != 3 || ft_strcmp(av[1], "-c") != 0)
	{
		ft_fprintf(STDERR_FILENO, "Usage: ./minishell [Flag] \"[Command]\"\n");
		ft_fprintf(STDERR_FILENO, "\t-c\tExecute Command without promot\n");
		return (EXIT_FAILURE);
	}
	exit_code = lexer(av[2]);
	free_envar(get_envar());
	return (exit_code);
}

static int	hide_ctrl_c(void)
{
	t_exp_tok	*stty;

	stty = malloc(sizeof(*stty));
	if (stty == NULL)
		return (EXIT_FAILURE);
	stty->cmd = ft_calloc(3, sizeof(*stty->cmd));
	if (stty->cmd == NULL)
		return (EXIT_FAILURE);
	stty->cmd[0] = ft_strdup("/bin/stty");
	if (stty->cmd[0] == NULL)
		return (EXIT_FAILURE);
	stty->cmd[1] = ft_strdup("-echoctl");
	if (stty->cmd[1] == NULL)
		return (EXIT_FAILURE);
	stty->in = STDIN_FILENO;
	stty->out = STDOUT_FILENO;
	if (ft_execute(stty) == EXIT_FAILURE)
	{
		ft_free_tab(stty->cmd);
		free(stty);
		return (EXIT_FAILURE);
	}
	ft_free_tab(stty->cmd);
	free(stty);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*envar;
	
	global_signal();
	envar = init_envar(envp);
	if (envar == NULL)
		return (EXIT_FAILURE);
	set_envp(envp);
	set_envar(envar);
	if (hide_ctrl_c() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ac != 1)
		return (manage_flags(ac, av));
	if (core() == EXIT_FAILURE)
	{
		free_envar(envar);
		return (EXIT_FAILURE);
	}
	free_envar(envar);
	return (EXIT_SUCCESS);
}
