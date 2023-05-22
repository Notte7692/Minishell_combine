/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:10:15 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/22 14:54:59 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	list_of_command(char *first, char *seconde)
{
	if (compare(first, ECHO) == 0 || compare(first, ECHO_N) == 0)
	{
		if (seconde == NULL)
			return ;
		commande_echo(first, seconde);
	}
	if (compare(first, EXIT) == 0)
		exit (0);
	if (compare(first, PWD) == 0)
		commande_pwd();
	if (compare(first, CD) == 0)
		commande_cd(seconde);
	if (compare(first, ENV) == 0)
		commande_env();
	free (first);
	free (seconde);
}

int	main(void)
{
	char	*user_input;
	char	*seconde;
	char	*first;

	while (1)
	{
		user_input = readline("$ ");
		add_history(user_input);
		first = take_firstword(user_input);
		seconde = take_second_word(user_input);
		list_of_command(first, seconde);
		// if (strcmp(user_input, "exit") == 0)
		// 	break ;
		free(user_input);
	}
	return (0);
}
