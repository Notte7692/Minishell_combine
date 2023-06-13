/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:09:47 by nassm             #+#    #+#             */
/*   Updated: 2023/06/13 17:33:30 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The functionis used to find the position of the first occurrence of 
	either a single quote (') or a double quote (") within a given string str.

	* The function uses ft_strclen to find the position of 
	the first single quote (') occurrence within the string str, 
	and assigns it to the variable squote_pos.

	* It also uses ft_strclen to find the position of 
	the first double quote (") occurrence within the string str, 
	and assigns it to the variable dquote_pos.

	* The function compares the values of squote_pos and dquote_pos. 
	If squote_pos is less than dquote_pos, it means the first occurrence 
	of a single quote appears before the first occurrence of a double quote, 
	and the function returns squote_pos.

	* If dquote_pos is less than or equal to squote_pos, it means either 
	the first occurrence of a double quote appears before the first occurrence of 
	a single quote or there are no quotes in the string. 
	In this case, the function returns dquote_pos.
*/

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

/*
	The functions responsible for initializing a structure 
	t_quote used for storing information about a quote 
	within a tokenized array of strings.

	* The function allocates memory for a t_quote structure using 
	ft_calloc and assigns it to the variable quote.

	* It sets the i and j fields of the quote structure to 
	the provided value i, indicating the position of 
	the quote within the token array.

	* The function sets the start field of the quote structure to 
	the i-th token in the token array.

	* It uses the find_quote_pos function to determine 
	the length of the quote and sets the len field of 
	the quote structure accordingly.

	* The function updates the start field of the quote structure 
	by duplicating the substring starting after the quote using ft_strdup.

	* The function checks the type of quote (single quote or double quote) 
	by examining the first character of the start field. 
	It assigns the corresponding quote character to the quote field of 
	the quote structure using ft_strdup.

	* Finally, the function returns the initialized quote structure.
*/

t_quote *init_quote(char ***token, int i)
{
	t_quote	*quote;

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

/*
	The functionis responsible for 
	freeing the memory allocated for a t_quote structure 
	and returning an exit status.
*/

int	end_join(t_quote *quote, int e_status)
{
	ft_free_str(&quote->start);
	ft_free_str(&quote->end);
	ft_free_str(&quote->quote);
	free(quote);
	return (e_status);
}

/*
	The functionis responsible for joining tokens in the token array based on quotes.

	* The function calls the init_quote function to initialize a t_quote structure 
	based on the provided token array and position i. 
	If initialization fails (returns NULL), it returns EXIT_FAILURE.

	* The function then calls the token_join_all function to join all tokens 
	within the specified quote range, as indicated by the quote structure. 
	The result is stored in the verif variable.

	* If the verif value is not equal to 2, indicating a failure in joining tokens, 
	the function calls the end_join function 
	to free the allocated memory and returns the verif value.

	* If the verif value is equal to 2, the function proceeds 
	to call the combine_loop function to further process and 
	combine the tokens within the quote range. 
	If the combine_loop function returns EXIT_FAILURE, 
	the function calls end_join to free the memory and returns EXIT_FAILURE.

	* If the token at the position quote->i in the token array is NULL, 
	indicating that all tokens within the quote range have been successfully joined, 
	the function calls end_join to free the memory and returns EXIT_SUCCESS.

	* If the token_join_end_one function fails to join the end of the last token 
	within the quote range, the function calls end_join 
	to free the memory and returns EXIT_FAILURE.

	* Finally, if none of the above conditions are met, 
	the function calls end_join to free the memory and returns EXIT_SUCCESS.
*/

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

/*
	The function is responsible for joining tokens within quotes in the token array.
	
	* The function initializes a variable i to 0 to keep 
	track of the current position in the token array.

	* t checks if the token array is NULL. If so, it returns EXIT_FAILURE 
	indicating a failure.

	* The function enters a loop that iterates through each element in the token array.
	
	* Within the loop, it checks if the current token at position i exists 
	and contains single or double quotes (' or "). 
	If so, it calls the join_token function to join the tokens within the quote range.
	If the join_token function returns EXIT_FAILURE, indicating a failure,
	the function returns EXIT_FAILURE. Otherwise, it performs the following checks:
		- If the current token at position i no longer contains any quotes (' or "),
		it increments i by 2.
		- Otherwise, if the current token still contains quotes, it increments i by 1.
		
	* If the current token does not contain any quotes, the function simply increments i by 1 
	and continues to the next token.

	* Once all tokens have been processed, the function returns EXIT_SUCCESS 
	to indicate successful execution.
*/

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