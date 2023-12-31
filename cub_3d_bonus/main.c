/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:48:13 by hhattaki          #+#    #+#             */
/*   Updated: 2023/08/02 17:34:13 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	renderer(void *t)
{
	t_mlx	*m;

	m = t;
	m->map.map_img = mlx_new_image(m->mlx_ptr, m->map.x_elements_nb
			* m->map.tile,
			m->map.y_elements_nb * m->map.tile);
	m->addr = mlx_get_data_addr(m->map.map_img, &m->bits_per_pixel,
			&m->line_length, &m->endian);
	draw_map(m);
	cast_rays(m);
	m->img_ptr = mlx_new_image(m->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bits_per_pixel,
			&m->line_length, &m->endian);
	draw_walls(m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_ptr, 0, 0);
	mlx_destroy_image(m->mlx_ptr, m->img_ptr);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->map.map_img,
		0 - (m->p.x - 125), 0 - (m->p.y - 75));
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr,
		m->weapon.t[m->weapon.frame].xpm_ptr, 750, 400);
	mlx_destroy_image(m->mlx_ptr, m->map.map_img);
}

void	pars(t_mlx *m, char **argv)
{
	int	fd;
	int	start;

	fd = open_map(argv[1]);
	start = textures(fd, m);
	height_len(fd, m);
	if (!m->t[0].path || !m->t[1].path || !m->t[2].path || !m->t[3].path
		|| m->map.sky_color == -1 || m->map.floor_color == -1)
		error_mess("identifier missing\n");
	map(argv[1], start, m);
}

int	main(int argc, char **argv)
{
	t_mlx	*m;

	if (argc != 2)
		error_mess("Wrong number of arguments\n");
	m = malloc(sizeof(t_mlx));
	init_pars(m);
	pars(m, argv);
	m->rays = malloc(NB_RAYS * sizeof(t_ray));
	m->mlx_ptr = mlx_init();
	init(m);
	m->win_ptr = mlx_new_window(m->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, "cub3d");
	weapon(m);
	mlx_hook(m->win_ptr, 17, 0, red_cross, 0);
	mlx_hook(m->win_ptr, 2, 0, keys_down, m);
	mlx_hook(m->win_ptr, 6, 0, mouse, m);
	mlx_loop_hook(m->mlx_ptr, move, m);
	mlx_hook(m->win_ptr, 3, 0, keys_up, m);
	mlx_loop(m->mlx_ptr);
}
