/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:55:46 by nassm             #+#    #+#             */
/*   Updated: 2023/05/27 10:48:18 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	verif_is_token(char *token)
{
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		return (true);
	return (false);
}
