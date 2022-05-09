/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:01:12 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 12:59:08 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

void	init_points_to_wall(const t_map *map, t_matrix *const *result)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			zero_init_point(&result[x][y]);
			result[x][y].mat[2][0] = 1;
			x++;
		}
		y++;
	}
}

int	print_error(char *msg)
{
	static int	is_first_error = 1;

	if (is_first_error == 1)
		ft_putstr_fd(msg, 2);
	is_first_error--;
	return (1);
}

int	spawn_is_set(t_map *result)
{
	if (result == NULL)
		return (0);
	if (result->spawn_orientation == 0)
	{
		ft_putendl_fd("Error\nNo spawn point in map", 2);
		return (0);
	}
	return (1);
}
