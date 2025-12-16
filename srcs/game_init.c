/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:29:34 by homura            #+#    #+#             */
/*   Updated: 2025/12/16 13:42:06 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "mlx.h"

// Count the number of collectibles in the map

int	count_collectibles_in_map(char **map, int rows)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == COLLECT)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	exit_with_error(char *msg, char **map, int rows)
{
	error_msg(msg);
	if (map)
		free_map(map, rows);
	exit(EXIT_FAILURE);
}

void	set_exit_pos(t_game *game)
{
	int	ex;
	int	ey;

	if (find_exit(game, &ex, &ey) == SUCCESS)
	{
		game->exit_col = ex;
		game->exit_row = ey;
	}
}

t_game	setup_game(char **argv)
{
	t_game	game;

	game = (t_game){0};
	game.map = read_map(argv[1], &game.rows);
	if (!game.map)
		exit_with_error("Failed to load map file or file not found", NULL, 0);
	if (!validate_map(game.map, game.rows))
		exit_with_error("Invalid map", game.map, game.rows);
	game.collect_count = count_collectibles_in_map(game.map, game.rows);
	game.collected = 0;
	game.move_count = 0;
	set_exit_pos(&game);
	return (game);
}
