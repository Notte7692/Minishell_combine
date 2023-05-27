/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:35:55 by nassm             #+#    #+#             */
/*   Updated: 2023/05/27 14:54:38 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../include/minishell.h"

bool    token_is_right(char *token)
{
    if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
        return (false);
    if ((ft_strchr(token, '|') && !ft_strstr(token, "||"))
            || (ft_strchr(token, '<') && !ft_strstr(token, "<<"))
            || (ft_strchr(token, '>') &&   !ft_strstr(token, ">>")))
        if (ft_strlen(token) != 1)
            return (true);
    if (ft_strstr(token, "&&") || ft_strstr(token, "<<")
            || ft_strstr(token, ">>") || ft_strstr(token, "||"))
        if (ft_strlen(token) != 2)
            return (true);
    return (false);
}


char    get_next_special(char *token)
{
    while (*token)
    {
        if (*token == '|' || *token == '<'
                || *token == '>' || *token == ';')
            return (*token);
        if (*token == '&' && *(token +1) && *(token + 1) == '&')
            return (*token);
        token++;
    }
    return ('\0');
}

size_t  get_next_token_size(char *token, char next_spe)
{
    size_t  size;

    size = 0;
    if (*token == next_spe)
    {
        while(*token && *token == next_spe)
        {
            token++;
            size++;
        }
    }
    else
    {
        while (*token && *token != next_spe)
        {
            token++;
            size++;
        }
    }
    return (size);
}
