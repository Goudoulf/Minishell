/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:11:36 by cassie            #+#    #+#             */
/*   Updated: 2024/03/09 09:18:07 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *get_next_token(char **string, char *delim, char *c_quote) {
    char *ret = NULL;
    while (**string != '\0') {
        if (**string == '\"' || **string == '\'') {
            *c_quote = **string;
            (*string)++;
            return *string - 1;
        }
        if (is_delim(**string, delim) && !(*c_quote)) {
            (*string)++;
            continue;
        }
        ret = *string;
        (*string)++;
        while (**string != '\0') {
            if (**string == *c_quote) {
                *c_quote = '\0';
                (*string)++;
                continue;
            }
            if (!(*c_quote) && (**string == '\"' || **string == '\'')) {
                *c_quote = **string;
                (*string)++;
                continue;
            }
            if (is_delim(**string, delim) && !(*c_quote)) {
                **string = '\0';
                (*string)++;
                return ret;
            }
            (*string)++;
        }
    }
    return ret;
}

char *ft_strtok_quote(char *string, char *delim) {
    static char *string_copy;
    char c_quote = '\0';
    if (!string) string = string_copy;
    if (!string) return NULL;
    char *token = get_next_token(&string, delim, &c_quote);
    if (*string != '\0') string_copy = string;
    return token;
}

