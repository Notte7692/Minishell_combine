/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:59:10 by nassm             #+#    #+#             */
/*   Updated: 2023/05/27 15:46:48 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../include/minishell.h"

void	*ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab &&tab[i])
	{
		ft_free_str(&tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	*free_token(char **token, char **resized)
{
	ft_free_tab(token);
	ft_free_tab(resized);
	reset_lex_token();
	return (NULL);
}

char    *get_next_token(char **token)
{
	char    *next_token;
	char    *tmp;
	char    next_spe;
	int     i;

	tmp= *token;
	next_spe = get_next_special(tmp);
	next_token = ft_calloc(get_next_token_size(tmp, next_spe) + 1, \
			sizeof(*next_token));;
	if (next_token == NULL)
		return (NULL);
	i = 0;
	if (*tmp == next_spe)
		while(*tmp && *tmp == next_spe)
			next_token[i++] = *tmp++;
	tmp = ft_substr(*token, i, ft_strlen(*token));
	if (*token == NULL)
		return (ft_free((void **)&next_token));
	free(*token);
	*token = tmp;
	return (next_token);
}

char    *get_subtoken(char *token[], int *i)
{
	char    *subtoken;
	int     subtoken_count;

	subtoken = NULL;
	subtoken_count = get_subtoken_count(token, *i);
	while (token[*i] && subtoken_count)
	{
		if (subtoken_count == 1 && ft_strchr(token[*i], ')')
				&& ft_strlen(ft_strrchr(token[*i], ')')) != 1)
			return (get_end_subtoken(token, i, subtoken));
		subtoken = ft_append(&subtoken, " ");
		if (subtoken == NULL)
			return (NULL);
		if (ft_strchr(token[*i], '(') || ft_strchr(token[*i], ')'))
			subtoken_count--;
		(*i)++;
	}
	return (subtoken);
}

char    **resize_token(char **token)
{
	char    **resized;
	size_t  resized_size;
	int     i[2];

	resized_size = 50;
	resized = ft_calloc(resized_size + 1, sizeof(*resized));
	if (resized == NULL)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while(token[i[0]])
	{
		if (token[i[0]][0] == '(')
			resized[i[1]] = get_subtoken(token, &i[0]);
		else if (!token_is_right(token[i[0]]))
			resized[i[1]] = ft_strdup(token[i[0]++]);
		else
			resized[i[1]] = get_next_token(&token[i[0]]);
		if (resized[i[1]++] == NULL)
			return (free_token(token, resized));
		if ((size_t)i[1] == resized_size - 1)
			resized = ft_realloc_str_arr(resized, resized_size += 10);			
	}
	ft_free_str_array(&token);
	return (resized);
}

int lexer(char  *rline)
{
	char    **token;
	
	if (!valid_synthax_str(rline))
		return (0);
	token = ft_split_set(rline, " \t\r\v\f\n");
	if (join_quote(&token) == EXIT_FAILURE)
	{
		ft_free_str_array(&token);
		return (EXIT_FAILURE);
	}
	token = resize_token(token);
	if (token == NULL)
		return (EXIT_FAILURE);
	set_lex_token(token);
	if (!valid_syntax_token(token))
		return (130);
	else
		return(1);
}

/*
int main() {
    char input[100];
    printf("Enter a command: ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0';  // Remove newline character

    int result = lexer(input);

    printf("Lexer result: %d\n", result);

    if (result == 1) {
        char **tokens = get_lex_token(NULL, false);
        if (tokens != NULL) {
            printf("Tokens:\n");
            for (int i = 0; tokens[i] != NULL; i++) {
                printf("%s\n", tokens[i]);
            }
        }
    }

    return (0);
}
*/