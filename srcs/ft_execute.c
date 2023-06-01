/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:45:10 by nassm             #+#    #+#             */
/*   Updated: 2023/06/01 19:20:20 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	this function is used to remove the outer quotes from a command
	string if they exist.
*/

char	*clean_cmd(char *cmd)
{
	char	*ok_cmd;
	int		cmd_len;
	int		i;
	int		j;

	cmd_len = ft_strlen(cmd);
	if (cmd[0] != '\'' && cmd[0] != '\"')
		return (cmd);
	if(cmd[cmd_len - 1] != cmd[0])
		return (cmd);
	ok_cmd = ft_calloc(cmd_len +1, sizeof(*ok_cmd));
	if (ok_cmd == NULL)
	{
		free(cmd);
		return (NULL);
	}
	i = 1;
	j = 0;
	while( i < cmd_len - 1)
		ok_cmd[j++] = cnd[i++];
	free(cmd);
	return (ok_cmd);
}

/*
	This function cleans the outer quotes from each command in
	the exp_tok->cmd array, ensuring that the commands are properly formatted 
*/
int clean_quote_exp_tok_cmd(t_exp_tok *exp_tok)
{
	int	i;
	
	i = 0;
	while(exp_tok && exp_tok->cmd &&exp_tok->cmd[i])
	{
		exp_tok->cmd[i] = clen_cmd(exp_tok->cmd[i])
		if (exp_tok->cmd[i] == NULL)
		{
			ft_free_split(exp_tok->cmd);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

int ft_execute(t_exp_tok *exp_tok)
{
	int exit_status;

	if (exp_tok == NULL)
		return (EXIT_SUCCESS)
	if (clean_quote_exp_tok_cmd(exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if 	(is_builtin(exp_tok->cmd[0]))
		//il va falloir gerer les cas particuliers des builtin

	//il va falloir retrouver le chemin absolu des cmds
	//peut etre creer un char * pour ca

	//verifier les conditions avant execution

	//creer une fonction aqui va faire l'execution et renvoyer u int a exit status
	
	//free et renvoyer exit_status
		
}