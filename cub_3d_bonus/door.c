/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:16:14 by hhattaki          #+#    #+#             */
/*   Updated: 2023/08/03 13:58:26 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_door_color(t_mlx *m, int index, double wall_height, int frame)
{
	double	x_pic;
	double	y_pic;
	int		color;

	y_pic = (index / wall_height) * m->door.frames[frame].ht;
	x_pic = floor(m->rays[m->ray].xwall / m->map.tile) * m->map.tile;
	x_pic = ((m->rays[m->ray].xwall - x_pic) / m->map.tile)
		* m->door.frames[frame].wt;
	if (m->rays[m->ray].down == 1)
		x_pic = m->door.frames[frame].wt - x_pic;
	if (m->rays[m->ray].hit == VERTICAL)
	{
		x_pic = floor(m->rays[m->ray].ywall / m->map.tile) * m->map.tile;
		x_pic = ((m->rays[m->ray].ywall - x_pic) / m->map.tile)
			* m->door.frames[frame].wt;
		if (m->rays[m->ray].right == -1)
			x_pic = m->door.frames[frame].wt - x_pic;
	}
	color = my_mlx_pixel_get(&m->door.frames[frame], x_pic, y_pic);
	return (color);
}

void	*open_door(void *p)
{
	t_mlx	*m;
	double	x;
	double	y;

	m = p;
	x = (int)(m->rays[NB_RAYS / 2].xwall) / m->map.tile;
	y = (int)(m->rays[NB_RAYS / 2].ywall) / m->map.tile;
	if (m->rays[NB_RAYS / 2].down == -1
		&& m->rays[NB_RAYS / 2].hit == HORIZONTAL)
		y--;
	if (m->rays[NB_RAYS / 2].right == -1
		&& m->rays[NB_RAYS / 2].hit == VERTICAL)
		x--;
	m->map.map[(int)y][(int)x] = 'o';
	while (m->door.frame < 12)
	{
		usleep(200000);
		m->door.frame++;
	}
	m->door.frame = 0;
	m->map.map[(int)y][(int)x] = 'd';
	return (0);
}

void	*close_door(void *p)
{
	t_mlx	*m;
	double	x;
	double	y;
	int		size;

	m = p;
	size = 0;
	x = m->p.x + (cos(m->p.angle) * size);
	y = m->p.y + (sin(m->p.angle) * size);
	while (x >= 0 && x < m->map.x_elements_nb * m->map.tile && y >= 0
		&& y < m->map.y_elements_nb * m->map.tile
		&& m->map.map[(int)y / m->map.tile][(int)x / m->map.tile] != 'd')
	{
		size++;
		x = m->p.x + (cos(m->p.angle) * size);
		y = m->p.y + (sin(m->p.angle) * size);
	}
	if (x >= 0 && x < m->map.x_elements_nb * m->map.tile && y >= 0
		&& y < m->map.y_elements_nb * m->map.tile)
		m->map.map[(int)y / m->map.tile][(int)x / m->map.tile] = 'D';
	return (0);
}

void	door(t_mlx *m)
{
	pthread_t	door;

	if (m->rays[NB_RAYS / 2].hit_door && !m->door.frame)
	{
		pthread_create(&door, 0, open_door, m);
		pthread_detach(door);
	}
	else if (m->map.map[(int)m->p.y / m->map.tile][(int)m->p.x / m->map.tile]
			!= 'd')
	{
		pthread_create(&door, 0, close_door, m);
		pthread_detach(door);
	}
}
