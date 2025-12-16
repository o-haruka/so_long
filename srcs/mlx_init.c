/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:54:04 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:32:31 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "mlx.h"

// Initialize mlx and exit with cleanup if it fails

void	*init_mlx_or_exit_with_map(char **map, int rows)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
	{
		error_msg("Failed to initialize mlx");
		free_map(map, rows);
		exit(EXIT_FAILURE);
	}
	return (mlx_ptr);
}

// Create a new window and exit if it fails

void	*create_window_or_exit(void *mlx_ptr, int width, int height,
		const char *title)
{
	void	*win_ptr;

	win_ptr = mlx_new_window(mlx_ptr, width, height, (char *)title);
	if (win_ptr == NULL)
	{
		error_msg("Failed to create window");
		exit(EXIT_FAILURE);
	}
	return (win_ptr);
}

// Initialize all images from XPM files

void	init_images(void *mlx_ptr, t_img_set *imgs)
{
	imgs->player = mlx_xpm_file_to_image(mlx_ptr, "images/player.xpm",
			&imgs->width, &imgs->height);
	imgs->wall = mlx_xpm_file_to_image(mlx_ptr, "images/wall.xpm", &imgs->width,
			&imgs->height);
	imgs->floor = mlx_xpm_file_to_image(mlx_ptr, "images/floor.xpm",
			&imgs->width, &imgs->height);
	imgs->collect = mlx_xpm_file_to_image(mlx_ptr, "images/collect.xpm",
			&imgs->width, &imgs->height);
	imgs->exit = mlx_xpm_file_to_image(mlx_ptr, "images/exit.xpm", &imgs->width,
			&imgs->height);
	if (!imgs->player || !imgs->wall || !imgs->floor || !imgs->collect
		|| !imgs->exit)
	{
		error_msg("Failed to load one or more images");
		free_images(mlx_ptr, imgs);
		exit(EXIT_FAILURE);
	}
}

void	mlx_setup_game(t_game *game)
{
	game->mlx_ptr = init_mlx_or_exit_with_map(game->map, game->rows);
	init_images(game->mlx_ptr, &game->imgs);
	game->win_ptr = create_window_or_exit(game->mlx_ptr, game->imgs.width
			* ft_strlen(game->map[0]), game->imgs.height * game->rows,
			"so_long");
}
