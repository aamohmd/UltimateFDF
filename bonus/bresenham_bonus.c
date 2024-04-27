/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:10:55 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/25 20:55:03 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

void	assign_points(t_point *a, t_point *b, t_meta *meta)
{
	meta->a_x = a->x - (meta->map.points[0][0].num_columns) / 2;
	meta->b_x = b->x - (meta->map.points[0][0].num_columns) / 2;
	meta->a_y = a->y - (meta->map.num_rows) / 2;
	meta->b_y = b->y - (meta->map.num_rows) / 2;
	meta->a_x *= (meta->zoom + meta->extra_zoom);
	meta->a_y *= (meta->zoom + meta->extra_zoom);
	meta->b_x *= (meta->zoom + meta->extra_zoom);
	meta->b_y *= (meta->zoom + meta->extra_zoom);
	meta->a_z = a->z * (meta->zoom + meta->extra_zoom);
	meta->b_z = b->z * (meta->zoom + meta->extra_zoom);
}

void	rotate(t_meta *meta)
{
	rotate_z(meta);
	rotate_y(meta);
	rotate_x(meta);
	meta->a_x += (WINX / 2) + meta->x_translate + 235;
	meta->a_y += (WINY / 2) + meta->y_translate;
	meta->b_x += (WINX / 2) + meta->x_translate + 235;
	meta->b_y += (WINY / 2) + meta->y_translate;
}

void	assign_start(t_meta *meta)
{
	meta->a_x_start = meta->a_x;
	meta->a_y_start = meta->a_y;
	meta->b_x_start = meta->b_x;
	meta->b_y_start = meta->b_y;
}

void	bre(t_point *a, t_point *b, t_meta *meta)
{
	assign_points(a, b, meta);
	rotate(meta);
	assign_start(meta);
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
