/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:29:34 by aamohame          #+#    #+#             */
/*   Updated: 2024/04/15 19:56:12 by aamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int valid_point(char *value)
{
    if (value == NULL)
        return (0);
    if (*value == '-' || *value == '+')
        value++;
    while (*value)
	{
        if (ft_isdigit(*value) == 0)
            return (0);
        value++;
    }
    return (1);
}