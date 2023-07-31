/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:16:14 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/31 19:07:54 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_vertical_textures(t_mlx *m)
{
	m->t[EAST].xpm_ptr = mlx_xpm_file_to_image(m->mlx_ptr, m->t[EAST].path,
			&m->t[EAST].wt, &m->t[EAST].ht);
	if (m->t[EAST].xpm_ptr == 0)
	{	
		printf("texture not found: %s\n", m->t[EAST].path);
		exit(1);
	}
	m->t[EAST].addr = mlx_get_data_addr(m->t[EAST].xpm_ptr,
			&m->t[EAST].bits_per_pixel, &m->t[EAST].line_length,
			&m->t[EAST].endian);
	m->t[WEST].xpm_ptr = mlx_xpm_file_to_image(m->mlx_ptr, m->t[WEST].path,
			&m->t[WEST].wt, &m->t[WEST].ht);
	if (m->t[WEST].xpm_ptr == 0)
	{	
		printf("texture not found: %s\n", m->t[WEST].path);
		exit(1);
	}
	m->t[WEST].addr = mlx_get_data_addr(m->t[WEST].xpm_ptr,
			&m->t[WEST].bits_per_pixel, &m->t[WEST].line_length,
			&m->t[WEST].endian);
}

void	open_textures(t_mlx *m)
{
	m->t[NORTH].xpm_ptr = mlx_xpm_file_to_image(m->mlx_ptr, m->t[NORTH].path,
			&m->t[NORTH].wt, &m->t[NORTH].ht);
	if (m->t[NORTH].xpm_ptr == 0)
	{	
		printf("texture not found: %s\n", m->t[NORTH].path);
		exit(1);
	}
	m->t[NORTH].addr = mlx_get_data_addr(m->t[NORTH].xpm_ptr,
			&m->t[NORTH].bits_per_pixel, &m->t[NORTH].line_length,
			&m->t[NORTH].endian);
	m->t[SOUTH].xpm_ptr = mlx_xpm_file_to_image(m->mlx_ptr, m->t[SOUTH].path,
			&m->t[SOUTH].wt, &m->t[SOUTH].ht);
	if (m->t[SOUTH].xpm_ptr == 0)
	{	
		printf("texture not found: %s\n", m->t[SOUTH].path);
		exit(1);
	}
	m->t[SOUTH].addr = mlx_get_data_addr(m->t[SOUTH].xpm_ptr,
			&m->t[SOUTH].bits_per_pixel, &m->t[SOUTH].line_length,
			&m->t[SOUTH].endian);
	open_vertical_textures(m);
}
