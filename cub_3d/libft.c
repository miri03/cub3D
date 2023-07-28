/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:40:04 by meharit           #+#    #+#             */
/*   Updated: 2023/07/27 15:47:46 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	count;

	count = 0;
	while (s1[count] != '\0' || s2[count] != '\0')
	{
		if (s1[count] != s2[count])
			return (s1[count] - s2[count]);
		count++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL && fd >= 0)
		write(fd, s, ft_strlen(s));
}

unsigned long	ft_atoi(const char *str)
{
	unsigned long	result;
	int				i;
	int				sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
		if (result > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return ((result * sign));
}

// char	*ft_strdup(const char *s1)
// {
// 	int		i;
// 	char	*ptr;

// 	i = 0;
// 	ptr = NULL;
// 	if (!s1)
// 		return (NULL);
// 	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
// 	if (ptr == NULL)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }
