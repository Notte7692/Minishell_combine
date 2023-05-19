/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:10:07 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/19 16:41:22 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

void	commande_ls(char *word);

void	commande_echo(char *first, char *word);

int		commande_pwd(void);

char	*take_second_word(char argv[]);

char	*take_firstword(char *argv);

int		compare(char *word, char *tmp);

int		commande_cd(char *word);

#endif