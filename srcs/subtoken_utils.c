/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:04:04 by nassm             #+#    #+#             */
/*   Updated: 2023/05/27 14:31:52 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_subtoken_count(char *token[], int i)
{
    int count;
    int open_brack;

    count = 0;
    open_brack = 0;
    while(token[i])
    {
        if (ft_strchr(token[i], '('))
        {
            open_brack++;
            count++;
        }
        else if (ft_strchr(token[i], ')'))
        {
            open_brack--;
            count++;
        }
        if (open_brack == 0)
            break;
        i++;
    }
    return (count);
}

char    *get_end_subtoken(char *token[], int *i, char *sub_token)
{
    char    *tmp;
    int     len;

    len = ft_strrchr(token[*i], ')') - token[*i];
    tmp = ft_substr(token[*i], 0, len + 1);
    sub_token = ft_append(&sub_token, tmp);
    free(tmp);
    tmp = token[*i];
    token[*i] = ft_substr(tmp, len +1, ft_strlen(token[*i]));
    free(tmp);
    return (sub_token);
}