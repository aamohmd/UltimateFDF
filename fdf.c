/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:05:26 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/15 20:01:32 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strslen(char	**parts)
{
	int	i;

	i = 0;
	while (parts[i])
		i++;
	return (i);
}

void	ft_strsdel(char ***strs)
{
    int	i;

    if (!strs || !*strs)
        return ;
    i = 0;
    while ((*strs)[i])
    {
        free((*strs)[i]);
        i++;
    }
    free(*strs);
    *strs = NULL;
}

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

void	terminate(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

int	get_next_line_fdf(int fd, char **line)
{
	*line = get_next_line(fd);
	if (*line == NULL)
		return (1);
	return (0);
}

void	create_2d_array(t_map *map)
{
	int i;

	i = 0;
	map->points = (t_point **)malloc(map->num_rows * sizeof(t_point *));
    while (i < map->num_rows)
	{
        map->points[i] = (t_point *)malloc(map->num_columns * sizeof(t_point));
		i++;
    }
}

int	map_dimensions(char *filename, t_map *map)
{
    int		fd;
    char	*line;
	int		previous_num_columns;
	char	**parts;

	map->num_rows = 0;
    if (ft_file_name_error(filename) == 1)
        terminate("wrong file name");
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        terminate("can't open file");
    while (get_next_line_fdf(fd, &line) == 0)
    {
		parts = ft_split(line, ' ');
		previous_num_columns = map->num_columns;
		map->num_columns = ft_strslen(parts);
        if (previous_num_columns != map->num_columns && map->num_rows != 0)
			return (free(line), ft_strsdel(&parts), terminate("inconsistent number of columns"), 1);
		free(line);
        ft_strsdel(&parts);
		map->num_rows++;
    }
	close(fd);
	return (0);
}
void	load_points(t_map *map, char *filename)
{
	int		fd;
	char	**parts;
    char	*line;
	int		i;
	int		j;

	i = 0;
	fd = open(filename, O_RDONLY);
	map_dimensions(filename, map);
	create_2d_array(map);
	while (i < map->num_rows)
    {
		j = 0;
		line = get_next_line(fd);
		parts = ft_split(line, ' ');
		while (parts[j])
		{
			if (valid_point(parts[j]) == 1)
				map->points[i][j].z = ft_atoi(parts[j]);
			// else if (valid_point(parts[j]) == 0)
			// 	terminate("invalid point");
			j++;
		}
		free(line);
        ft_strsdel(&parts);
		i++;
    }
}

int	main(int argc, char *argv[])
{
	t_map	map;
	int		i;
	int		j;

	if (argc == 2)
	{
		load_points(&map, argv[1]);
		i = 0;
		while (i < map.num_rows)
		{
			j = 0;
			while (j < map.num_columns)
			{
				printf("%d ", map.points[i][j].z);
				j++;
			}
			i++;
		}
	}
}
