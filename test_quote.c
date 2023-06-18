#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./include/minishell.h"
#include <readline/readline.h>

bool    find_quote(char *token)
{
    if (strchr(token, '\'') != NULL || strchr(token, '\"') != NULL)
        return (true);
    else
    return (false);
}

bool    verif_even_squote(char *token)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (token[i])
    {
        if (token[i] == '\'' && token[i -1] != '\\')
            count++;
        i++;
    }
    if (count % 2 == 0)
        return (true);
    else
        return (false);
}

bool    verif_even_dquote(char *token)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(token[i])
    {
        if (token[i] == '\"' && token[i - 1] != '\\')
            count++;
        i++;
    }
    if (count % 2 == 0)
        return (true);
    else
        return (false);
}

bool    count_quote(char *token)
{
    int i;

    i = 0;
    while (token[i])
    {
        if (token[i] == '\'')
        {
            if (verif_even_squote(token))
                return (true);
            else
                return (false);
        }
        if (token[i] =='\"')
        {
            if (verif_even_dquote(token))
                return (true);
            else
                return (true);
        }
        i++;
    }
    return (false);
}

void    handle_squote(char **token)
{
    int i = 0;
    int j = 0;
    int count = 0;

    while ((*token) && (*token)[i])
    {
        if ((*token)[i] == '\'')
            count++;
        i++;
    }

    for (i = 0; (*token) && (*token)[i]; i++)
    {
        if ((*token)[i] != '\'' || ((*token)[i] == '\'' && (*token)[i - 1] == '\\')) 
        {
            (*token)[j] = (*token)[i];
            j++;
        }
    }

    (*token)[j] = '\0';
}

void    handle_dquote(char **token)
{
    int i = 0;
    int j = 0;

    while((*token) && (*token)[i])
    {
        if ((*token)[i] == '\\' && (*token)[i + 1] == '\"')
        {
            i++;
            (*token)[j] = (*token)[i];
            j++;
            i++;
        }
        if ((*token)[i] != '\"' || ((*token)[i] == '\"' && (*token)[i - 1] == '\\'))
        {
            (*token)[j] = (*token)[i];
            j++;
        }
        i++;
    }

    (*token)[j] = '\0';
}

char    *utils_core_jquote(char *token)
{
    int i;

    i = 0;
    while (token && token[i])
    {
        if (token[i] == '\'')
        {
            handle_squote(&token);
            break ;
        }
        if (token[i] == '\"')
        {
            handle_dquote(&token);
            break ;
        }
        i++;
    }
    return (token);
}

char    *core_jquote(char *token)
{
    if (count_quote(token))
        token = utils_core_jquote(token);
    return (token);
}

char **j_quote(char **token)
{
    int i;

    i = 0;
    while (token && token[i])
    {
        if (find_quote(token[i]))
           token[i] = core_jquote(token[i]);
        i++;
    }
    return (token);
}

int main() {
    // Read input from readline
    char* input = readline("Enter your command: ");

    // Allocate memory for the token string
    char** token = malloc(2 * sizeof(char*));
    token[0] = malloc(strlen(input) + 1);
    strcpy(token[0], input);
    token[1] = NULL;

    // Perform the quote handling
    j_quote(token);

    // Print the modified token
    printf("%s\n", token[0]);

    // Free the allocated memory
    free(token[0]);
    free(token);
    free(input);

    return 0;
}
/*
   echo command
    echo 'arg1" "arg2'
    echo ""e'""c""h""o""
    echo ''"sdfsdf'"sfsdf'
    echo "test '"string'""
    echo ''''''
    echo "arg"
    echo 'arg'
    echo ""
    echo''
    echo "test"test"
    echo 'test'test'
    echo "'"
    echo '""'
    echo "test'test"
    echo '"'"test"'"'
    echo ""test""test"""
    echo 'test'test'
    echo "''''"'"'"'"'"'"
    echo ''''''''''

    */