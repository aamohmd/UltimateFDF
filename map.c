/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:56:14 by aamohame          #+#    #+#             */
/*   Updated: 2024/05/02 16:13:51 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

int	ft_file_name_error(char *filename)
{
	size_t	filename_len;

	filename_len = ft_strlen(filename);
	if (filename_len < 4)
		return (1);
	if (ft_strncmp(&filename[filename_len - 4], ".fdf", 4))
		return (1);
	return (0);
}

int	map_dimensions(char *filename, t_map *map)
{
	int		fd;
	char	*line;

	map->num_rows = 0;
	if (ft_file_name_error(filename) == 1)
		terminate("wrong file name");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		terminate("can't open file");
	while (get_next_line_fdf(fd, &line) == 0)
	{
		free(line);
		map->num_rows++;
	}
	close(fd);
	return (0);
}

void	load_points(t_map *map, char *str, int y, int x)
{
	char	*color;

	if (valid_point(str) == 1)
	{
		map->points[y][x].flag = 0;
		map->points[y][x].x = x;
		map->points[y][x].y = y;
		map->points[y][x].z = ft_atoi(str);
		map->points[y][x].num_columns = map->num_columns;
		color = ft_strchr(str, ',');
		if (color)
			map->points[y][x].color = ft_strtol(color + 1, 16);
		else
		{
			if (map->points[y][x].z < 3)
				map->points[y][x].color = BLEU;
			else if (map->points[y][x].z >= 3 && map->points[y][x].z <= 13)
				map->points[y][x].color = YELLOW;
			else if (map->points[y][x].z > 13 && map->points[y][x].z <= 25)
				map->points[y][x].color = ORANGE;
			else
				map->points[y][x].color = RED;
		}
	}
}

void	read_map(t_map *map)
{
	int	prev_num_columns;

	prev_num_columns = map->num_columns;
	map->x = 0;
	map->line = get_next_line(map->fd);
	map->parts = ft_split(map->line, ' ');
	map->num_columns = ft_strslen(map->parts);
	if (prev_num_columns != map->num_columns && map->y != 0)
		terminate("found wrong line length. Exiting.");
	map->points[map->y] = (t_point *)malloc((map->num_columns + 1)
			* sizeof(t_point));
	while (map->parts[map->x] != NULL)
	{
		if (map->parts[map->x + 1] == NULL)
			map->parts[map->x] = ft_strtrim(map->parts[map->x], "\n");
		load_points(map, map->parts[map->x], map->y, map->x);
		map->x++;
	}
	map->points[map->y][map->x].flag = 1;
}

void	check_map(t_map *map, char *filename)
{
	map->y = 0;
	map->fd = open(filename, O_RDONLY);
	map_dimensions(filename, map);
	if (map->num_rows == 0)
		terminate("empty file");
	map->points = (t_point **)malloc(map->num_rows * sizeof(t_point *));
	while (map->y < map->num_rows)
	{
		read_map(map);
		if (ft_strncmp(map->line, "\n", 1) == 0 && map->y == 0)
			terminate("empty file");
		free(map->line);
		ft_strsdel(&map->parts);
		map->y++;
	}
}
