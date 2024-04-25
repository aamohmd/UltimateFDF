/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:17 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/21 19:57:03 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

void	assign_map_limits(t_meta *meta)
{
	int	y;
	int	x;

	meta->x_min = meta->map.points[0][0].x;
	meta->x_max = meta->map.points[0][0].x;
	meta->y_min = meta->map.points[0][0].y;
	meta->y_max = meta->map.points[0][0].y;
	y = 0;
	while (y < meta->map.num_rows)
	{
		x = 0;
		while (meta->map.points[y][x].flag != 1)
		{
			if (meta->map.points[y][x].x < meta->x_min)
				meta->x_min = meta->map.points[y][x].x;
			if (meta->map.points[y][x].x > meta->x_max)
				meta->x_max = meta->map.points[y][x].x;
			if (meta->map.points[y][x].y < meta->y_min)
				meta->y_min = meta->map.points[y][x].y;
			if (meta->map.points[y][x].y > meta->y_max)
				meta->y_max = meta->map.points[y][x].y;
			x++;
		}
		y++;
	}
}

void	put_pixel(int x, int y, t_meta *meta, int color)
{
	mlx_pixel_put(meta->mlx, meta->win, x, y, color);
}

void	draw_line(t_meta *meta, int color_a, int color_b)
{
	float	e2;

	while (1)
	{
		gradient(meta, color_a, color_b);
		mlx_pixel_put(meta->mlx, meta->win, meta->a_x + ((WINX / 2) - meta->x_min) - (meta->x_max - meta->x_min) / 2, meta->a_y + ((WINY / 2) - meta->y_min) - (meta->y_max - meta->y_min) / 2, meta->color);
		if (meta->a_x == meta->b_x && meta->a_y == meta->b_y)
			break ;
		e2 = meta->err;
		if (e2 > -meta->dx)
		{
			meta->err -= meta->dy;
			meta->a_x += meta->sx;
		}
		if (e2 < meta->dy)
		{
			meta->err += meta->dx;
			meta->a_y += meta->sy;
		}
	}
}

void	bresenham_algo(t_point *a, t_point *b, t_meta *meta)
{
	meta->a_x = a->x;
	meta->b_x = b->x;
	meta->a_y = a->y;
	meta->b_y = b->y;
	meta->a_x_start = a->x;
	meta->a_y_start = a->y;
	meta->b_x_start = b->x;
	meta->b_y_start = b->y;
	meta->dx = abs(meta->b_x - meta->a_x);
	meta->dy = abs(meta->b_y - meta->a_y);
	if (meta->a_x < meta->b_x)
		meta->sx = 1;
	else
		meta->sx = -1;
	if (meta->a_y < meta->b_y)
		meta->sy = 1;
	else
		meta->sy = -1;
	if (meta->dx > meta->dy)
		meta->err = meta->dx / 2;
	else
		meta->err = -meta->dy / 2;
	draw_line(meta, a->color, b->color);
}

void	get_perfect_zoom(t_meta *meta)
{
	int	surface;

	surface = meta->map.num_rows * meta->map.points[0][0].num_columns;
	if (surface == 209)
		meta->zoom = 40;
	else if (surface == 110 || surface == 100)
		meta->zoom = 25;
	else if (surface == 400)
		meta->zoom = 15;
	else if (surface == 10100)
		meta->zoom = 5;
	else if (surface == 250000)
		meta->zoom = 2;
	else if (surface == 2550)
		meta->zoom = 10;
	else if (surface == 23200)
		meta->zoom = 4;
}

void	draw_map(t_meta *meta)
{
	int	x;
	int	y;

	get_perfect_zoom(meta);
	convert_to_isometric(meta);
	assign_map_limits(meta);
	y = 0;
	while (y < meta->map.num_rows)
	{
		x = 0;
		while (meta->map.points[y][x].flag != 1)
		{
			if (y < meta->map.num_rows - 1)
				bresenham_algo(&meta->map.points[y][x], &meta->map.points[y
					+ 1][x], meta);
			if (meta->map.points[y][x + 1].flag != 1)
				bresenham_algo(&meta->map.points[y][x], &meta->map.points[y][x
					+ 1], meta);
			x++;
		}
		y++;
	}
}
