/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:59:10 by nassm             #+#    #+#             */
/*   Updated: 2023/05/26 13:33:22 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../include/minishell.h"

int lexer(char  *rline)
{
    char    **token;
    
    if (!valid_synthax(rline))
        return (0);
    token = ft_split_set(rline, " \t\r\v\f\n");
    

}
