/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:12:18 by meharit           #+#    #+#             */
/*   Updated: 2023/07/28 14:51:37 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	pars_color(char *line, t_mlx *m, int ident)
{
	if (ident)
		m->map.sky_color = check_rgb(line);
	else
		m->map.floor_color = check_rgb(line);
}

void	pars_rgb(char *rgb)
{
	int	i;

	i = 0;
	if (rgb[i] == '-' || rgb[i] == '+')
		i++;
	while (rgb[i] && ft_isdigit(rgb[i]))
		i++;
	if (rgb[i])
		error_mess("RGB NOT DIGIT\n");
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	check_rgb_uti(char **rgb, int i)
{
	char	*n_rgb;
	char	**tt;
	int		j;

	while (rgb[i])
	{
		printf("->%s\n", rgb[i]);
		j = 0;
		while ((rgb[i][j] && (rgb[i][j] == ' ' || rgb[i][j] == '\t')) ||
				((rgb[i][j] && i == 0) && (rgb[i][j] == ' ' || rgb[i][j] == '\t'
							|| rgb[0][j] == 'F' || rgb[0][j] == 'C')))
			j++;
		if (rgb[i][j])
		{
			n_rgb = ft_strdup(&rgb[i][j]);
			free(rgb[i]);
			rgb[i] = n_rgb;
		}
		printf("=>%s\n", rgb[i]);
		tt = ft_space_split(rgb[i], ' ', '\t');
		if (tab_len(tt) != 1)
			error_mess("Space in RGB\n");
		free(rgb[i]);
		rgb[i] = ft_strdup(tt[0]);
		free_tab(tt);
		i++;
	}
}

int	check_rgb(char *str)
{
	int				i;
	char			**rgb;
	unsigned long	color[3];

	i = 0;
	comma(str);
	if (str[ft_strlen(str) - 2] == ',')
		error_mess("RGB invalid\n");
	rgb = ft_space_split(str, ',', '\n');
	// printf("%d\n", tab_len(rgb));
	check_rgb_uti(rgb, i);
	while (rgb[i])
	{
		pars_rgb(rgb[i]);
		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || color[i] > 255)
			error_mess("RGB invalid\n");
		i++;
	}
	if (i != 3)
		error_mess("RGB invalid\n");
	free_tab(rgb);
	return (color[0] * 256 * 256 + color[1] * 256 + color[2]);
}
