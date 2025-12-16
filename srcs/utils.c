/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:57:53 by homura            #+#    #+#             */
/*   Updated: 2025/12/15 18:32:52 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "mlx.h"

// Free the memory allocated for the map

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}

void	error_msg(char *msg)
{
	ft_putstr_fd(RED "Error\n", 2);
	ft_putendl_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
}

// Free all loaded images

void	free_images(void *mlx_ptr, t_img_set *imgs)
{
	if (imgs->player)
		mlx_destroy_image(mlx_ptr, imgs->player);
	if (imgs->wall)
		mlx_destroy_image(mlx_ptr, imgs->wall);
	if (imgs->floor)
		mlx_destroy_image(mlx_ptr, imgs->floor);
	if (imgs->collect)
		mlx_destroy_image(mlx_ptr, imgs->collect);
	if (imgs->exit)
		mlx_destroy_image(mlx_ptr, imgs->exit);
}
