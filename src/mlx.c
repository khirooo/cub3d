/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:40:13 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/17 13:07:33 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int	window_init(t_window **wind)
{
	*wind = (t_window *)malloc(sizeof(t_window));
	if (!*wind)
		return (1);
	(*wind)->mlx = mlx_init();
	(*wind)->win = mlx_new_window((*wind)->mlx, width, height, "Cub3D");
	(*wind)->image = (t_image *)malloc(sizeof(t_image));
	if (!*wind)
		return (1);
	(*wind)->image->img = mlx_new_image((*wind)->mlx, width, height);
	(*wind)->image->addr = mlx_get_data_addr((*wind)->image->img, &((*wind)->image->bits_per_pixel),
						&((*wind)->image->line_length), &((*wind)->image->endian));
	// (*wind)->pos.x = 22;
	// (*wind)->pos.y = 12;
	// (*wind)->dir.x = -1;
	// (*wind)->dir.y = -1;
	(*wind)->plan.x = 0;
	(*wind)->plan.y = 0.66;
	return (0);
}

double	normalize(int	x)
{
	double	ret;
	int		min;
	int		max;
	int		range;

	min = -551;
	max = 2008;
	range = max - min;
	ret = ((double)x - (double)min) / (double)range;	
	ret = (ret * 2) - 1;	
	return (ret);
}


// int	mouse_hook(t_global *glob)
// {
// 	int	x;
// 	int	y;

// 	mlx_mouse_get_pos(glob->wind->win, &x, &y);
// 	printf("x:%d, y:%d\n", x, y);
// 	printf("mouse\n");
// 	return (0);
// }

// int	key_hook(int keycode, t_global	*glob)
// {
// 	if (keycode == KEY_W &&
// 		glob->scene->matrix_map[(int)glob->wind->pos.x - 2][(int)glob->wind->pos.y] != '1')
// 		{
// 		glob->wind->pos.y += glob->wind->dir.y;
// 		glob->wind->pos.x += glob->wind->dir.x;
// 		}
// 	if (keycode == KEY_S &&
// 		glob->scene->matrix_map[(int)glob->wind->pos.x + 2][(int)glob->wind->pos.y] != '1')
// 		{
// 		glob->wind->pos.y -= glob->wind->dir.y;
// 		glob->wind->pos.x -= glob->wind->dir.x;
// 		}
// 	if (keycode == KEY_D &&
// 		glob->scene->matrix_map[(int)glob->wind->pos.x][(int)glob->wind->pos.y - 2] != '1')
// 		{
// 			glob->wind->pos.y -= glob->wind->dir.x;
// 			glob->wind->pos.x += glob->wind->dir.y;
// 		}
// 	if (keycode == KEY_A &&
// 		glob->scene->matrix_map[(int)glob->wind->pos.x][(int)glob->wind->pos.y + 2] != '1')
// 		{
// 			glob->wind->pos.y += glob->wind->dir.x;
// 			glob->wind->pos.x -= glob->wind->dir.y;
// 		}
// 	return (0);
// }

void	open_window(t_scene *scene)
{
	t_window *wind;
	t_global	glob;

	wind = (t_window *)malloc(sizeof(t_window));
	if (window_init(&wind) || !scene)
		return ;
	mlx_put_image_to_window(wind->mlx, wind->win, wind->image->img, 0, 0);
	glob.wind = wind;
	glob.scene = scene;
	set_pos_dir(scene, wind);
	mlx_mouse_hide();
	//raycast(&glob);
	//mlx_put_image_to_window(wind->mlx, wind->win, wind->image->img, 0, 0);
	mlx_key_hook(wind->win, key_hook, &glob);
	//mlx_mouse_hook(wind->win, mouse_hook, &glob);
	mlx_loop_hook(wind->mlx, raycast, (void *)&glob);
	mlx_loop(wind->mlx);
}
