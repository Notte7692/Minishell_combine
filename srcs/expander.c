/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:01:00 by nassm             #+#    #+#             */
/*   Updated: 2023/05/30 21:28:55 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
int	execute_subshell(t_exp_tok *exp_tok)
{
	pid_t	pid;
	int		status;
	char	*cutted_cmd;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		cutted_cmd = ft_substr(exp_tok->cmd[0], 1,
				ft_strrchr(exp_tok->cmd[0], ')') - exp_tok->cmd[0] - 1);
		if (cutted_cmd == NULL)
			return (EXIT_FAILURE);
		status = lexer(cutted_cmd);
		free(cutted_cmd);
		exit(get_error_code());
	}
	waitpid(pid, &status, 0);
	set_err_code(WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

static bool	is_redir(t_par_tok *par_tok)
{
	if (par_tok->redir_type[is_in] || par_tok->redir_type[is_in_heredoc] \
	|| par_tok->redir_type[is_out] || par_tok->redir_type[is_out_append] \
	|| par_tok->redir_type[is_pipe])
		return (true);
	return (false);
}

static int process_expression_tokens(t_exp_tok *exp_toks[], t_par_tok *par_toks[])
{
	int	i;

	i = 0;
	while (exp_toks[i] && par_toks[i])
	{
		if (par_toks[i]->type == and || par_toks[i]->type == or)
		{
			if ((par_toks[i]->type == and && get_error_code() != EXIT_SUCCESS) \
			|| (par_toks[i]->type == or && get_error_code() == EXIT_SUCCESS))
				i++;
			
		}
	}
}
*/