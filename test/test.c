/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:05:30 by cassie            #+#    #+#             */
/*   Updated: 2024/02/21 21:54:54 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned int is_delim(char c, char *delim)
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

    if(!string)
        string = string_copy;
    if(!string)
        return NULL;
    while(1)
    {
        if(is_delim(*string, delim))
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
        if(is_delim(*string, delim))
        {
            *string = '\0';
            string_copy = string + 1;
            return ret;
        }
        string++;
    }
}
int main()
{
    char string[] = "<include ls -l \"-a\"\"test\"";
    char *delim = " \"";
    char *token = ft_strtok(string, delim);

    while(token)
    {
        printf("%s\n", token);
        token = ft_strtok(NULL, delim);
    }
    return 0 ;
}
