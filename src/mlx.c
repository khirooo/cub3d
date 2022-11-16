/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:40:13 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/16 20:23:13 by kfergani         ###   ########.fr       */
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

void	draw_wall(int x, int start, int end, t_window *wind, int color)
{
	//printf("x = %d, start = %d, end = %d\n", x, start, end);
	while (start <= end)
	{
		my_mlx_pixel_put(wind->image, x, start, color);
		start++;
	}
}

double	normalize(int	x)
{
	double	ret;
	int		min;
	int		max;
	int		range;
	int		range2;

	min = -551;
	max = 2008;
	range = max - min;
	ret = ((double)x - (double)min) / (double)range;	
	ret = (ret * 2) - 1;	
	return (ret);
}

int	raycast(void *globb)
{
	//printf("seg2\n");
	int	x;
	t_point	cam;
	t_point	raydir;
	t_point	sqr_map;
	t_point	sideDist;
	t_point	delta_dist;
	t_point	step;
	int	hit;
	int	side;
	t_global *glob = globb;
	double	perpWallDist;
	int	line_h;
	int	start;
	int	end;
	int	color;
	x = 0;
	int	a;
	int	b;

	mlx_mouse_get_pos(glob->wind->win, &a, &b);
	printf("x:%d, y:%d, norm:%f\n", a, b, normalize(a));
	// if (a < 0)
	// {
	// 	glob->wind->dir.y = 
	// }
	// else
	// {
		
	// }
	if (a > 500)
	{
		double	old_dir_x = glob->wind->dir.x;
		glob->wind->dir.x = glob->wind->dir.x * cosf(-0.05) - glob->wind->dir.y * sinf(-0.05);
		glob->wind->dir.y = old_dir_x * sinf(-0.05) + glob->wind->dir.y * cosf(-0.05);
		double	old_plan_x = glob->wind->plan.x;
		glob->wind->plan.x = glob->wind->plan.x * cosf(-0.05) - glob->wind->plan.y * sinf(-0.05);
      	glob->wind->plan.y = glob->wind->plan.x * sin(-0.05) + glob->wind->plan.y * cosf(-0.05);
		mlx_mouse_move(glob->wind->win, width / 2, height / 2);
		printf("pos(x, y)= %f, %f\ndir: %f, %f\n",  glob->wind->pos.x,  glob->wind->pos.y, glob->wind->dir.x, glob->wind->dir.y);
	}
	if (a < 500)
	{
		double	old_dir_x = glob->wind->dir.x;
		glob->wind->dir.x = glob->wind->dir.x * cosf(0.05) - glob->wind->dir.y * sinf(0.05);
		glob->wind->dir.y = old_dir_x * sinf(0.05) + glob->wind->dir.y * cosf(0.05);
		double	old_plan_x = glob->wind->plan.x;
		glob->wind->plan.x = glob->wind->plan.x * cosf(0.05) - glob->wind->plan.y * sinf(0.05);
      	glob->wind->plan.y = glob->wind->plan.x * sin(0.05) + glob->wind->plan.y * cosf(0.05);
		mlx_mouse_move(glob->wind->win, width / 2, height / 2);
		printf("pos(x, y)= %f, %f\ndir: %f, %f\n",  glob->wind->pos.x,  glob->wind->pos.y, glob->wind->dir.x, glob->wind->dir.y);
	}
	// if (glob->wind->dir.x > 1 || glob->wind->dir.x < -1)
	// 		glob->wind->dir.x = 0;
	// if (glob->wind->dir.y > 1 || glob->wind->dir.y < -1)
	// 		glob->wind->dir.y = 0;
	//cast a ray
	//printf("initial state:\nPos(%d, %d)\nDir(%d, %d)\nPlan(%f, %f)\n", (int)glob->wind->pos.x, (int)glob->wind->pos.y, (int)glob->wind->dir.x, (int)glob->wind->dir.y, glob->wind->plan.x, glob->wind->plan.y);
	mlx_destroy_image(glob->wind->mlx, glob->wind->image->img);
	glob->wind->image->img = mlx_new_image(glob->wind->mlx, width, height);
	while (x < width)
	{
		//printf("x == %d\n", x);
		cam.x = ((2 * x) / (double)width) - 1;
		raydir.x = glob->wind->dir.x + glob->wind->plan.x * cam.x;
		raydir.y = glob->wind->dir.y + glob->wind->plan.y * cam.x;
		sqr_map.x = glob->wind->pos.x;
		sqr_map.y = glob->wind->pos.y;
		if (raydir.x)
			delta_dist.x = fabs(1.0 / raydir.x);
		else
			delta_dist.x = DBL_MAX;
		if (raydir.y)
			delta_dist.y = fabs(1.0 / raydir.y);
		else
			delta_dist.y = DBL_MAX;
		step.x = 0;
		step.y = 0;
		hit = 0;
		side = 0;
		if (raydir.x < 0)
		{
			step.x = -1.0;
			sideDist.x = (glob->wind->pos.x - sqr_map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1.0;
			sideDist.x = (sqr_map.x + 1.0 - glob->wind->pos.x) * delta_dist.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1.0;
			sideDist.y = (glob->wind->pos.y - sqr_map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1.0;
			sideDist.y = (sqr_map.y + 1.0 - glob->wind->pos.y) * delta_dist.y;
		}
		while (hit == 0)
		{
			//printf("step.x: %f, step.y: %f\n", step.x, step.y);
			//printf("sideD.x: %f, sideD.y: %f\n", sideDist.x, sideDist.y);
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += delta_dist.x;
				sqr_map.x += step.x;
				side = 0;
			}
			else
			{
				sideDist.y += delta_dist.y;
				sqr_map.y += step.y;
				side = 1;
			}
			//printf("current ray_squar: |%c| x = %d, y = %d\n", glob->scene->matrix_map[(int)sqr_map.x][(int)sqr_map.y - 1], (int)sqr_map.x, (int)sqr_map.y);
			if (glob->scene->matrix_map[(int)sqr_map.x][(int)sqr_map.y] == '1')
				hit = 1;
			//getchar();
		}
		// calculate distance between player and a hit
		if(side == 0)
			perpWallDist = (sideDist.x - delta_dist.x); // problem here <<<<-----
		else
			perpWallDist = (sideDist.y - delta_dist.y);
		line_h =(int)(height / perpWallDist);
		//printf("line h == %d\n", line_h);
		//getchar();
		start = -line_h / 2 + height / 2;
		if (start < 0)
			start = 0;
		end =  line_h / 2 + height / 2;
		if (end >= height)
			end = height - 1;
		color = 0x00FF0000;
		if(side == 1)
			color = color / 2;
		draw_wall(x, start, end, glob->wind, color);
		x++;
	}
	mlx_put_image_to_window(glob->wind->mlx, glob->wind->win, glob->wind->image->img, 0, 0);
	return (0);
}

void	set_pos_dir(t_scene *scene, t_window *wind)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (scene->matrix_map[i])
	{
		j = 0;
		while (j < ft_strlen(scene->matrix_map[i]))
		{
			if (scene->matrix_map[i][j] > '1')
			{
				wind->pos.x = i;
				wind->pos.y = j;
				c = scene->matrix_map[i][j];
			}
			j++;
		}
		i++;
	}
	if (c == 'N')
	{
		wind->dir.x = -1;
		wind->dir.y = 0;
	}
	if (c == 'S')
	{
		wind->dir.x = 1;
		wind->dir.y = 0;
	}
	if (c == 'W')
	{
		wind->dir.x = 0;
		wind->dir.y = -1;
	}
	if (c == 'E')
	{
		wind->dir.x = 0;
		wind->dir.y = 1;
	}
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

int	key_hook(int keycode, t_global	*glob)
{
	if (keycode == KEY_W &&
		glob->scene->matrix_map[(int)glob->wind->pos.x - 2][(int)glob->wind->pos.y] != '1')
		{
		glob->wind->pos.y += glob->wind->dir.y;
		glob->wind->pos.x += glob->wind->dir.x;
		}
	if (keycode == KEY_S &&
		glob->scene->matrix_map[(int)glob->wind->pos.x + 2][(int)glob->wind->pos.y] != '1')
		{
		glob->wind->pos.y -= glob->wind->dir.y;
		glob->wind->pos.x -= glob->wind->dir.x;
		}
	if (keycode == KEY_D &&
		glob->scene->matrix_map[(int)glob->wind->pos.x][(int)glob->wind->pos.y - 2] != '1')
		{
			glob->wind->pos.y -= glob->wind->dir.x;
			glob->wind->pos.x += glob->wind->dir.y;
		}
	if (keycode == KEY_A &&
		glob->scene->matrix_map[(int)glob->wind->pos.x][(int)glob->wind->pos.y + 2] != '1')
		{
			glob->wind->pos.y += glob->wind->dir.x;
			glob->wind->pos.x -= glob->wind->dir.y;
		}
	return (0);
}

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
