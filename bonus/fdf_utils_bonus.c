/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:29:34 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/25 15:49:10 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

void	get_perfect_zoom(t_meta *meta)
{
	int	surface;

	surface = meta->map.num_rows * meta->map.points[0][0].num_columns;
	if (surface == 209 || surface == 189)
		meta->zoom = 20;
	else if (surface == 9)
		meta->zoom = 60;
	else if (surface >= 80 && surface < 189)
		meta->zoom = 25;
	else if (surface >= 400 && surface < 1000)
		meta->zoom = 15;
	else if (surface >= 25000 && surface < 40000)
		meta->zoom = 3;
	else if (surface == 250000 && surface == 129213)
		meta->zoom = 2;
	else if (surface >= 40000 && surface < 100000)
		meta->zoom = 4;
	else if (surface == 70950)
		meta->zoom = 1;
	else if (surface >= 2000 && surface < 4000)
		meta->zoom = 10;
	else if (surface >= 10000 && surface < 25000)
		meta->zoom = 4;
	else
		meta->zoom = 2;
}
