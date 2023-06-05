#include "../include/minishell.h"

int	execute_child(t_exp_tok *exp_tok, char *abs_cmd_path, int status)
{
	int		s;

	if (exp_tok->in != STDIN_FILENO && dup2(exp_tok->in, STDIN_FILENO) == -1)
		return (ft_perror(EXIT_FAILURE, "dup2 error"));
	if (exp_tok->out != STDOUT_FILENO)
	{
		s = dup(STDOUT_FILENO);
		if (s == -1 || dup2(exp_tok->out, STDOUT_FILENO) == -1)
			return (ft_perror(EXIT_FAILURE, "dup error"));
	}
	status = execve(abs_cmd_path, exp_tok->cmd, get_envar()->env_var);
	perror(NULL);
	if (exp_tok->in != STDIN_FILENO)
	{
		close(exp_tok->in);
		dup2(0, exp_tok->in);
	}
	if (exp_tok->out != STDOUT_FILENO)
	{
		dup2(s, STDOUT_FILENO);
		close(s);
	}
	exit(status);
	return (status);
}

int	execute_builtin(t_exp_tok *exp_tok)
{
	if (ft_strcmp(exp_tok->cmd[0], "echo") == 0)
		return (echo(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "export") == 0)
		return (echo(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "env") == 0)
		return (env(exp_tok->cmd[0]));
	if (ft_strcmp(exp_tok->cmd[0], "cd") == 0)
		return (cd(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "pwd") == 0)
		return (pwd());
	if (ft_strcmp(exp_tok->cmd[0], "unset") == 0)
		return (unset(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "exit"))
		return (Commande_exit(exp_tok->cmd[0]));
	return (EXIT_FAILURE);
}

int	execute_builtin_child(t_exp_tok *exp_tok)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
	 return (EXIT_FAILURE);
	else if (pid == 0)
	{
		exit_status = execute_builtin(exp_tok);
		exit(exit_status);
		return (exit_status);
	}
	waitpid(pid, &exit_status, 0);
	return (exit_status);
}

int	exbuiltin_reset_fd(t_exp_tok *exp_tok, int pipes_save)
{
	if (exp_tok->in != STDIN_FILENO)
	{
		dup2(pipes_save[STDIN_FILENO], STDIN_FILENO);
		close(pipes_save[STDIN_FILENO]);
	}
	if (exp_tok->out != STDOUT_FILENO)
	{
		dup2(pipes_save[STDOUT_FILENO], STDOUT_FILENO);
		close(pipes_save[STDOUT_FILENO]);
	}
	return (EXIT_SUCCESS);
}
