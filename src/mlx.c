/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:40:13 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/09 19:22:26 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	window_init(t_window **wind)
{
	*wind = (t_window *)malloc(sizeof(t_window));
	if (!*wind)
		return (1);
	(*wind)->mlx = mlx_init();
	(*wind)->win = mlx_new_window((*wind)->mlx, 1024, 512, "Cub3D");
	(*wind)->image = (t_image *)malloc(sizeof(t_image));
	if (!*wind)
		return (1);
	(*wind)->image->img = mlx_new_image((*wind)->mlx, 1024, 512);
	(*wind)->image->addr = mlx_get_data_addr((*wind)->image->img, &((*wind)->image->bits_per_pixel),
						&((*wind)->image->line_length), &((*wind)->image->endian));
	// (*wind)->pos.x = 22;
	// (*wind)->pos.y = 12;
	(*wind)->dir.x = -1;
	(*wind)->dir.x = 0;
	(*wind)->plan.x = 0;
	(*wind)->plan.y = 0.66;
	return (0);
}

void	draw_wall(int x, int start, int end, t_window *wind)
{
	while (start <= end)
	{
		mlx_put_image_to_window(wind->mlx, wind->win, wind->image->img, x, start);
		start++;
	}
}

void	raycast(void *globb)
{
	int	x;
	t_point	cam;
	t_point	raydir;
	t_point	sqr_map;
	t_point	sideDist;
	t_point	delta_dist;
	t_point	step;
	int	hit;
	int	side;
	t_global *globbb = globb;
	t_global glob = *globbb;
	double	perpWallDist;
	int	line_h;
	int	start;
	int	end;
	x = 0;
	//cast a ray
	while (x < 512)
	{
		cam.x = ((2 * x) / 512) - 1;
		raydir.x = glob.wind->dir.x + glob.wind->plan.x * cam.x;
		raydir.y = glob.wind->dir.y + glob.wind->plan.y * cam.x;
		sqr_map.x = glob.wind->pos.x;
		sqr_map.y = glob.wind->pos.y;
		if (raydir.x)
			delta_dist.x = 1 / raydir.x;
		else
			delta_dist.x = DBL_MAX;
		if (raydir.y)
			delta_dist.y = 1 / raydir.y;
		else
			delta_dist.y = DBL_MAX;
		step.x = 0;
		step.y = 0;
		hit = 0;
		side = 0;
		if (raydir.x < 0)
		{
			step.x = -1;
			sideDist.x = (glob.wind->pos.x - sqr_map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (sqr_map.x + 1 - glob.wind->pos.x) * delta_dist.x;
		}
		if (raydir.y < 0)
		{
			step.x = -1;
			sideDist.y = (glob.wind->pos.y - sqr_map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			sideDist.y = (sqr_map.y + 1 - glob.wind->pos.y) * delta_dist.y;
		}
		while (hit == 0)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += step.x;
				sqr_map.x += step.x;
				side = 0;
			}
			else
			{
				sideDist.y += step.y;
				sqr_map.y += step.y;
				side = 0;
			}
			if (!strcmp(glob.scene->matrix_map[(int)sqr_map.x][(int)sqr_map.y], "1"))
				hit = 1;
		}
		x++;
	}
	// calculate distance between player and a hit
	if(side == 0)
		perpWallDist = (sideDist.x - delta_dist.x);
	else
		perpWallDist = (sideDist.x - delta_dist.y);
	line_h = 256 / perpWallDist;
	start = -line_h / 2 + 256 / 2;
	if (start < 0)
		start = 0;
	end =  line_h / 2 + 256 / 2;
	if (end >= 256)
		end = 255;
	draw_wall(x, start, end, glob.wind);
}

void	set_pos_dir(t_scene *scene, t_window *wind)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (scene->matrix_map[i][j])
	{
		j = 0;
		while (j < ft_strlen(scene->matrix_map[i]))
		{
			if (scene->matrix_map[i][j] > '1')
				c = scene->matrix_map[i][j];
			j++;
		}
		i++;	
	}
	wind->pos.x = i;
	wind->pos.y = j;
	//initilize dir here later
}

void	open_window(t_scene *scene)
{
	t_window *wind;
	t_global	glob;

	wind = (t_window *)malloc(sizeof(t_window));
	if (window_init(&wind) || !scene)
		return ;
	my_mlx_pixel_put(wind->image, 512, 256, 0x00FF0000);
	mlx_put_image_to_window(wind->mlx, wind->win, wind->image->img, 0, 0);
	glob.wind = wind;
	glob.scene = scene;
	set_pos_dir(scene, wind);
	mlx_loop_hook(wind->mlx, raycast, (void *)&glob);
	mlx_loop(wind->mlx);
}
