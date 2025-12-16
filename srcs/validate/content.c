/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:00:35 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:28:57 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"
#include "../../libft/includes/libft.h"
#include <stdio.h>

// Check if the map contains only valid characters (0,1,C,E,P)

int	has_only_valid_chars(char **map, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] != EMPTY && map[i][j] != WALL && map[i][j] != COLLECT
				&& map[i][j] != EXIT && map[i][j] != PLAYER)
				return (ERROR);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

// Count the number of player, exit, and collect elements in the map

static void	count_elements(char **map, int rows, int cols, t_elemcount *cnt)
{
	int	i;
	int	j;

	cnt->player = 0;
	cnt->exit = 0;
	cnt->collect = 0;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] == PLAYER)
				cnt->player++;
			if (map[i][j] == EXIT)
				cnt->exit++;
			if (map[i][j] == COLLECT)
				cnt->collect++;
			j++;
		}
		i++;
	}
}

// Check if the map has the required elements:
// 1 player, exactly 1 exit, and at least 1 collect

int	has_required_elements(char **map, int rows, int cols)
{
	t_elemcount	cnt;

	count_elements(map, rows, cols, &cnt);
	if (cnt.player != 1 || cnt.exit != 1 || cnt.collect < 1)
	{
		if (cnt.player != 1)
			error_msg("Invalid number of player (P)");
		else if (cnt.exit != 1)
			error_msg("Invalid number of exit (E)");
		else if (cnt.collect < 1)
			error_msg("No collectible (C) found");
		return (ERROR);
	}
	return (SUCCESS);
}
