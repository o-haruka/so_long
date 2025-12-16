/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:19:50 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:31:12 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../libft/stdio/ft_printf/ft_printf.h"
#include "../libft/stdio/get_next_line/get_next_line.h"
#include "mlx.h"

int	is_ber_file(const char *filename)
{
	int	len;

	if (!filename)
		return (ERROR);
	len = ft_strlen(filename);
	if (len < 4)
		return (ERROR);
	if (ft_strncmp(filename + len - 4, ".ber", 4) == 0)
		return (SUCCESS);
	return (ERROR);
}

// Validate command line arguments for the program

int	validate_args(int argc, char **argv)
{
	if (argc != 2)
		return (error_msg("Usage: ./so_long <path to map.ber>"), ERROR);
	if (!is_ber_file(argv[1]))
		return (error_msg("Map file must have .ber extension"), ERROR);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game = (t_game){0};
	if (!validate_args(argc, argv))
		return (ERROR);
	game = setup_game(argv);
	mlx_setup_game(&game);
	draw_map(game.mlx_ptr, game.win_ptr, &game);
	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_hook(game.win_ptr, ON_EXPOSE, 0, expose_hook, &game);
	mlx_hook(game.win_ptr, ON_DESTROY, 0, destroy_hook, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
