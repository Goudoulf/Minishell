/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:26:37 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/12 14:50:51 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_append(char *buf, char *str, size_t *len)
{
	size_t	i;

	i = 0;
	while (buf[i] && buf[i] != '\n' && i < BUFFER_SIZE)
		i++;
	(*len) += i;
	if (buf[i] == '\n')
		str = ft_realloc(str, buf, ++(*len));
	else
		str = ft_realloc(str, buf, (*len));
	if (str == NULL)
		return (NULL);
	ft_substr2(buf, ++i);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	buf[BUFFER_SIZE];
	int			rvalue;
	size_t		len;

	len = 0;
	str = NULL;
	rvalue = 1;
	if (fd < 0)
		return (NULL);
	if (!buf[0])
		rvalue = read(fd, buf, BUFFER_SIZE);
	while (rvalue > 0)
	{
		str = ft_append(buf, str, &len);
		if (str == NULL)
			return (NULL);
		if (str[len - 1] == '\n')
			return (str);
		rvalue = read(fd, buf, BUFFER_SIZE);
	}
	if (rvalue < 0)
		return (ft_substr2(buf, BUFFER_SIZE), free(str), NULL);
	return (str);
}
