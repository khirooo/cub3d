/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:47:25 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/22 20:08:26 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	t_global *glob = globb;
	double	perpWallDist;
	int	line_h;
	int	start;
	int	end;
	int	color;
	x = 0;
	int	a;
	int	b;

	mlx_get_mouse_pos(glob->wind->mlx, &a, &b);
	if (a > 500)
	{
		double	old_dir_x = glob->wind->dir.x;
		glob->wind->dir.x = glob->wind->dir.x * cosf(-0.05) - glob->wind->dir.y * sinf(-0.05);
		glob->wind->dir.y = old_dir_x * sinf(-0.05) + glob->wind->dir.y * cosf(-0.05);
		double	old_plan_x = glob->wind->plan.x;
		glob->wind->plan.x = glob->wind->plan.x * cosf(-0.05) - glob->wind->plan.y * sinf(-0.05);
      	glob->wind->plan.y = glob->wind->plan.x * sin(-0.05) + glob->wind->plan.y * cosf(-0.05);
		mlx_set_mouse_pos(glob->wind->mlx, WIDTH / 2, HEIGHT / 2);
		//printf("pos(x, y)= %f, %f\ndir: %f, %f\n",  glob->wind->pos.x,  glob->wind->pos.y, glob->wind->dir.x, glob->wind->dir.y);
	}
	if (a < 500)
	{
		double	old_dir_x = glob->wind->dir.x;
		glob->wind->dir.x = glob->wind->dir.x * cosf(0.05) - glob->wind->dir.y * sinf(0.05);
		glob->wind->dir.y = old_dir_x * sinf(0.05) + glob->wind->dir.y * cosf(0.05);
		double	old_plan_x = glob->wind->plan.x;
		glob->wind->plan.x = glob->wind->plan.x * cosf(0.05) - glob->wind->plan.y * sinf(0.05);
      	glob->wind->plan.y = glob->wind->plan.x * sin(0.05) + glob->wind->plan.y * cosf(0.05);
		mlx_set_mouse_pos(glob->wind->mlx, WIDTH / 2, HEIGHT / 2);
		//printf("pos(x, y)= %f, %f\ndir: %f, %f\n",  glob->wind->pos.x,  glob->wind->pos.y, glob->wind->dir.x, glob->wind->dir.y);
	}
	mlx_delete_image(glob->wind->mlx, glob->wind->image);
	glob->wind->image = mlx_new_image(glob->wind->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(glob->wind->mlx, glob->wind->image, 0, 0);
	while (x < WIDTH)
	{
		cam.x = ((2 * x) / (double)WIDTH) - 1;
		raydir.x = glob->wind->dir.x + glob->wind->plan.x * cam.x;
		raydir.y = glob->wind->dir.y + glob->wind->plan.y * cam.x;
		sqr_map.x = (int)glob->wind->pos.x;
		sqr_map.y = (int)glob->wind->pos.y;
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
				sqr_map.x += (int)step.x;
				side = 0;
			}
			else
			{
				sideDist.y += delta_dist.y;
				sqr_map.y += (int)step.y;
				side = 1;
			}
			//printf("current ray_squar: |%c| x = %d, y = %d\n", glob->scene->matrix_map[(int)sqr_map.x][(int)sqr_map.y - 1], (int)sqr_map.x, (int)sqr_map.y);
			if (glob->scene->matrix_map[(int)sqr_map.x][(int)sqr_map.y] == '1')
				hit = 1;
			//getchar();
		}
		// calculate distance between player and a hit
		if(side == 0)
			perpWallDist = (sideDist.x - delta_dist.x);
		else
			perpWallDist = (sideDist.y - delta_dist.y);
		line_h =(int)(HEIGHT * 1.5 / perpWallDist);
		//printf("line h == %d\n", line_h);
		//getchar();
		start = -line_h / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		end =  line_h / 2 + HEIGHT / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
		color = 0xFF0000FF;
		if(side == 1)
			color = color / 2;
		draw_wall(x, start, end, glob->wind, color);
		x++;
	}
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