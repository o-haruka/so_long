/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:15:43 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:30:47 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

// Draw a single tile based on its type
// Draw EXIT then PLAYER if same position

static void	draw_tile(t_tileinfo info, t_game *game)
{
	mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.imgs->floor,
		info.col * info.imgs->width, info.row * info.imgs->height);
	if (info.col == game->exit_col
		&& info.row == game->exit_row
		&& info.tile == PLAYER)
	{
		mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.imgs->exit,
			info.col * info.imgs->width, info.row * info.imgs->height);
		mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.imgs->player,
			info.col * info.imgs->width, info.row * info.imgs->height);
	}
	else if (info.tile == PLAYER)
		mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.imgs->player,
			info.col * info.imgs->width, info.row * info.imgs->height);
	else if (info.tile == WALL)
		mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.imgs->wall,
			info.col * info.imgs->width, info.row * info.imgs->height);
	else if (info.tile == COLLECT)
		mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.imgs->collect,
			info.col * info.imgs->width, info.row * info.imgs->height);
	else if (info.tile == EXIT)
		mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, info.imgs->exit,
			info.col * info.imgs->width, info.row * info.imgs->height);
}

// Draw the entire map using the image set

void	draw_map(void *mlx_ptr, void *win_ptr, t_game *game)
{
	int			row;
	int			col;
	char		**map;
	t_tileinfo	info;

	map = game->map;
	row = 0;
	while (row < game->rows)
	{
		col = 0;
		while (map[row][col])
		{
			info.mlx_ptr = mlx_ptr;
			info.win_ptr = win_ptr;
			info.imgs = &game->imgs;
			info.col = col;
			info.row = row;
			info.tile = map[row][col];
			draw_tile(info, game);
			col++;
		}
		row++;
	}
}
