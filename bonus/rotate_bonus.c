/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:43:23 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/28 19:43:42 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

void	rotate_z(t_meta *meta)
{
	double	tmp;

	tmp = meta->a_x;
	meta->a_x = tmp * cos(meta->gamma) - meta->a_y * sin(meta->gamma);
	meta->a_y = tmp * sin(meta->gamma) + meta->a_y * cos(meta->gamma);
	tmp = meta->b_x;
	meta->b_x = tmp * cos(meta->gamma) - meta->b_y * sin(meta->gamma);
	meta->b_y = tmp * sin(meta->gamma) + meta->b_y * cos(meta->gamma);
}

void	rotate_y(t_meta *meta)
{
	double	tmp;

	tmp = meta->a_x;
	meta->a_x = tmp * cos(meta->tetha) + meta->a_z * sin(meta->tetha);
	meta->a_z = meta->a_z * cos(meta->tetha) - tmp * sin(meta->tetha);
	tmp = meta->b_x;
	meta->b_x = tmp * cos(meta->tetha) + meta->b_z * sin(meta->tetha);
	meta->b_z = meta->b_z * cos(meta->tetha) - tmp * sin(meta->tetha);
}

void	rotate_x(t_meta *meta)
{
	double	tmp;

	tmp = meta->a_y;
	meta->a_y = tmp * cos(meta->alpha) - meta->a_z * sin(meta->alpha);
	meta->a_z = tmp * sin(meta->alpha) + meta->a_z * cos(meta->alpha);
	tmp = meta->b_y;
	meta->b_y = tmp * cos(meta->alpha) - meta->b_z * sin(meta->alpha);
	meta->b_z = tmp * sin(meta->alpha) + meta->b_z * cos(meta->alpha);
}
