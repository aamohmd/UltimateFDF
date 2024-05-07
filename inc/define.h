/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:59:45 by aamohame          #+#    #+#             */
/*   Updated: 2024/05/04 21:03:02 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define WINX 1920
# define WINY 1080

# define DEFAULT_COLOR 0xFFFFFF
# define RED 0xe84309
# define BLEU 0x00aaff
# define YELLOW 0xf1c40f
# define ORANGE 0xe67e22

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
	int			flag;
	int			num_columns;
}				t_point;

typedef struct s_map
{
	t_point		**points;
	int			num_columns;
	int			num_rows;
	int			fd;
	char		**parts;
	char		*line;
	int			x;
	int			y;
}				t_map;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_gradient
{
	int			dx;
	int			dy;
	float		fraction_result;
	int			r_a;
	int			g_a;
	int			b_a;
	int			r_b;
	int			g_b;
	int			b_b;
	int			r;
	int			g;
	int			b;
}				t_gradient;

typedef struct s_meta
{
	t_map		map;
	t_img		data;
	t_gradient	grad;
	void		*mlx;
	void		*win;
	int			zoom;
	int			a_x;
	int			b_x;
	int			a_y;
	int			b_y;
	int			x_next;
	int			y_next;
	int			a_x_start;
	int			a_y_start;
	int			b_x_start;
	int			b_y_start;
	int			x_min;
	int			x_max;
	int			y_min;
	int			y_max;
	int			dx;
	int			dy;
	float		sx;
	float		sy;
	float		err;
	int			color;
}				t_meta;

#endif