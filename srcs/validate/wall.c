/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:00:29 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:30:34 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"
#include "../../libft/includes/libft.h"
#include <stdio.h>

// Check if the map is surrounded by walls

int	is_surrounded_by_walls(char **map, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
			{
				if (map[i][j] != WALL)
					return (ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
