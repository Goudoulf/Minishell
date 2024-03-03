/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:44:20 by cassie            #+#    #+#             */
/*   Updated: 2024/03/03 10:06:12 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen2(char const *s, char c)
{
	int		i;
	size_t	n;

	n = 0;
	i = 0;
	while (s[i] == c)
		i++;
	while ((s[i]) && (s[i] != c))
	{
		i++;
		n++;
	}
	return (n);
}

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
		if (s[i])
			i++;
	}
	return (count);
}

static void	*ft_free_malloc(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

static char	**ft_split_split(char const *s, char c, size_t start, int i)
{
	int		count;
	char	**tab;

	count = ft_count(s, c);
	if (count == 0)
		count = 1;
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (count-- > 0)
	{
		tab[i] = malloc(sizeof(char) * (ft_strlen2((char *)&s[start], c) + 1));
		if (!tab[i])
			return (ft_free_malloc(tab, i));
		ft_strlcpy(tab[i], (char *) &s[start], ft_strlen2(&s[start], c) + 1);
		start = start + ft_strlen2((char *) &s[start], c) + 1;
		if (start > ft_strlen(s))
			start = ft_strlen(s);
		while (s[start] == c)
			start++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		start;
	char	*str;
	char	**tab;

	tab = 0;
	start = 0;
	if (!s)
		return (NULL);
	str = (char *) s;
	while ((str) && (str[start] == c))
		start++;
	tab = ft_split_split(s, c, start, 0);
	return (tab);
}
