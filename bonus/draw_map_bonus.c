/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:17 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/27 10:21:33 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

void	initial_image(t_meta *meta)
{
	int	img_width;
	int	img_height;

	img_width = WINX;
	img_height = WINY;
	meta->data.img = mlx_new_image(meta->mlx, WINX, WINY);
	meta->data.img = mlx_xpm_file_to_image(meta->mlx, "bonus/background.xpm",
			&img_width, &img_height);
	meta->data.addr = mlx_get_data_addr(meta->data.img,
			&meta->data.bits_per_pixel, &meta->data.line_length,
			&meta->data.endian);
}

void	draw_map(t_meta *meta)
{
	int	x;
	int	y;

	y = 0;
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
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(meta->mlx, meta->win, meta->data.img, 0, 0);
}
