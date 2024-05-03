/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:41:56 by aamohame          #+#    #+#             */
/*   Updated: 2024/05/02 16:16:09 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

int	loop(t_meta *meta)
{
	long	i;

	i = 0;
	if (!meta->is_looping)
		return (0);
	while (i < 2147483647 / 256)
		i++;
	meta->gamma += 0.1;
	meta->alpha += 0.1;
	meta->tetha += 0.1;
	draw_map(meta);
	return (0);
}

void	crazy_mode(t_meta *meta, int key)
{
	if (key == 18)
		meta->color_mode = 'g';
	else if (key == 19)
		meta->color_mode = 'w';
	else if (key == 20)
	{
		if (meta->is_looping)
			meta->is_looping = 0;
		else
		{
			meta->color_mode = 'r';
			meta->gamma = atan(1);
			meta->alpha = atan(sqrt(2));
			meta->tetha = 0;
			mlx_loop_hook(meta->mlx, loop, meta);
			meta->is_looping = 1;
		}
	}
}

void	triangles(t_meta *meta, int x, int y)
{
	if (y < meta->map.num_rows - 1 && meta->map.points[y + 1][x + 1].flag != 1
		&& meta->mode > 0)
		bre(&meta->map.points[y][x], &meta->map.points[y + 1][x + 1], meta);
	if (meta->map.points[y][x + 1].flag != 1 && y < meta->map.num_rows - 1
		&& meta->mode > 1)
		bre(&meta->map.points[y + 1][x], &meta->map.points[y][x + 1], meta);
}

void	put_pixel_image(int x, int y, t_meta *meta, int color)
{
	char	*dst;

	dst = meta->data.addr + (y * meta->data.line_length + x
			* (meta->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	side_bar(t_meta *meta)
{
	int	color;
	int	x;
	int	y;

	color = mlx_get_color_value(meta->mlx, 0x5001161B);
	meta->data.img = mlx_new_image(meta->mlx, 500, 1920);
	meta->data.addr = mlx_get_data_addr(meta->data.img,
			&meta->data.bits_per_pixel, &meta->data.line_length,
			&meta->data.endian);
	y = 0;
	while (y < 1920)
	{
		x = 0;
		while (x < 500)
		{
			put_pixel_image(x, y, meta, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(meta->mlx, meta->win, meta->data.img, 0, 0);
	meta->data.img = mlx_xpm_file_to_image(meta->mlx, "bonus/help.xpm",
			&meta->img_width, &meta->img_height);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->data.img, 0, 0);
}
