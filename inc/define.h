/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:59:45 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/19 14:44:15 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define WINX 1920	
# define WINY 1080

# define DEFAULT_COLOR	0xFFFFFF
# define RED			0xff0000

typedef struct s_point
{
    int 	x;
    int 	y;
    int 	z;
	int		color;
	int		flag;
	int		num_columns;
} 				t_point;

typedef struct s_map
{
	t_point	**points;
	int		num_columns;
	int		num_rows;
}				t_map;

typedef struct s_meta
{
	t_map	map;
	void	*mlx;
	void 	*win;
	int		zoom;
	int	a_x;
	int	b_x;
	int	a_y;
	int	b_y;
	int	a_z;
	int	b_z;
	int	x_next;
	int	y_next;
}				t_meta;

#endif