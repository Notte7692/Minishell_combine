/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:10:07 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/24 17:20:50 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ECHO "echo"
# define ECHO_N "echo -n"
# define CD "cd"
# define PWD "pwd"
# define EXIT "exit"
# define ENV "env"
# define EXPORT "export"
# define UNSET "unset"


//////////////////// ENUM ////////////////////

typedef enum
{
	COMMAND = 0,
	RED_INF,
	PIPES,
	ENV_VAR,
	SUBSTITUTE,
	SQUOTE,
	DQUOTE,
	FLAG,
	APPEND,
	TRUNCATE,

}	arg_type;

//////////////////// TOKEN_ELEM ///////////////////

typedef struct s_elem
{
	char	*value;
	arg_type	type;
}	t_elem;

/////////////////// TOKEN_STRUCT //////////////////

typedef struct s_stack
{
	t_elem *elem;
	struct s_stack	*previous;
	struct s_stack *next;
}	t_token;

//////////////////// signal.c /////////////////////

void	signal_crtl(void);

//////////////////// commandes.c //////////////////

void	commande_echo(char *first, char *word);
int		commande_pwd(void);
int		commande_cd(char *word);

///////////////// takeword.c ////////////////////

char	*take_second_word(char *user_input);
char	*take_firstword(char *user_input);

//////////////// compare.c //////////////////////

int		compare(char *word, char *tmp);

//////////////// commandes2.c //////////////////

void	commande_env(char **env);
void	commande_export(char **env);
void	commande_unset(char **env, char *var_name);
void	commande_exit(char *input);

////////////// all_printf.c ////////////////////

void	printf_exit2(void);
void	printf_exit(char *arg);

/////////////// parsing.c //////////////////////
void	free_tab(char **tab);
size_t	ft_strlen(const char *str);
int	tab_size(char *str);
char	**create_tab(char *av);
t_token *create_token_stack(char **av);
void print_token_stack(t_token *head);
void free_token_stack(t_token *head);

///////////////////////////////////////////////////

#endif