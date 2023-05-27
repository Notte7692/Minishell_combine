/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_jquote_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:13:34 by nassm             #+#    #+#             */
/*   Updated: 2023/05/27 14:34:04 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int combine_loop(char ***token, t_quote *quote)
{
	while (*token && (*token)[quote->i]
			&& ft_setinstr((*token)[quote->i], quote->quote) == false)
	{
		(*token)[quote->j] = ft_strstrjoin((*token)[quote->i],
				(*token)[quote->i], " ");
		if ((*token)[quote->j] == NULL)
			return (EXIT_FAILURE);
		ft_free_single_str(token, quote->i);
	}
	return (EXIT_SUCCESS);
}

/*
	the token_join_end_one function is responsible for handling the joining 
	and splitting of tokens based on quotes, ensuring the correct 
	manipulation of tokens within the tokens array.
*/

int	token_join_end_one(char ***token, t_quote *quote)
{
	quote->end = ft_strdup((*token)[quote->i]);
	if (quote->end == NULL)
		return (EXIT_FAILURE);
	quote->len = ft_strclen(quote->end, *quote->quote) + 1;
	(*token)[quote->j] = ft_append_len_div(&(*token)[quote->j],
			quote->end, quote->len, " ");
	if ((*token)[quote->j] == NULL)
		return (EXIT_FAILURE);
	if (quote->end[quote->len] == '\0')
		ft_free_single_str(token, quote->i);
	else
	{
		ft_free_str(&(*token)[quote->i]);
		(*token)[quote->i] = ft_strdup(quote->end + quote->len);
		if ((*token)[quote->i] == NULL)
			return	(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}