/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:07:35 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/27 10:40:39 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

void	int_to_rgb(int color, int *r, int *g, int *b)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

float	fraction(t_meta *meta, char c)
{
	if (c == 'x' && meta->a_x != meta->b_x_start)
		return ((float)(meta->a_x - meta->a_x_start) / (meta->b_x_start
				- meta->a_x_start));
	else if (c == 'y' && meta->a_y != meta->b_y_start)
		return ((float)(meta->a_y - meta->a_y_start) / (meta->b_y_start
				- meta->a_y_start));
	return (0);
}

void	gradient(t_meta *meta, int color_a, int color_b)
{
	meta->grad.dx = (int)fabsf((float)meta->b_x_start - (float)meta->a_x_start);
	meta->grad.dy = (int)fabsf((float)meta->b_y_start - (float)meta->a_y_start);
	if (meta->grad.dx >= meta->grad.dy)
		meta->grad.fraction_result = fraction(meta, 'x');
	else
		meta->grad.fraction_result = fraction(meta, 'y');
	int_to_rgb(color_a, &meta->grad.r_a, &meta->grad.g_a, &meta->grad.b_a);
	int_to_rgb(color_b, &meta->grad.r_b, &meta->grad.g_b, &meta->grad.b_b);
	meta->grad.r = meta->grad.r_a + meta->grad.fraction_result * (meta->grad.r_b
			- meta->grad.r_a);
	meta->grad.g = meta->grad.g_a + meta->grad.fraction_result * (meta->grad.g_b
			- meta->grad.g_a);
	meta->grad.b = meta->grad.b_a + meta->grad.fraction_result * (meta->grad.b_b
			- meta->grad.b_a);
	meta->grad.r = meta->grad.r & 0xFF;
	meta->grad.r = meta->grad.r << 16;
	meta->grad.g = meta->grad.g & 0xFF;
	meta->grad.g = meta->grad.g << 8;
	meta->grad.b = meta->grad.b & 0xFF;
	meta->color = meta->grad.r | meta->grad.g | meta->grad.b;
}

void	isometric(t_point *point, t_meta *meta)
{
	int	previous_x;
	int	previous_y;

	point->x -= (meta->map.num_columns - 1) / 2;
	point->y -= (meta->map.num_rows - 1) / 2;
	point->x *= meta->zoom;
	point->y *= meta->zoom;
	point->z *= meta->zoom;
	previous_x = point->x;
	previous_y = point->y;
	point->x = (previous_x - previous_y) * cos(0.6);
	point->y = ((previous_x + previous_y) * sin(0.6)) - point->z;
	point->x += (WINX / 2);
	point->y += (WINY / 2);
}

void	convert_to_isometric(t_meta *meta)
{
	int	x;
	int	y;

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
