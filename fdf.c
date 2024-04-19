/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:05:26 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/19 19:50:17 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

int	main(int argc, char *argv[])
{
	t_meta	meta;
	// int		i;
	// int		j;

	if (argc == 2)
	{
    	meta.mlx = mlx_init();
    	if (!meta.mlx)
        	return (1);
		// meta.win = mlx_new_window(meta.mlx, WINX, WINY, "Dammmnnnn");
		check_map(&(meta.map), argv[1]);
		draw_map(&meta);
		// i = 0;
		// while (i < meta.map.num_rows)
		// {
		// 	j = 0;
		// 	while (meta.map.points[i][j].flag != 1)
		// 	{
		// 		printf("%d ", meta.map.points[i][j].z);
		// 		j++;
		// 	}
		// 	printf("\n");
		// 	i++;
		// }
		// mlx_loop(meta.mlx);
    	// free(meta.mlx);
	}
}
