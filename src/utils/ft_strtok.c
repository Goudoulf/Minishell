/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:08:41 by cassie            #+#    #+#             */
/*   Updated: 2024/02/23 12:43:32 by cassie           ###   ########.fr       */
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
    static bool    quote;

    if (!quote)
        quote = false;
    if(!string)
        string = string_copy;
    if(!string)
        return NULL;
    while(1)
    {
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
    while(1)
    {
        if(*string == '\0')
        {
            string_copy = string;
            return ret;
        }
        if(is_delim(*string, delim) && !quote)
        {
            *string = '\0';
            string_copy = string + 1;
            return ret;
        }
        string++;
    }
}
