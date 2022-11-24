/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:47:25 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/24 18:25:10 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_buff(t_global *glob, int32_t buffer[WIDTH][HEIGHT])
{
    int	c1 = 0 ,c2;
	while (c1 < WIDTH)
	{
		c2 = 0;
		while (c2 < HEIGHT)
		{
			mlx_put_pixel(glob->wind->image, c1, c2, buffer[c1][c2]);
			c2++;
		}
		c1++;
	}
}

int		get_tex_num(int	side, double ray_x, double ray_y)
{
	if (side == 0 && ray_x > 0)
		return (1);
	if (side == 0 && ray_x < 0)
		return (0);
	if (side == 1 && ray_y < 0)
		return (3);
	if (side == 1 && ray_y > 0)
		return (2);
	return (0);
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
	t_global *glob = globb;
	double	perpWallDist;
	int	line_h;
	int	start;
	int	end;
	int		color;
	x = 0;
	int	a;
	int	b;
	int		buffer[WIDTH][HEIGHT];

	int	c1 = 0 ,c2;
	//clear buffer
	while (c1 < WIDTH)
	{
		c2 = 0;
		while (c2 < HEIGHT)
		{
			buffer[c1][c2] = 0;
			c2++;
		}
		c1++;
	}
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
		line_h =(int)(HEIGHT * 0.6 / perpWallDist);
		//printf("line h == %d\n", line_h);
		//getchar();
		start = -line_h / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		end =  line_h / 2 + HEIGHT / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
		
		//texture to use 
		int	texNum = 0;
		// where did the ray hit the wall ? (relative to the map)
		double	wall_x;
		if (side == 0)
			wall_x = glob->wind->pos.y + perpWallDist * raydir.y;
		else
			wall_x = glob->wind->pos.x + perpWallDist * raydir.x;
		// where did the ray hit the wall ? (relative to the wall)
		wall_x = wall_x - (double)((int)wall_x);
		// wich coordinate is it on the texture ?
		int	tex_x = (int)(wall_x * (double)64);
		// this might be optional (to not have the same text on two facing sides of the wall)
		if ((side == 0 && raydir.x > 0) || (side == 1 && raydir.y < 0))
			tex_x = 64 - tex_x  -1;
		// whats the next pixel on the line ? (step = 1 if your super close to the wall gets bigger the farther u go)
		double	step = 1.0 * glob->scene->text_arr[2]->height / line_h;
		//not sure ...
		double tex_pos = (start - HEIGHT / 2 + line_h / 2) * step;
		int y1;
		y1 = start;
		int	tex_y;
		mlx_texture_t *tex = glob->scene->text_arr[get_tex_num(side, raydir.x, raydir.y)];
		
		int m = 0;
    	while (m < start)
       	 buffer[x][m++] = createRGB(glob->scene->f[0], glob->scene->f[1], glob->scene->f[2]);
		while (y1 < end)
		{
			tex_y = (int)tex_pos & (64 - 1);
			tex_pos += step;
			color = get_rgba(tex->pixels[64 * tex_y * 4 + tex_x * 4], tex->pixels[64 * tex_y * 4 + tex_x * 4 + 1], tex->pixels[64 * tex_y * 4 + tex_x * 4 + 2], tex->pixels[64 * tex_y * 4 + tex_x * 4 + 3]);
			//printf("pos: %f, tex(%d, %d), color: %.6x\n",tex_pos, tex_x, tex_y, color);
			if (side == 1)
				color = (color >> 1) & 8355711;
			buffer[x][y1] = color;
			y1++;
			m++;
		}
    	while (m < HEIGHT)
       		buffer[x][m++] = createRGB(glob->scene->c[0], glob->scene->c[1], glob->scene->c[2]);
		//getchar();
		// color = 0xFF0000FF;
		// if(side == 1)
		// 	color = color / 2;
		// draw_wall(x, start, end, glob->wind, color, glob);
		x++;
	}
	draw_buff(glob, buffer);
	c1 = 0;
	//clear buffer
	while (c1 < WIDTH)
	{
		c2 = 0;
		while (c2 < HEIGHT)
		{
			//printf("buff:%d\n", buffer[c1][c2]);
			buffer[c1][c2] = 0;
			c2++;
		}
		c1++;
	}
	//getchar();
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