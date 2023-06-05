/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:56:51 by nassm             #+#    #+#             */
/*   Updated: 2023/06/01 14:53:12 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is responsible for opening the input file(s) specified by
	the redirection tokens in the par_token and updating
	the input file descriptor in the exp_tok structure.

	*The function open_in takes two parameters: par_token, a pointer to a
	structure t_par_tok containing tokenized command information, and exp_tok
	 a pointer to a structure t_exp_tok containing command execution information.
    
	*It declares several variables, including i for iteration, fd for
	file descriptor, and heredeoc_fd to store the file descriptor
	if it is redirected from a here-document.
    
	*If the input file descriptor in exp_tok is not STDIN_FILENO,
	it means there is a redirection from a here-document,
	so the value is stored in heredeoc_fd.
    
	*The function then enters a loop to process each input redirection
	token in par_token until it encounters a token with
	no redirection (NULL or a different redirection type).
    
	*Inside the loop, it checks if the input redirection token is not a
	here-document token (indicated by not matching <<).
	If it is not a here-document token, it opens the
	file specified by the token using open with the O_RDONLY flag.
    
	*If the file fails to open (fd == -1), it returns an appropriate
	error status using ft_perror and EXIT_FAILURE.
    
	*If the input redirection token is a here-document token,
	it assigns the heredeoc_fd to fd.
    
	*If there are more input redirection tokens to process,
	it checks if the fd is not the heredeoc_fd and not equal to standard input
	or output (0 or 1). If so, it closes the file descriptor.
    
	*After processing all input redirection tokens, it updates the
	input file descriptor in exp_tok with the final fd.
    
	*Finally, it returns EXIT_SUCCESS to indicate successful execution.
*/

static int	open_in(t_par_tok *par_token, t_exp_tok *exp_tok)
{
	int		i;
	int		fd;
	int		heredeoc_fd;

	i = 0;
	fd = 0;
	if (exp_tok->in != STDIN_FILENO)
		heredeoc_fd = exp_tok->in;
	while (par_token->redir_type[is_in] || par_token->redir_type[is_in_heredoc])
	{
		if (ft_strncmp(par_token->in[i++], "<<", 2) != 0)
			fd = open(par_token->in[i], O_RDONLY);
		else if (par_token->redir_type[is_in_heredoc])
			fd = heredeoc_fd;
		if (fd == -1)
			return (ft_perror(EXIT_FAILURE, "open error"));
		if (par_token->in[i + 1] == NULL)
			break ;
		if (fd != heredeoc_fd && fd != 0 && fd != 1)
			close(fd);
		i++;
	}
	exp_tok->in = fd;
	return (EXIT_SUCCESS);
}

/*
	The function  is responsible for opening the output file(s) specified
	by the redirection tokens in the par_token and updating
	the output file descriptor in the exp_tok structure.

	*The function open_out takes two parameters: par_token, a pointer to a structure
	t_par_tok containing tokenized command information, and exp_tok,
	a pointer to a structure t_exp_tok containing command execution information.
    
	*It declares two variables, i for iteration and fd for file descriptor,
	initializing fd to 1, which represents standard output.
    
	*The function enters a loop to process each output redirection token
	in par_token until it encounters a token with
	no redirection (NULL or a different redirection type).
    
	*Inside the loop, it checks if the output redirection token corresponds
	to a regular output redirection (>) or an append output redirection (>>).
    
	*If it is a regular output redirection token, it opens the file specified
	by the next token using open with
	flags O_RDWR | O_CREAT | O_TRUNC and file permissions 0644.
    
	*If it is an append output redirection token, it opens the file specified
	by the next token using open with flags O_RDWR | O_CREAT | O_APPEND and file permissions 0644.
    
	*If the file fails to open (fd == -1), it returns an appropriate
	error status using ft_perror and EXIT_FAILURE.
    
	*If there are more output redirection tokens to process, it checks
	if the fd is not equal to standard input or output (0 or 1).
	If so, it closes the file descriptor.
    
	*After processing all output redirection tokens, it updates the output
	file descriptor in exp_tok with the final fd.
    
	*Finally, it returns EXIT_SUCCESS to indicate successful execution.
*/

static int	open_out(t_par_tok *par_token, t_exp_tok *exp_tok)
{
	int		i;
	int		fd;

	i = 0;
	fd = 1;
	while (par_token->redir_type[is_out] || par_token->redir_type[is_out_append])
	{
		if (par_token->redir_type[is_out]
			&& ft_strcmp(par_token->out[i++], ">") == 0)
			fd = open(par_token->out[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (par_token->redir_type[is_out_append]
			&& ft_strcmp(par_token->out[i++], ">>") == 0)
			fd = open(par_token->out[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (ft_perror(EXIT_FAILURE, "open error"));
		if (par_token->out[i + 1] == NULL)
			break ;
		if (fd != 0 && fd != 1)
			close(fd);
		i++;
	}
	exp_tok->out = fd;
	return (EXIT_SUCCESS);
}

int	handle_redir(t_par_tok *par_tok, t_exp_tok *exp_tok, int pipe_type)
{
	int	exit_status;
	
	if (open_in(par_tok, exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (open_out(par_tok, exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (handle_pipes(exp_tok, pipe_type) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (par_tok->redir_type[is_pipe] == true)
		exp_tok->is_pipe = true;
	else
		exp_tok->is_pipe = false;
	if (par_tok->type == subshell)
		return (execute_subshell(exp_tok));
	exit_status = 
}