/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:58:46 by aamohame          #+#    #+#             */
/*   Updated: 2024/05/04 21:02:42 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

void	check_map(t_map *map, char *filename);
int		valid_point(char *value);
int		ft_strslen(char **parts);
void	ft_strsdel(char ***strs);
void	terminate(char *s);
int		get_next_line_fdf(int fd, char **line);
void	draw_map(t_meta *meta);
void	gradient(t_meta *meta, int color_a, int color_b);
void	convert_to_isometric(t_meta *meta);
void	draw_line(t_meta *meta, int color_a, int color_b);

#endif