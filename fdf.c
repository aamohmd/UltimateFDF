/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:05:26 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/12 05:38:50 by aamohame         ###   ########.fr       */
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

void	check_map(char *filename, t_map *map)
{
    int		fd;
    char	*line;
    char	**parts;
	int		previous_num_columns;

    if (ft_file_name_error(filename) == 1)
        terminate("wrong file name");
    fd = open(filename, O_RDONLY);
    if (fd == -1)
	{
        terminate("can't open file");
	}
	map->num_rows = 0;
	map->num_columns = 0;
	line = ft_strdup("");
	if (line == NULL)
        terminate("memory allocation failed");
    while ((line = get_next_line(fd)) != NULL)
    {
        parts = ft_split(line, ' ');
		previous_num_columns = map->num_columns;
		map->num_columns = ft_strslen(parts);
        if (previous_num_columns != map->num_columns && map->num_rows != 0)
        {
            free(line);
            ft_strsdel(&parts);
            terminate("inconsistent number of columns");
        }
		free(line);
        ft_strsdel(&parts);
		map->num_rows++;
    }
    close(fd);
}

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc == 2)
	{
		check_map(argv[1], &map);
		printf("%d\n", map.num_columns);
		printf("%d\n", map.num_rows);
	}
}
