/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:13:03 by nassm             #+#    #+#             */
/*   Updated: 2023/05/27 18:23:04 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_error_code(int err_code, bool set_err)
{
    static int  static_err_code = 0;
    
    if (set_err)
        static_err_code = err_code;
    return (static_err_code);
}

void    set_err_code(int err_code)
{
    static bool last_cmd_ctrlc = false;

    if  (last_cmd_ctrlc)
    {
        last_cmd_ctrlc = false;
        return ;
    }
    if (err_code == 130)
        last_cmd_ctrlc = true;
    get_error_code(err_code, true);
}

int	get_err_code(void)
{
	return (get_error_code(0, false));
}