/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_jquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:27:55 by nassm             #+#    #+#             */
/*   Updated: 2023/05/27 14:47:36 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../include/minishell.h"

int first_start(char ***token, t_quote *quote)
{
    *token = ft_add_str_to_tab((token), quote->i, quote->start);
    if (*token == NULL)
        return (EXIT_FAILURE);
    (*token)[quote->i] = ft_realloc_str((*token)[quote->i], quote->len);
    if ((*token)[quote->i] == NULL)
        return (EXIT_FAILURE);
    quote->i++;
    if (ft_strlen(quote->start)> 1
            && ft_setinstr(quote->start +1, quote->quote))
    {
        quote->end = ft_strdup(ft_strchr(quote->start +1, *quote->quote) + 1);
        (*token)[quote->i] = ft_realloc_str((*token)[quote->i],
                ft_strclen(quote->start +1, *quote->quote +2));
        if (ft_strlen(quote->end) >= 1)
            *token = ft_add_str_to_tab(token, quote->i, quote->end);
        return (EXIT_SUCCESS);
    }
    quote->j = quote->i;
    quote->i++;
    return (2);
}

int second_start_norm(char ***token, t_quote *quote)
{
    if (ft_strlen(quote->end) >= 2)
    {
        quote->end = ft_strdup(quote->end +1);
        if (quote->end == NULL)
            return (EXIT_FAILURE);
        (*token)[quote->j] = ft_realloc_str((*token)[quote->j],
				ft_strclen((*token)[quote->j] + 1, *quote->quote) + 2);
            return (EXIT_FAILURE);
    }
    else
        quote->end = NULL;
    return (EXIT_SUCCESS);
}

int second_start(char ***token, t_quote *quote)
{
    quote->i++;
    if (ft_setinstr((*token)[quote->i], quote->quote) == true)
    {
        (*token)[quote->i] = ft_strstrjoin((*token)[quote->i],
                (*token)[quote->i], " ");
        if ((*token)[quote->i] == NULL)
            return (EXIT_FAILURE);
        quote->end = ft_strchr((*token)[quote->j] + 1, *quote->quote);
        if (second_start_norm(token, quote) == EXIT_FAILURE)
            return (EXIT_FAILURE);  
        if (ft_strlen(quote->end) >= 1)
        {   
            ft_free_str(&(*token)[quote->i]);
            (*token)[quote->i] = ft_strdup(quote->end);
            if ((*token)[quote->i] == NULL)
                return (EXIT_FAILURE);
        }    
        else
            ft_free_single_str(token, quote->i);
        return (EXIT_SUCCESS);
    }
    return (2);
}

int special_start(char ***token, t_quote *quote, int i)
{
    quote->end  = ft_strchr(quote->start + 1, *quote->quote);
    if (ft_strlen(quote->end) > 1)
    {
        quote->end = ft_strdup(quote->end + 1);
        if (quote->end == NULL)
            return (EXIT_FAILURE);
    }
    else
        quote->end = NULL;
    quote->start = ft_realloc_str(quote->start,
            ft_strclen(quote->start + 1, *quote->quote + 2));
    if (quote->start == NULL)
        return (EXIT_FAILURE);
    ft_free_str(&(*token)[i]);
    (*token)[i] = ft_strdup(quote->start);
    if (quote->end != NULL)
        ft_add_str_to_tab(token, i, quote->end);
    return (EXIT_SUCCESS);
}

int token_join_all(char ***token, t_quote *quote, int i)
{
    int check;

    if (quote == NULL)
        return (EXIT_FAILURE);
    if ((ft_strchr(quote->start +1, *quote->quote) != NULL) 
            && ft_strcmp((*token)[i], quote->start) == 0)
    {
        if (special_start(token, quote, i) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        else
            return (EXIT_SUCCESS);
    }
    if (quote->len > 0)
    {
        check = first_start(token, quote);
        if (check != 2)
            return (check);
    }
    else
    {
        check = second_start(token, quote);
        if (check != 2)
            return (check);
    }
    return (2);
}