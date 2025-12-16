/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:02:01 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:29:13 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"
#include "../../libft/includes/libft.h"
#include <stdio.h>

// Check if the map contains no empty lines
// (including lines with only whitespace)

int	has_no_empty_lines(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		if (!map[i] || ft_isstrspace(map[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

// Check if the map is rectangular and return its width and height

int	is_rectangular(char **map, int *width, int *height)
{
	int	i;
	int	len;

	if (!map || !map[0])
		return (ERROR);
	len = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != len)
			return (ERROR);
		i++;
	}
	*width = len;
	*height = i;
	return (SUCCESS);
}

// Validate the map by checking shape, walls, elements, and solvability

int	validate_map(char **map, int rows)
{
	int	cols;

	cols = 0;
	if (rows == 0 || !map)
		return (error_msg("Map is empty or not loaded"), ERROR);
	if (!has_no_empty_lines(map, rows))
		return (error_msg("Empty line in map"), ERROR);
	if (!is_rectangular(map, &cols, &rows))
		return (error_msg("Map is not rectangular"), ERROR);
	if (!has_only_valid_chars(map, rows, cols))
		return (error_msg("Invalid character in map"), ERROR);
	if (!is_surrounded_by_walls(map, rows, cols))
		return (error_msg("Map is not surrounded by walls"), ERROR);
	if (!has_required_elements(map, rows, cols))
		return (error_msg("Map does not have required elements P/E/C"), ERROR);
	if (!is_map_solvable(map, rows, cols))
		return (error_msg("Map is not solvable"), ERROR);
	return (SUCCESS);
}
