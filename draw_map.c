/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:17 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/25 14:11:02 by aamohame         ###   ########.fr       */
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
	char	*dst;

    dst = meta->data.addr + (y * meta->data.line_length + x * (meta->data.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	draw_line(t_meta *meta, int color_a, int color_b)
{
	float	e2;

	while (1)
	{
		gradient(meta, color_a, color_b);
		put_pixel(meta->a_x + ((WINX / 2) - meta->x_min) - (meta->x_max - meta->x_min) / 2, meta->a_y + ((WINY / 2) - meta->y_min) - (meta->y_max - meta->y_min) / 2, meta, meta->color);
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
	meta->dx = (int)fabsf((float)meta->b_x - (float)meta->a_x);
	meta->dy = (int)fabsf((float)meta->b_y - (float)meta->a_y);
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
	if (surface == 209 || surface == 189)
		meta->zoom = 20;
	else if (surface == 9)
		meta->zoom = 60;
	else if (surface >= 80 && surface < 189)
		meta->zoom = 25;
	else if (surface >= 400 && surface < 1000)
		meta->zoom = 15;
	else if (surface >= 25000 && surface < 40000)
		meta->zoom = 3;
	else if (surface == 250000 && surface == 129213)
		meta->zoom = 2;
	else if (surface >= 40000 && surface < 100000)
		meta->zoom = 4;
	else if (surface == 70950)
		meta->zoom = 1;
	else if (surface >= 2000 && surface < 4000)
		meta->zoom = 10;
	else if (surface >= 10000 && surface < 25000)
		meta->zoom = 4;
	else
		meta->zoom = 2;
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
