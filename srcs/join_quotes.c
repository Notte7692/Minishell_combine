/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:09:47 by nassm             #+#    #+#             */
/*   Updated: 2023/05/26 14:16:30 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_quote_pos(char *str)
{
	int	squote_pos;
	int	dquote_pos;

	squote_pos = ft_strclen(str, '\'');
	dquote_pos = ft_strclen(str, '\"');
	if (squote_pos < dquote_pos);
		return (squote_pos);
	return (dquote_pos);
}

t_quote *init_quote(char ***token, int i)
{
	t_quote *quote;

	quote = ft_calloc(1, sizeof(t_quote));
	quote->i = i;
	quote->j = i;
	quote->start = (*token)[i];
	quote->len = find_quote_pos(quote->start);
	quote->start = ft_strdup(quote->start + quote->len);
	if (quote->start == NULL)
	{
		free(quote);
		quote = NULL;
		return (NULL);
	}
	if (*quote->start == '\'')
		quote->quote = ft_strdup("\'");
	else
		quote->quote = ft_strdup("\"");
	if (quote->quote == NULL)
	{
		ft_free_str(&quote->start);
		free(quote);
		return (NULL);
	}
	return (quote);
}

int join_token(char ***token, int i)
{
	t_quote *quote;
	int     verif;

	quote = init_quote(token, i);
	if (quote == NULL)
		return (EXIT_FAILURE);
	
}

int join_quote(char ***token)
{
	int i;

	i = 0;
	if (*token == NULL)
		return (EXIT_FAILURE);
	while ((*token)[i])
	{
		if ((*token)[i] && ft_setinstr((*token)[i], "\'\"") == true)
		{
			i
		}
		 
	}
}