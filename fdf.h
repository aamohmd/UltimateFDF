/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:05:55 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/15 19:52:41 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "lib/UltimateGNL/get_next_line.h"
# include "lib/UltimateLibft/libft.h"
# include <stdio.h>
# include <fcntl.h>

# define WINX 1920	
# define WINY 1080

# define DEFAULT_COLOR		JAFFA
# define BOTTOM_COLOR		AZUL
# define TOP_COLOR			BRICK_RED
# define GROUND_COLOR		SAFFRON
# define BACK_COLOR			0x151515
# define MENU_COLOR			0x202020
# define TEXT_COLOR			0xEAEAEA	
# define NUMBER_COLOR		0xF3AF3D

typedef struct s_vars
{
    
} 				t_vars;

typedef struct s_point
{
    int 	x;
    int 	y;
    int 	z;
	int		color;
} 				t_point;

typedef struct s_map
{
	t_point	**points;
	int		num_columns;
	int		num_rows;
}				t_map;

typedef struct s_meta
{
	t_map	*map;
	
}				t_meta;

int valid_point(char *value);

#endif