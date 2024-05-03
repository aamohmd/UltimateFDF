/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:05:26 by aamohame          #+#    #+#             */
/*   Updated: 2024/05/02 15:43:17 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

int	close_window(t_meta *meta)
{
	mlx_destroy_window(meta->mlx, meta->win);
	exit(0);
	return (0);
}

void	initial(t_meta *meta)
{
	meta->x_translate = 0;
	meta->y_translate = 0;
	meta->extra_zoom = 0;
	meta->gamma = atan(1);
	meta->tetha = 0;
	meta->alpha = atan(sqrt(2));
	meta->extra_zoom = 0;
	meta->color_mode = 'd';
	meta->map.zmin = 0;
	meta->map.zmax = 0;
	meta->mode = 0;
}

int	main(int argc, char *argv[])
{
	t_meta	meta;
	void	*img;
	int		img_width;
	int		img_height;

	if (argc == 2)
	{
		meta.mlx = mlx_init();
		if (!meta.mlx)
			return (1);
		meta.win = mlx_new_window(meta.mlx, WINX, WINY, "UltimateFDF");
		initial(&meta);
		img_width = WINX;
		img_height = WINY;
		check_map(&(meta.map), argv[1]);
		get_perfect_zoom(&meta);
		draw_map(&meta);
		img = mlx_xpm_file_to_image(meta.mlx, "bonus/start.xpm", &img_width,
				&img_height);
		mlx_put_image_to_window(meta.mlx, meta.win, img, 0, 0);
		mlx_key_hook(meta.win, key_press, &meta);
		mlx_hook(meta.win, 17, 0, close_window, &meta);
		mlx_loop(meta.mlx);
	}
}
