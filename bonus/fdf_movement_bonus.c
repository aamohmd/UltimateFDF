/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_movement_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:00:47 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/25 12:32:12 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

void	rotate_translate_zoom(t_meta *meta, int key)
{
	if (key == 91)
		meta->gamma += 0.1;
	else if (key == 87)
		meta->gamma -= 0.1;
	else if (key == 88)
		meta->tetha += 0.1;
	else if (key == 86)
		meta->tetha -= 0.1;
	else if (key == 89)
		meta->alpha += 0.1;
	else if (key == 92)
		meta->alpha -= 0.1;
	else if (key == 13)
		meta->y_translate -= 15;
	else if (key == 0)
		meta->x_translate -= 15;
	else if (key == 1)
		meta->y_translate += 15;
	else if (key == 2)
		meta->x_translate += 15;
	else if (key == 69)
		meta->extra_zoom += meta->zoom / 10;
	else if (key == 78)
		meta->extra_zoom -= meta->zoom / 10;
}

int	key_press(int key, t_meta *meta)
{
    if (key == 53)
    {
        mlx_destroy_window(meta->mlx, meta->win);
        exit(0);
    }
	else if (key == 126 || key == 125)
	{
		meta->x_translate = 0;
		meta->y_translate = 0;
		meta->extra_zoom = 0;
		meta->gamma = 0;
		meta->tetha = 0;
		meta->alpha = 0;
		if (key == 126)
			meta->projection = 'p';
		else
			meta->projection = 'i';
	}

	rotate_translate_zoom(meta, key);
	mlx_clear_window(meta->mlx, meta->win);
	draw_map(meta);
    return (0);
}

void	rotate_z(t_meta *meta)
{
	int	tmp;

	tmp = meta->a_x;
	meta->a_x = tmp * cos(meta->gamma) - meta->a_y * sin(meta->gamma);
	meta->a_y = tmp * sin(meta->gamma) + meta->a_y * cos(meta->gamma);
	tmp = meta->b_x;
	meta->b_x = tmp * cos(meta->gamma) - meta->b_y * sin(meta->gamma);
	meta->b_y = tmp * sin(meta->gamma) + meta->b_y * cos(meta->gamma);
}

void	rotate_y(t_meta *meta)
{
	int	tmp;

	tmp = meta->a_x;
	meta->a_x = tmp * cos(meta->tetha) + meta->a_z * sin(meta->tetha);
	meta->a_z = meta->a_z * cos(meta->tetha) - tmp * sin(meta->tetha);
	tmp = meta->b_x;
	meta->b_x = tmp * cos(meta->tetha) + meta->b_z * sin(meta->tetha);
	meta->b_z = meta->b_z * cos(meta->tetha) - tmp * sin(meta->tetha);
}

void	rotate_x(t_meta *meta)
{
	int tmp;

	tmp = meta->a_y;
	meta->a_y = tmp * cos(meta->alpha) - meta->a_z * sin(meta->alpha);
	meta->a_z = tmp * sin(meta->alpha) + meta->a_z * cos(meta->alpha);
	tmp = meta->b_y;
	meta->b_y = tmp * cos(meta->alpha) - meta->b_z * sin(meta->alpha);
	meta->b_z = tmp * sin(meta->alpha) + meta->b_z * cos(meta->alpha);
}