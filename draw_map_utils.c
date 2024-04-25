/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:07:35 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/21 19:44:37 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

void	intToRGB(int color, int *r, int *g, int *b)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

float	fraction(t_meta *meta, char c)
{
	if (c == 'x' && meta->a_x != meta->b_x_start)
		return (float)(meta->a_x - meta->a_x_start) / (meta->b_x_start
			- meta->a_x_start);
	else if (c == 'y' && meta->a_y != meta->b_y_start)
		return (float)(meta->a_y - meta->a_y_start) / (meta->b_y_start
			- meta->a_y_start);
	return (0);
}

void	gradient(t_meta *meta, int color_a, int color_b)
{
	int		dx;
	int		dy;
	float	fraction_result;
	int		r_a;
	int		g_a;
	int		b_a;
	int		r_b;
	int		g_b;
	int		b_b;
	int		r;
	int		g;
	int		b;

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
	meta->color = ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

void	isometric(t_point *point, t_meta *meta)
{
	int	previous_x;
	int	previous_y;

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
