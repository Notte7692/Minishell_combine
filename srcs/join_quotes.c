/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:09:47 by nassm             #+#    #+#             */
/*   Updated: 2023/05/27 12:47:48 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_quote_pos(char *str)
{
	int	squote_pos;
	int	dquote_pos;

	squote_pos = ft_strclen(str, '\'');
	dquote_pos = ft_strclen(str, '\"');
	if (squote_pos < dquote_pos)
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

int	end_join(t_quote *quote, int e_status)
{
	ft_free_str(&quote->start);
	ft_free_str(&quote->end);
	ft_free_str(&quote->quote);
	free(quote);
	return (e_status);
}

int join_token(char ***token, int i)
{
	t_quote *quote;
	int     verif;

	quote = init_quote(token, i);
	if (quote == NULL)
		return (EXIT_FAILURE);
	verif = token_join_all(token, quote, i);
	if (verif != 2)
		return (end_join(quote, verif));
	if (combine_loop(token, quote) == EXIT_FAILURE)
		return (end_join(quote, EXIT_FAILURE));
	if ((*token)[quote->i] == NULL)
		return (end_join(quote, EXIT_SUCCESS));
	if (token_join_end_one(token, quote) == EXIT_FAILURE)
		return (end_join(quote, EXIT_FAILURE));
	return (end_join(quote, EXIT_SUCCESS));
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
			if (join_token(token, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			else
			{
				if (ft_setinstr((*token)[i], "\'\"") == false)
					i += 2;
				else
					i++;
			}
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}