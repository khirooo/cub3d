/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:40:13 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/24 14:12:58 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int	window_init(t_window **wind)
{
	*wind = (t_window *)malloc(sizeof(t_window));
	if (!*wind)
		return (1);
	(*wind)->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!(*wind)->mlx)
		return (1);
	// (*wind)->win = mlx_new_window((*wind)->mlx, width, height, "Cub3D");
	(*wind)->image = mlx_new_image((*wind)->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window((*wind)->mlx, (*wind)->image, 0, 0) < 0)
		return (1);
	(*wind)->plan.x = 0;
	(*wind)->plan.y = 1;
	return (0);
}

void	print_text(mlx_texture_t **text_arr)
{
	int	i;

	i = 0;
	while(i < 8)
	{
		printf("text %d:\n	width: %d\n	height: %d\n", i,text_arr[i]->width, text_arr[i]->height);
		i++;	
	}
}

void	open_window(t_scene *scene)
{
	t_window *wind;
	t_global	glob;

	//mlx_set_setting(MLX_MAXIMIZED, true);
	if (window_init(&wind) || !scene)
	{
		perror("MLX: Error\n");
		return ;
	}
	//mlx_put_image_to_window(wind->mlx, wind->win, wind->image->img, 0, 0);
	glob.wind = wind;
	glob.scene = scene;
	set_pos_dir(scene, wind);
	print_text(scene->text_arr);
	mlx_image_t *m;
	m = mlx_texture_to_image(wind->mlx, scene->text_arr[1]);
	int	i = 0, j;
	//mlx_image_to_window(wind->mlx, m, 5, 5);
	while (i < m->width)
	{
		j = 0;
		while (j < m->height)
		{
			int32_t color = 0;
			color = color & m->pixels[i * m->width + j];
			color = color << 8;
			color = color | 4294967296;
			mlx_put_pixel(wind->image, i, j, color);
			j++;
		}
		i++;
	}
	
	// mlx_key_hook(wind->mlx, &key_hook, (void *)&glob);
	// mlx_loop_hook(wind->mlx, raycast, (void *)&glob);
	mlx_loop(wind->mlx);
}
