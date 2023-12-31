/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:00:27 by hhattaki          #+#    #+#             */
/*   Updated: 2023/07/31 21:49:05 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	if (angle < 0 || angle > 2 * M_PI)
	{
		if (angle < 0)
			angle += (2 * M_PI);
		if (angle > 2 * M_PI)
			angle -= 2 * M_PI;
	}
	return (angle);
}

double	calc_distance(double x, double y, double xfinal, double yfinal)
{
	double	distance;

	if (x < 0 || y < 0 || xfinal < 0 || yfinal < 0)
		return (-1);
	distance = sqrt(((xfinal - x) * (xfinal - x))
			+ ((yfinal - y) * (yfinal - y)));
	return (distance);
}
