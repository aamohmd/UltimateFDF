/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:17 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/25 15:41:13 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

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
		if (meta->a_x >= 470 && meta->a_x < WINX && meta->a_y >= 0 && meta->a_y < WINY)
			put_pixel(meta->a_x, meta->a_y, meta, meta->color);
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

void	assign_points(t_point *a, t_point *b, t_meta *meta)
{
	meta->a_x = a->x;
	meta->b_x = b->x;
	meta->a_y = a->y;
	meta->b_y = b->y;
	meta->a_z = a->z * (meta->zoom + meta->extra_zoom);
	meta->b_z = b->z * (meta->zoom + meta->extra_zoom);
}

void isometric(t_point *a, t_point *b, t_meta *meta)
{
	int	tmp;

	tmp = meta->a_x;
	meta->a_x = (tmp - meta->a_y) * cos(M_PI / 6) * (meta->zoom + meta->extra_zoom);
	meta->a_y = (((tmp + meta->a_y) * sin(M_PI / 6)) - a->z) * (meta->zoom + meta->extra_zoom);
	tmp = meta->b_x;
	meta->b_x = (tmp - meta->b_y) * cos(M_PI / 6) * (meta->zoom + meta->extra_zoom);
	meta->b_y = (((tmp + meta->b_y) * sin(M_PI / 6)) - b->z) * (meta->zoom + meta->extra_zoom);
	meta->a_z = a->z * (meta->zoom + meta->extra_zoom);
	meta->b_z = b->z * (meta->zoom + meta->extra_zoom);
}

void front_view(t_meta *meta)
{
	meta->a_x *= (meta->zoom + meta->extra_zoom);
	meta->a_y *= (meta->zoom + meta->extra_zoom);
	meta->b_x *= (meta->zoom + meta->extra_zoom);
	meta->b_y *= (meta->zoom + meta->extra_zoom);
}

void rotate(t_meta *meta)
{
	rotate_z(meta);
	rotate_y(meta);
	rotate_x(meta);
}

void	bre(t_point *a, t_point *b, t_meta *meta)
{
	assign_points(a, b, meta);
	if (meta->projection == 'i')
		isometric(a, b, meta);
	else
		front_view(meta);
	meta->a_x -= ((meta->map.points[0][0].num_columns * (meta->zoom + meta->extra_zoom)) / 2);
	meta->a_y -= ((meta->map.num_rows * (meta->zoom + meta->extra_zoom)) / 2);
	meta->b_x -= ((meta->map.points[0][0].num_columns * (meta->zoom + meta->extra_zoom)) / 2);
	meta->b_y -= ((meta->map.num_rows * (meta->zoom + meta->extra_zoom)) / 2);
	rotate(meta);
	meta->a_x += (WINX / 2) + meta->x_translate + 235;
	meta->a_y += (WINY / 2) + meta->y_translate;
	meta->b_x += (WINX / 2) + meta->x_translate + 235;
	meta->b_y += (WINY / 2) + meta->y_translate;
	meta->a_x_start = meta->a_x;
	meta->a_y_start = meta->a_y;
	meta->b_x_start = meta->b_x;
	meta->b_y_start = meta->b_y;
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
	int	img_width;
	int	img_height;

	img_width = WINX;
	img_height = WINY;
	meta->data.img = mlx_new_image(meta->mlx, WINX, WINY);
	meta->data.img = mlx_xpm_file_to_image(meta->mlx, "bonus/background.xpm", &img_width, &img_height);
    meta->data.addr = mlx_get_data_addr(meta->data.img, &meta->data.bits_per_pixel, &meta->data.line_length, &meta->data.endian);
	y = 0;
	while (y < meta->map.num_rows)
	{
		x = 0;
		while (meta->map.points[y][x].flag != 1)
		{
			if (y < meta->map.num_rows - 1)
				bre(&meta->map.points[y][x], &meta->map.points[y + 1][x], meta);
			if (meta->map.points[y][x + 1].flag != 1)
				bre(&meta->map.points[y][x], &meta->map.points[y][x + 1], meta);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(meta->mlx, meta->win, meta->data.img, 0, 0);
}
