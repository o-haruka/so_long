/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:12:31 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:26:47 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/stdio/ft_printf/ft_printf.h"
#include "mlx.h"
#include <stdlib.h>

// Check if the player can move to the next position

int	can_move(char **map, int next_col, int next_row)
{
	return (map[next_row][next_col] != WALL);
}

// +Perform the player move and update the game state
// +If the source position is the EXIT, keep EXIT
// +If the destination is the EXIT position,
// 	keep PLAYER (EXIT position is managed in t_game)

void	do_move(t_game *game, t_move mv)
{
	if (game->map[mv.next_row][mv.next_col] == COLLECT)
	{
		game->collected++;
		ft_printf(CHECK "Collected an item! (%d/%d)\n", game->collected,
			game->collect_count);
	}
	if (mv.player_col == game->exit_col && mv.player_row == game->exit_row)
		game->map[mv.player_row][mv.player_col] = EXIT;
	else
		game->map[mv.player_row][mv.player_col] = EMPTY;
	game->map[mv.next_row][mv.next_col] = PLAYER;
	game->move_count++;
	ft_printf("Move count: %d\n", game->move_count);
	draw_map(game->mlx_ptr, game->win_ptr, game);
}

// Try to exit the game if the player is on the exit tile

int	try_exit(t_game *game, int next_col, int next_row)
{
	if (game->map[next_row][next_col] == EXIT)
	{
		if (game->collected < game->collect_count)
		{
			ft_printf(CROSS "Items remain!\n");
			return (ERROR);
		}
		ft_printf(GREEN "\n==============================\n"
			"     ★☆★☆  GOAL!!  ★☆★☆      "
			"\n==============================\n" RESET);
		return (SUCCESS);
	}
	return (ERROR);
}

// Get the movement direction from the keycode

void	get_move_dir(int keycode, t_move *mv)
{
	mv->delta_col = 0;
	mv->delta_row = 0;
	if (keycode == W)
		mv->delta_row = -1;
	else if (keycode == S)
		mv->delta_row = 1;
	else if (keycode == A)
		mv->delta_col = -1;
	else if (keycode == D)
		mv->delta_col = 1;
}
