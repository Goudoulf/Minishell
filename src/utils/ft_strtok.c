/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:08:41 by cassie            #+#    #+#             */
/*   Updated: 2024/03/09 10:17:24 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int is_delim(char c, char *delim)
{
    while(*delim != '\0')
    {
        if(c == *delim)
            return 1;
        delim++;
    }
    return 0;
}

char *ft_strtok(char *string, char *delim)
{
    static char *string_copy;
    char *ret;
    char c_quote;
    bool    quote;

    quote = false;
    c_quote = 0;
    if(!string)
        string = string_copy;
    if(!string)
        return NULL;
    while(1)
    {
        if ((*string == '\"' || *string == '\''))
        {
            quote = !quote;
            c_quote = *string;
            //string++;
            break;
        }
        if(is_delim(*string, delim) && !quote)
        {
            string++;
            continue;
        }
        if(*string == '\0')
            return NULL; 
        break;
    }
    ret = string;
    string++;
    while(1)
    {
        if(*string == '\0')
        {
            string_copy = string;
            return ret;
        }
        if (*string == c_quote)
        {
            quote = false;
            c_quote = '\0';
            string++;
            continue ;
        }
        if (!quote && (*string == '\"' || *string == '\''))
        {
            quote = !quote;
            c_quote = *string;
            string++;
            continue ;
        }
        if(is_delim(*string, delim) && quote == false)
        {
            *string = '\0';
            string_copy = string + 1;
            return ret;
        }
        string++;
    }
}
