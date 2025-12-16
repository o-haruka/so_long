/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:07:34 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 21:19:35 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"
#include "../../libft/includes/libft.h"
#include <stdlib.h>

/*
** flood fill algorithm to check map solvability
*/

// Free the 2D visited array

static void	free_visited(int **visited, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

// Allocate a 2D array for visited flags

int	**allocate_visited(int rows, int cols)
{
	int	**visited;
	int	i;

	visited = malloc(sizeof(int *) * rows);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		visited[i] = ft_calloc(cols, sizeof(int));
		if (!visited[i])
			return (NULL);
		i++;
	}
	return (visited);
}

// Flood fill algorithm to mark reachable tiles

static void	flood_fill(t_mapinfo info, int row, int col, int **visited)
{
	if (row < 0 || col < 0 || row >= info.rows || col >= info.cols)
		return ;
	if (info.map[row][col] == WALL || visited[row][col])
		return ;
	visited[row][col] = 1;
	flood_fill(info, row + 1, col, visited);
	flood_fill(info, row - 1, col, visited);
	flood_fill(info, row, col + 1, visited);
	flood_fill(info, row, col - 1, visited);
}

// Check if all collectibles and exit are reachable

static int	check_reachable(t_mapinfo info, int **visited)
{
	int	i;
	int	j;

	i = 0;
	while (i < info.rows)
	{
		j = 0;
		while (j < info.cols)
		{
			if ((info.map[i][j] == COLLECT || info.map[i][j] == EXIT)
				&& !visited[i][j])
				return (ERROR);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

// Determine if the map is solvable (all items and exit reachable)

int	is_map_solvable(char **map, int rows, int cols)
{
	int			**visited;
	int			player_col;
	int			player_row;
	t_mapinfo	info;
	t_game		tmp_game;

	player_col = -1;
	player_row = -1;
	info.map = map;
	info.rows = rows;
	info.cols = cols;
	visited = allocate_visited(rows, cols);
	if (!visited)
		return (ERROR);
	tmp_game.map = map;
	tmp_game.rows = rows;
	if (!find_player(&tmp_game, &player_col, &player_row))
		return (free_visited(visited, rows), ERROR);
	flood_fill(info, player_row, player_col, visited);
	if (check_reachable(info, visited) == SUCCESS)
		return (free_visited(visited, rows), SUCCESS);
	return (free_visited(visited, rows), ERROR);
}
