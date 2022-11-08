/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:40:13 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/06 21:26:00 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	open_window(t_scene *scene)
{
	t_window *wind;

	wind = (t_window *)malloc(sizeof(t_window));
	if (!wind || !scene)
		return ;
	wind->mlx = mlx_init();
	wind->win = mlx_new_window(wind->mlx, 1024, 512, "Cub3D");
	wind->image = (t_image *)malloc(sizeof(t_image));
	wind->image->img = mlx_new_image(wind->mlx, 1024, 512);
	wind->image->addr = mlx_get_data_addr(wind->image->img, &(wind->image->bits_per_pixel), &(wind->image->line_length), &(wind->image->endian));
	my_mlx_pixel_put(wind->image, 512, 256, 0x00FF0000);
	mlx_put_image_to_window(wind->mlx, wind->win, wind->image->img, 0, 0);
	mlx_loop(wind->mlx);
}
