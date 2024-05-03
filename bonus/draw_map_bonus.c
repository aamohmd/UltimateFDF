/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:17 by aamohame          #+#    #+#             */
/*   Updated: 2024/05/02 16:14:35 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

void	initial_image(t_meta *meta)
{
	meta->img_width = WINX;
	meta->img_height = WINY;
	meta->data.img = mlx_new_image(meta->mlx, WINX, WINY);
	meta->data.img = mlx_xpm_file_to_image(meta->mlx, "bonus/background.xpm",
			&meta->img_width, &meta->img_height);
	meta->data.addr = mlx_get_data_addr(meta->data.img,
			&meta->data.bits_per_pixel, &meta->data.line_length,
			&meta->data.endian);
}

int	color_generator(void)
{
	int	color;

	color = 0;
	color = rand() % 0xFFFFFF;
	return (color);
}

void	color_scheme(t_meta *meta, int x, int y, int part)
{
	float	fraction;

	if (meta->color_mode == 'g')
	{
		if (meta->map.points[y][x].z == 0)
			meta->map.points[y][x].color = GROUND_COLOR;
		else if (meta->map.points[y][x].z >= meta->map.zmin
			&& meta->map.points[y][x].z < 0 && meta->map.zmin != 0)
			meta->map.points[y][x].color = BOTTOM_COLOR;
		else if (meta->map.points[y][x].z <= meta->map.zmax
			&& meta->map.points[y][x].z > part)
			meta->map.points[y][x].color = TOP_COLOR;
		else if (meta->map.points[y][x].z <= part
			&& meta->map.points[y][x].z > 0)
			meta->map.points[y][x].color = DEFAULT_COLOR;
	}
	else if (meta->color_mode == 'r')
	{
		fraction = (float)(meta->map.points[y][x].z - meta->map.zmin)
			/ meta->map.zmax - meta->map.zmin;
		meta->map.points[y][x].color = meta->grad.colora + fraction
			* (meta->grad.colorb - meta->grad.colora);
	}
	else if (meta->color_mode == 'w')
		meta->map.points[y][x].color = DEFAULT;
}

void	colorize_map(t_meta *meta)
{
	int	x;
	int	y;
	int	part;

	part = meta->map.zmax / 2;
	meta->grad.colora = color_generator();
	meta->grad.colorb = color_generator();
	y = 0;
	while (y < meta->map.num_rows)
	{
		x = 0;
		while (meta->map.points[y][x].flag != 1)
		{
			color_scheme(meta, x, y, part);
			x++;
		}
		y++;
	}
}

void	draw_map(t_meta *meta)
{
	int	x;
	int	y;

	y = 0;
	colorize_map(meta);
	initial_image(meta);
	while (y < meta->map.num_rows)
	{
		x = 0;
		while (meta->map.points[y][x].flag != 1)
		{
			if (y < meta->map.num_rows - 1)
				bre(&meta->map.points[y][x], &meta->map.points[y + 1][x], meta);
			if (meta->map.points[y][x + 1].flag != 1)
				bre(&meta->map.points[y][x], &meta->map.points[y][x + 1], meta);
			triangles(meta, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(meta->mlx, meta->win, meta->data.img, 0, 0);
	side_bar(meta);
}
