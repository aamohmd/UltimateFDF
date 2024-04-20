/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:17 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/20 21:29:50 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

void intToRGB(int color, int *r, int *g, int *b)
{
    *r = (color >> 16) & 0xFF;
    *g = (color >> 8) & 0xFF;
    *b = color & 0xFF;
}

int RGBToInt(int r, int g, int b)
{
    return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

float fraction(t_meta *meta, char c)
{
    if (c == 'x' && meta->a_x != meta->b_x_start)
        return (float)(meta->a_x - meta->a_x_start) / (meta->b_x_start - meta->a_x_start);
    else if (c == 'y' && meta->a_y != meta->b_y_start)
        return (float)(meta->a_y - meta->a_y_start) / (meta->b_y_start - meta->a_y_start);
    return 0;
}

void gradient(t_meta *meta, int color_a, int color_b)
{
    int dx;
    int dy;
    float fraction_result;
	int r_a;
	int g_a;
	int b_a;
	int r_b;
	int g_b;
	int b_b;
	int r;
	int g;
	int b;

	dx = abs(meta->b_x_start - meta->a_x_start);
	dy = abs(meta->b_y_start - meta->a_y_start);
    if (dx >= dy)
        fraction_result = fraction(meta, 'x');
    else
        fraction_result = fraction(meta, 'y');
	intToRGB(color_a, &r_a, &g_a, &b_a);
    intToRGB(color_b, &r_b, &g_b, &b_b);
	r = r_a + fraction_result * (r_b - r_a);
    g = g_a + fraction_result * (g_b - g_a);
    b = b_a + fraction_result * (b_b - b_a);
    meta->color = RGBToInt(r, g, b);
}

void    isometric(t_point *point, t_meta *meta)
{
    int previous_x;
    int previous_y;

	point->x *= meta->zoom;
	point->y *= meta->zoom;
	point->z *= meta->zoom;
    previous_x = point->x;
    previous_y = point->y;
    point->x = (previous_x - previous_y) * cos(0.6);
    point->y = ((previous_x + previous_y) * sin(0.6)) - point->z;
	// point->x += WINX / 2;
	// point->y += WINY / 2;
	point->x += 500;
	point->y -= 250;
}

void	convert_to_isometric(t_meta *meta)
{
	int x, y;

	x = 0;
	while (x < meta->map.num_rows)
	{
		y = 0;
		while (meta->map.points[x][y].flag != 1)
		{
			isometric(&(meta->map.points[x][y]), meta);
			y++;
		}
		x++;
	}
}

void	put_pixel(int x, int y, t_meta *meta, int color)
{
	mlx_pixel_put(meta->mlx, meta->win, x, y, color);
}

void	draw_line(t_meta *meta, int color_a, int color_b)
{
	float e2;

	while (1)
	{
		gradient(meta, color_a, color_b);
		mlx_pixel_put(meta->mlx, meta->win, meta->a_x, meta->a_y, meta->color);
		if (meta->a_x == meta->b_x && meta->a_y == meta->b_y)
			break;
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

void draw_map(t_meta * meta)
{
	int x;
	int y;

	meta->zoom = 7;
	convert_to_isometric(meta);
	y = 0;
	while (y < meta->map.num_rows)
	{
		x = 0;
		while (meta->map.points[y][x].flag != 1)
		{
			if (y < meta->map.num_rows - 1)
				bresenham_algo(&meta->map.points[y][x], &meta->map.points[y + 1][x], meta);
			if (meta->map.points[y][x + 1].flag != 1)
				bresenham_algo(&meta->map.points[y][x], &meta->map.points[y][x + 1], meta);
			x++;
		}
		y++;
	}
}
