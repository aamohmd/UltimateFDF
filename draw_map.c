/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:17 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/19 19:51:28 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

int	isometric(int x, int y, int z, char c)
{
	int	tmp;
	int	result;

	tmp = x;
	if (c == 'x')
		result = (tmp - y) * cos(0.523599);
	else
		result = (tmp + y) * sin(0.523599) - z;
	return (result);
}

void	convert_to_isometric(t_meta *meta)
{
	int x, y;
	int iso_x, iso_y;
	x = 0;
	while (x < meta->map.num_rows)
	{
		y = 0;
		while (meta->map.points[x][y].flag != 1)
		{
			iso_x = isometric(meta->map.points[x][y].x,
					meta->map.points[x][y].y, meta->map.points[x][y].z, 'x');
			iso_y = isometric(meta->map.points[x][y].x,
					meta->map.points[x][y].y, meta->map.points[x][y].z, 'y');
			meta->map.points[x][y].x = iso_x;
			meta->map.points[x][y].y = iso_y;
			y++;
		}
		x++;
	}
}

void	put_pixel(int x, int y, t_meta *meta, int color)
{
	mlx_pixel_put(meta->mlx, meta->win, x, y, color);
}

// void	slope_less_than_one(int dx, int dy, t_meta *meta, int color)
// {
// 	int	p;
// 	int	i;

// 	i = 0;
// 	p = 2 * abs(dy) - abs(dx);
// 	while (i < abs(dx))
// 	{
// 		if (dx > 0)
// 			meta->a_x += 1;
// 		else
// 			meta->a_x -= 1;
// 		if (p < 0)
// 			p = p + 2 * abs(dy);
// 		else
// 		{
// 			if (dy > 0)
// 				meta->a_y += 1;
// 			else
// 				meta->a_y -= 1;
// 			p = p + 2 * abs(dy) - 2 * abs(dx);
// 		}
// 		put_pixel(meta->a_x, meta->a_y, meta, color);
// 		i++;
// 	}
// }

// void	slope_bigger_than_one(int dx, int dy, t_meta *meta, int color)
// {
// 	int	p;
// 	int	i;

// 	i = 0;
// 	p = 2 * dx - dy;
// 	put_pixel(meta->a_x, meta->a_y, meta, color);
// 	while (i < dy)
// 	{
// 		meta->a_y += 1;
// 		if (p < 0)
// 			p = p + 2 * dx;
// 		else
// 		{
// 			meta->a_x += 1;
// 			p = p + 2 * dx - 2 * dy;
// 		}
// 		put_pixel(meta->a_x, meta->a_y, meta, color);
// 		i++;
// 	}
// }

void	draw_line(t_meta *meta)
{
	float dx = abs(meta->b_x - meta->a_x);
	float dy = abs(meta->b_y - meta->a_y);
	float sx = (meta->a_x < meta->b_x) ? 1 : -1;
	float sy = (meta->a_y < meta->b_y) ? 1 : -1;
	float err = (dx > dy ? dx : -dy) / 2;
	float e2;
	while (1)
	{
		mlx_pixel_put(meta->mlx, meta->win, meta->a_x, meta->a_y, 0xffffff);
		if (meta->a_x == meta->b_x && meta->a_y == meta->b_y)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			meta->a_x += sx;
		}
		else if (e2 < dy)
		{
			err += dx;
			meta->a_y += sy;
		}
	}
}

void bresenham_algo(t_point * a, t_point * b, t_meta * meta)
{
	// int dx;
	// int dy;

	meta->zoom = 35;
	meta->a_x = a->x;
	meta->b_x = b->x;
	meta->a_y = a->y;
	meta->b_y = b->y;
	meta->a_x *= meta->zoom;
	meta->b_x *= meta->zoom;
	meta->a_y *= meta->zoom;
	meta->b_y *= meta->zoom;
	meta->a_x += WINX / 2;
	meta->b_x += WINX / 2;
	meta->a_y += WINY / 2;
	meta->b_y += WINY / 2;
	printf("(%d,%d) ", meta->a_x, meta->a_y);
	printf("(%d,%d)\n", meta->b_x, meta->b_y);
	// meta->x_next = (a->num_columns * meta->zoom) / 2;
	// meta->y_next = (meta->map.num_rows * meta->zoom) / 2;
	// dx = meta->b_x - meta->a_x;
	// dy = meta->b_y - meta->a_y;
	// draw_line(meta);
	// if (abs(dx) > abs(dy))
	// 	slope_less_than_one(dx, dy, meta, a->color);
	// else
	// 	slope_bigger_than_one(dx, dy, meta, a->color);
}

void draw_map(t_meta * meta)
{
	int x;
	int y;

	convert_to_isometric(meta);
	y = 0;
	while (y < meta->map.num_rows)
	{
		x = 0;
		while (meta->map.points[y][x].flag != 1)
		{
			// printf("(%d,%d) ", meta->map.points[y][x].y,
				// meta->map.points[y][x].x);
			if (meta->map.points[y][x + 1].flag != 1)
				bresenham_algo(&meta->map.points[y][x], &meta->map.points[y][x + 1], meta);
			if (y < meta->map.num_rows - 1)
				bresenham_algo(&meta->map.points[y][x], &meta->map.points[y + 1][x], meta);
			x++;
		}
		y++;
	}
}
