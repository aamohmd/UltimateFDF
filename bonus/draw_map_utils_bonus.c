/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:07:35 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/25 16:13:21 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

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

void	put_pixel(int x, int y, t_meta *meta, int color)
{
	char	*dst;

	dst = meta->data.addr + (y * meta->data.line_length + x
			* (meta->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_meta *meta, int color_a, int color_b)
{
	float	e2;

	while (1)
	{
		gradient(meta, color_a, color_b);
		if (meta->a_x >= 470 && meta->a_x < WINX && meta->a_y >= 0
			&& meta->a_y < WINY)
			put_pixel(meta->a_x, meta->a_y, meta, meta->color);
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
