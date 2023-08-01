/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_uti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:45:55 by meharit           #+#    #+#             */
/*   Updated: 2023/08/01 19:47:27 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	comma(char *str)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		error_mess("RGB invalid\n");
}

void	check_id(char *rgb, int *i)
{
	int	c_f;

	c_f = 0;
	while ((rgb[*i] && (rgb[*i] == ' ' || rgb[*i] == '\t' || rgb[*i] == 'F'
				|| rgb[*i] == 'C')))
	{
		if (!c_f && (rgb[*i] == 'F' || rgb[*i] == 'C'))
			c_f++;
		else if (c_f && (rgb[*i] == 'F' || rgb[*i] == 'C'))
			error_mess("no!no!\n");
		*i = *i + 1;
	}
}
