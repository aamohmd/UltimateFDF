/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:59:45 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/20 21:33:43 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define WINX 1920	
# define WINY 1080

# define DEFAULT_COLOR	0xFFFFFF
# define RED			0xe84309
# define BLEU			0x00aaff
# define YELLOW			0xf1c40f
# define ORANGE			0xe67e22 

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
	int	x_next;
	int	y_next;
	int	a_x_start;
	int	a_y_start;
	int	b_x_start;
	int	b_y_start;
	int	dx;
	int dy;
	float sx;
	float sy;
	float err;
	int	color;
}				t_meta;

#endif