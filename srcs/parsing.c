/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:04:32 by nsalhi            #+#    #+#             */
/*   Updated: 2023/05/24 16:18:35 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlen(const char *str)
{
	int		i;

	if (str != NULL)
	{
		i = 0;
		while (str[i])
			i++;
		return (i);
	}
	return (0);
}

int	tab_size(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(str && str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '/' || str[i] == '.')
		{
			count++;
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
                    || str[i] == '/' || str[i] == '.'))
                i++;
		}
        if (str[i] == '-')
        {
            count++;
            while (str[i] && (str[i] == '-' || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
                i++;
        }
		if (str[i] == '<')
        {
			count++;
            while (str[i] && str[i] == '<')
                i++;
        }
		if (str[i] == '>')
        {
			count++;
            while (str[i] == '>')
                i++;
        }
		if (str[i] == '\'')
        {
			count++;
            while (str[i] && str[i] == '\'')
                i++;
        }
		if (str[i] == '"')
        {
			count++;
            while (str[i] && str[i] == '"')
                i++;
        }
        if (str[i] == '|')
        {
			count++;
            while (str[i] && str[i] == '|')
                i++;
        }
		else
			i++;
    }
	return (count);
}

char	**tab(char *av)
{
	int	i;
	int	start;
	int	j;
	char	**tab;

	tab = calloc(tab_size(av) + 1, sizeof(char*));
	i = 0;
	j = 0;
    while (av[i])
    {
        if ((av[i] >= 'a' && av[i] <= 'z') || (av[i] >= 'A' && av[i] <= 'Z') || av[i] == '/' || av[i] == '.')
        {
			start = i;
            while (av[i] && ((av[i] >= 'a' && av[i] <= 'z') || (av[i] >= 'A' && av[i] <= 'Z')
                    || av[i] == '/' || av[i] == '.'))
                i++;
			tab[j] = strndup(&av[start], i - start);
			j++;
        }
        if (av[i] == '-')
        {
           start = i;
            while (av[i] && (av[i] == '-' || (av[i] >= 'a' && av[i] <= 'z') || (av[i] >= 'A' && av[i] <= 'Z')))
                i++;
            tab[j] = strndup(&av[start], i - start);
			j++;
        }
        else if (av[i] == '<')
        {
			start = i;
            while (av[i] && av[i] == '<')
                i++;
			tab[j] = strndup(&av[start], i - start);
			j++;
        }
        else if (av[i] == '>')
        {
			start = i;
            while (av[i] == '>')
                i++;
			tab[j] = strndup(&av[start], i - start);
			j++;
        }
        else if (av[i] == '\'')
        {
			start = i;
            while (av[i] && av[i] == '\'')
                i++;
			tab[j] = strndup(&av[start], i - start);
			j++;
        }
        else if (av[i] == '"')
        {
			start = i;
            while (av[i] && av[i] == '"')
                i++;
			tab[j] = strndup(&av[start], i - start);
			j++;
        }
        else if (av[i] == '|')
        {
			start = i;
            while (av[i] && av[i] == '|')
                i++;
			tab[j] = strndup(&av[start], i - start);
			j++;
        }
		else
			i++;
    }
	return (tab);
}

t_token *create_token_stack(char **av)
{
    t_token *head = NULL;
    t_token *current = NULL;

    for (int i = 0; av[i] != NULL; i++) {
        t_elem *elem = malloc(sizeof(t_elem));
        elem->value = strdup(av[i]);

        if (av[i][0] == '<' ) 
            elem->type = RED_INF;
        else if(av[i][0] == '-')
            elem->type = FLAG;
        else if (av[i][0] == '>' && ft_strlen(av[i]) == 1)
            elem->type = TRUNCATE;
        else if (av[i][0] == '>' && ft_strlen(av[i]) > 1)
            elem->type = APPEND;
        else if (av[i][0] == '|')
            elem->type = PIPES;
        else if (av[i][0] == '\'')
            elem->type = SQUOTE;
        else
            elem->type = COMMAND;

        // Create a new token node
        t_token *node = malloc(sizeof(t_token));
        node->elem = elem;
        node->previous = NULL;
        node->next = NULL;

        if (head == NULL)
        {
            head = node;
            current = node;
        }
        else
        {
            current->next = node;
            node->previous = current;
            current = node;
        }
    }

    return head;
}

void print_token_stack(t_token *head) {
    t_token *current = head;
    while (current != NULL) {
        printf("Value: %s, Type: %d\n", current->elem->value, current->elem->type);
        current = current->next;
    }
}

void free_token_stack(t_token *head) {
    t_token *current = head;
    while (current != NULL) {
        t_token *temp = current;
        current = current->next;
        free(temp->elem->value);  // Free the allocated value
        free(temp->elem);
        free(temp);
    }
}

/*
int main() {
    //char *av[] = {"<command", "arg1", "<", "|", "env_var", ">>", ">", "\'", "\"", NULL};
    char input[] = "hello world <<< >>>> >> < >cat ls -la cat | ls .txt | command";
    char **av = tab(input);

    t_token *token_stack = create_token_stack(av);
    print_token_stack(token_stack);

    // Free the allocated memory
    free_token_stack(token_stack);

    return 0;
}


int main() {
    char input[] = "hello world <<< >>>> >> < >cat ls -la cat | ls .txt | command";
    char **result = tab(input);

    if (result == NULL) {
        printf("Erreur : échec de l'allocation mémoire.\n");
        return 1;
    }

    printf("Résultat :\n");
    for (int i = 0; result[i] != NULL; i++) {
        printf("Token %d: %s\n", i, result[i]);
    }

    // Libérer la mémoire
    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}
*/
