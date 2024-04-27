/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:55:43 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/25 15:52:16 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf_bonus.h"

int	valid_point(char *value)
{
	int	i;

	i = 0;
	if (value == NULL)
		return (0);
	if (value[i] == '-' || value[i] == '+')
		i++;
	while (value[i] && value[i] != ',')
	{
		if (ft_isdigit(value[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strslen(char **parts)
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
