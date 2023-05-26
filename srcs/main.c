/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:10:15 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/25 19:52:40 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
/*
int	main(int argc, char *argv[], char **env)
{
	char				*user_input;
	char				*seconde;
	char				*first;
	char	**tab;
	t_token *token_stack;

	(void)argc;
	(void)argv;
	user_input = NULL;
	token_stack = NULL;
	tab = NULL;
	if (isatty(STDIN_FILENO))
	{
		signal_crtl();
		while (1)
		{
			user_input = readline("$ ");
			if (user_input == NULL)
				break ;
			tab = create_tab(user_input);
    		token_stack = create_token_stack(tab);
    		print_token_stack(token_stack);
			free_token_stack(token_stack);
    		free_tab(tab);
			add_history(user_input);
			first = take_firstword(user_input);
			seconde = take_second_word(user_input);
			list_of_command(first, seconde, env, user_input);
			free(user_input);
		}
	}
	else
		printf("L'entrée standard n'est pas un terminal interactif.\n");
	
	return (0);
}
*/