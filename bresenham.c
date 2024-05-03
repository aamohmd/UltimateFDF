/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:10:11 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/29 11:37:48 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

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
		if (meta->a_x >= 0 && meta->a_x < WINX && meta->a_y >= 0
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
