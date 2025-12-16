/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:57:57 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:31:42 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../libft/stdio/get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// Frees memory and closes fd when a map load error occurs.

static void	free_map_on_error(char **map, int used, char *line, int fd)
{
	int	j;

	if (line)
		free(line);
	j = 0;
	while (j < used)
	{
		free(map[j]);
		j++;
	}
	free(map);
	if (fd >= 0)
		close(fd);
}

// Reads one line from the map file and replaces '\n' with '\0'.

static char	*read_map_line(int fd)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

// Reads the file line by line and stores each line in the map array in a loop.
// Doubles the array capacity as needed.

static int	read_map_loop(int fd, char ***map, int *capacity)
{
	int		i;
	char	**tmp;
	char	*line;

	i = 0;
	while (1)
	{
		line = read_map_line(fd);
		if (!line)
			break ;
		if (i >= *capacity)
		{
			tmp = ft_realloc(*map, sizeof(char *) * (*capacity + 1),
					sizeof(char *) * ((*capacity) * 2 + 1));
			if (!tmp)
				return (free_map_on_error(*map, i, line, fd), ERROR);
			*map = tmp;
			*capacity *= 2;
		}
		(*map)[i++] = line;
	}
	(*map)[i] = NULL;
	return (i);
}

// Opens the specified file (map file),
// reads it line by line, and returns it as a 2D array (char**).
// The number of lines read is stored in `rows`.

char	**read_map(const char *filename, int *rows)
{
	int		fd;
	int		capacity;
	char	**map;

	*rows = 0;
	capacity = 1;
	map = malloc(sizeof(char *) * (capacity + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	*rows = read_map_loop(fd, &map, &capacity);
	close(fd);
	if (*rows < 0)
		return (NULL);
	return (map);
}
