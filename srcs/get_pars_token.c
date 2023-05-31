/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pars_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:08:44 by nassm             #+#    #+#             */
/*   Updated: 2023/05/31 15:35:12 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The functionis responsible for retrieving and managing a static variable
	static_pars_token, which stores a pointer to
	an array of t_par_tok structures.
*/

static t_par_tok	**_get_par_toks(t_par_tok **par_toks, bool reset)
{
	static t_par_tok	**static_par_toks = NULL;

	if (par_toks == NULL && !reset)
		return (static_par_toks);
	if (reset)
	{
		static_par_toks = NULL;
		return (NULL);
	}
	static_par_toks = par_toks;
	return (static_par_toks);
}

t_par_tok	**get_pars_token(void)
{
	return (_get_par_toks(NULL, false));
}

/*
	The function retrieves the current t_par_tok token from the t_par_tok array.

	* It first calls the get_iter function to retrieve the current iterator iter.

	* If iter is NULL, indicating that there is no valid iterator,
	it returns NULL indicating no current token.
	
	* Otherwise, it calls the get_pars_token function to retrieve
	the t_par_tok array and accesses the element at the index iter[par].

	* It returns the retrieved t_par_tok token.
*/

t_par_tok	*get_current_par_token(void)
{
	t_iter	*iter;

	iter = get_iter();
	if (iter == NULL)
		return (NULL);
	return (get_pars_token()[iter[par]]);
}

void	set_pars_token(t_par_tok **pars_token)
{
	_get_par_toks(pars_token, false);
}

/*
	The function is a void function that resets the t_par_tok array
	to its initial state. 
*/

void	reset_pars_token(void)
{
	_get_par_toks(NULL, true);
}