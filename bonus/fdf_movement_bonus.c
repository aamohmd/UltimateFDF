/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_movement_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:00:47 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/30 16:12:19 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

void	rotate_translate(t_meta *meta, int key)
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
}

void	zoom(t_meta *meta, int key)
{
	if (meta->zoom + meta->extra_zoom == 1 && key == 78)
		return ;
	if (key == 69)
		meta->extra_zoom += 1;
	else if (key == 78)
		meta->extra_zoom -= 1;
	else if (key == 49)
	{
		if (meta->mode == 2)
			meta->mode = 0;
		else if (meta->mode < 2)
			meta->mode++;
	}
}

void	projections(t_meta *meta, int key)
{
	if (key == 126 || key == 125 || key == 123 || key == 124)
	{
		meta->tetha = 0;
		if (key == 126)
		{
			meta->gamma = 0;
			meta->alpha = 0;
		}
		else if (key == 125)
		{
			meta->gamma = atan(1);
			meta->alpha = atan(sqrt(2));
		}
		else if (key == 123)
		{
			meta->gamma = M_PI / 2;
			meta->alpha = M_PI / 2;
		}
		else if (key == 124)
		{
			meta->alpha = M_PI / 2;
			meta->gamma = 0;
		}
	}
}

int	key_press(int key, t_meta *meta)
{
	if (key == 53)
	{
		mlx_destroy_window(meta->mlx, meta->win);
		exit(0);
	}
	projections(meta, key);
	crazy_mode(meta, key);
	rotate_translate(meta, key);
	zoom(meta, key);
	mlx_destroy_image(meta->mlx, meta->data.img);
	mlx_clear_window(meta->mlx, meta->win);
	draw_map(meta);
	return (0);
}
