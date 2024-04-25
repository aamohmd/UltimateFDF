/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:56:14 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/25 12:18:09 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

int	ft_file_name_error(char	*filename)
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

	map->points[y][x].flag = 0;
	map->points[y][x].x = x;
	map->points[y][x].y = y;
	map->points[y][x].z = ft_atoi(str); 
	map->points[y][x].num_columns = map->num_columns;
	color = ft_strchr(str, ',');
	if (color)
		map->points[y][x].color = strtol(color + 1, NULL, 16);
	else
	{
		if (map->points[y][x].z >= -5 && map->points[y][x].z <= 5)
			map->points[y][x].color = DEFAULT_COLOR;
		else if (map->points[y][x].z > 5 || map->points[y][x].z < -5)
			map->points[y][x].color = 0x49DDE8;
	}
}

void	check_map(t_map *map, char *filename)
{
	int		fd;
	char	**parts;
    char	*line;
	int		x;
	int		y;

	y = 0;
	fd = open(filename, O_RDONLY);
	map_dimensions(filename, map);
	map->points = (t_point **)malloc(map->num_rows * sizeof(t_point *));
	while (y < map->num_rows)
    {
		x = 0;
		line = get_next_line(fd);
		parts = ft_split(line, ' ');
		map->num_columns = ft_strslen(parts);
		map->points[y] = (t_point *)malloc((map->num_columns + 1) * sizeof(t_point));
		while (parts[x] != NULL)
		{
			if (parts[x + 1] == NULL)
				parts[x] = ft_strtrim(parts[x], "\n");
			load_points(map, parts[x], y, x);
			x++;
		}
		map->points[y][x].flag = 1;
		free(line);
        ft_strsdel(&parts);
		y++;
    }
}