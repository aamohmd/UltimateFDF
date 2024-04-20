/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:05:26 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/20 20:30:26 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

int	main(int argc, char *argv[])
{
	t_meta	meta;

	if (argc == 2)
	{
    	meta.mlx = mlx_init();
    	if (!meta.mlx)
        	return (1);
		meta.win = mlx_new_window(meta.mlx, WINX, WINY, "Dammmnnnn");
		check_map(&(meta.map), argv[1]);
		draw_map(&meta);
		mlx_loop(meta.mlx);
    	free(meta.mlx);
	}
}
