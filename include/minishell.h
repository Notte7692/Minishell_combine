/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:10:07 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/27 15:41:56 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
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

//////////////////// strucure-quote  //////////////

typedef struct s_quote
{
	int		i;
	int		j;
	int		len;
	char	*start;
	char	*end;
	char	*quote;
}	t_quote;

//////////////////// structure-token //////////////

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;


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
int		tab_size(char *str);
char	**create_tab(char *av);
t_token *create_token_stack(char **av);
void 	print_token_stack(t_token *head);
void 	free_token_stack(t_token *head);

//////////// verif_synthax.c ////////////////////

bool	valid_synthax_str(char	*rline);
int		count_elem_char(char *rline, char c);
bool 	is_correct_sub(char *rline, int i);
bool	bracket_closed(char *rline, int i);

//////////////// get_lex_set.c ///////////////////

void	reset_lex_token(void);
void	set_lex_token(char **lex_toks);
char	**get_lexic_token(void);
char	**get_lex_token(char **lex_toks, bool reset);

//////////////// get_token_utils.c ///////////////

bool	verif_is_token(char *token);

///////////////	join_quotes.c ///////////////////

int		find_quote_pos(char *str);
t_quote *init_quote(char ***token, int i);
int 	join_token(char ***token, int i);
int 	join_quote(char ***token);

/////////////// lexer.c /////////////////////////

void	*ft_free_tab(char **tab);
void	*free_token(char **token, char **resized);
char    *get_next_token(char **token);
char    *get_subtoken(char *token[], int *i);
char    **resize_token(char **token);

/////////////// sub_token_utils.c ////////////////

int		get_subtoken_count(char *token[], int i);
char    *get_end_subtoken(char *token[], int *i, char *sub_token);

//////////////// utils_jquote.c ///////////////////

int		first_start(char ***token, t_quote *quote);
int 	second_start_norm(char ***token, t_quote *quote);
int 	second_start(char ***token, t_quote *quote);
int 	special_start(char ***token, t_quote *quote, int i);
int 	token_join_all(char ***token, t_quote *quote, int i);

/////////////// utils_jquote_bis.c ////////////////

int		combine_loop(char ***token, t_quote *quote);
int		token_join_end_one(char ***token, t_quote *quote);

///////////////// utils_token.c //////////////////

bool    token_is_right(char *token);
char    get_next_special(char *token);
size_t  get_next_token_size(char *token, char next_spe);

////////////// check_token_synthax,c /////////////

bool	is_redirection(char *token);
bool	is_correct_spe(char	*token);
bool	is_correct_pipe(char *current, char *next);
bool	is_special(char *token, int type);
bool	valid_syntax_token(char	*token[]);

///////////////////////////////////////////////////

#endif