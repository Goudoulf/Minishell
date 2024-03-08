/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:44:20 by cassie            #+#    #+#             */
/*   Updated: 2024/03/04 15:27:54 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_sign(const char *str, int i )
{
	int	c;

	c = 1;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == '-')
			c = c * -1;
	}
	return (c);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			c;
	long int	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	c = ft_sign(str, i);
	if (str[i] == 45 || str[i] == 43)
		i++;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		if (c > 0 && (result * c < 0))
			return (-1);
		if (c < 0 && (result * c > 0))
			return (0);
		result = result * 10 + (str[i] - '0');
		if ((str[i + 1] < 48) || (str[i + 1] > 57))
			return ((int)result * c);
		i++;
	}
	return (0);
}
