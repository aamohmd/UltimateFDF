/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:05:26 by aamohame          #+#    #+#             */
/*   Updated: 2024/05/06 16:34:24 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

int	key_press(int key, t_meta *meta)
{
	if (key == 53)
	{
		mlx_destroy_window(meta->mlx, meta->win);
		exit(0);
	}
	return (0);
}

void	free_map(t_map map)
{
	int	y;

	y = 0;
	while (y < map.num_rows)
	{
		free(map.points[y]);
		y++;
	}
	free(map.points);
}

int	close_window(t_meta *meta)
{
	mlx_destroy_window(meta->mlx, meta->win);
	free_map(meta->map);
	exit(0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_meta	meta;

	if (argc == 2)
	{
		meta.mlx = mlx_init();
		if (!meta.mlx)
			return (1);
		meta.win = mlx_new_window(meta.mlx, WINX, WINY, "UltimateFDF");
		mlx_hook(meta.win, 17, 0, close_window, &meta);
		mlx_hook(meta.win, 2, 0, key_press, &meta);
		check_map(&(meta.map), argv[1]);
		draw_map(&meta);
		mlx_loop(meta.mlx);
	}
}
