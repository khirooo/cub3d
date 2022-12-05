/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:40:13 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/05 19:47:59 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_init(t_window **wind)
{
	*wind = (t_window *)malloc(sizeof(t_window));
	if (!*wind)
		return (1);
	(*wind)->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!(*wind)->mlx)
		return (1);
	(*wind)->image = mlx_new_image((*wind)->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window((*wind)->mlx, (*wind)->image, 0, 0) < 0)
		return (1);
	return (0);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	open_window(t_scene *scene)
{
	t_window	*wind;
	t_global	glob;

	if (window_init(&wind) || !scene)
	{
		perror("MLX: Error\n");
		return ;
	}
	glob.wind = wind;
	glob.scene = scene;
	glob.mode = 1;
	set_pos_dir(scene, wind);
	mlx_key_hook(wind->mlx, &key_hook, (void *)&glob);
	mlx_loop_hook(wind->mlx, raycast, (void *)&glob);
	mlx_loop(wind->mlx);
}
