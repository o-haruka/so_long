/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:21:32 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:24:28 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/stdio/ft_printf/ft_printf.h"
#include "mlx.h"
#include <stdlib.h>

int	expose_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_map(game->mlx_ptr, game->win_ptr, game);
	return (SUCCESS);
}

// Handle key press events for player movement and actions

int	key_hook(int keycode, void *param)
{
	t_game	*game;
	t_move	mv;

	game = (t_game *)param;
	if (!find_player(game, &mv.player_col, &mv.player_row))
		return (ERROR);
	get_move_dir(keycode, &mv);
	if (keycode == ESC)
		destroy_hook(game);
	if (mv.delta_col == 0 && mv.delta_row == 0)
		return (ERROR);
	mv.next_col = mv.player_col + mv.delta_col;
	mv.next_row = mv.player_row + mv.delta_row;
	if (!can_move(game->map, mv.next_col, mv.next_row))
		return (ERROR);
	if (try_exit(game, mv.next_col, mv.next_row))
		destroy_hook(game);
	do_move(game, mv);
	return (SUCCESS);
}

// Handle window close event and free all resources

int	destroy_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_printf("Window closed!\n");
	free_images(game->mlx_ptr, &game->imgs);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free_map(game->map, game->rows);
	exit(EXIT_SUCCESS);
}
