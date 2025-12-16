/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:41:04 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:30:57 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Search for the specified element 'target' on the map 
// and store the first found coordinates in *pcol, *prow

int	find_element(t_game *game, char target, int *pcol, int *prow)
{
	int	col;
	int	row;

	if (!game || !game->map || game->rows <= 0)
		return (ERROR);
	row = 0;
	while (row < game->rows)
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == target)
			{
				if (pcol)
					*pcol = col;
				if (prow)
					*prow = row;
				return (SUCCESS);
			}
			col++;
		}
		row++;
	}
	return (ERROR);
}

// Search for the EXIT position and store it in exit_col, exit_row

int	find_exit(t_game *game, int *exit_col, int *exit_row)
{
	return (find_element(game, EXIT, exit_col, exit_row));
}

// Search for the PLAYER position on the map

int	find_player(t_game *game, int *player_col, int *player_row)
{
	return (find_element(game, PLAYER, player_col, player_row));
}
