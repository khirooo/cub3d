/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:47:25 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/28 04:00:08 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_buff(t_global *glob, int32_t buffer[WIDTH][HEIGHT])
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			mlx_put_pixel(glob->wind->image, i, j, buffer[i][j]);
			j++;
		}
		i++;
	}
}

int	tex_num(int side, double ray_x, double ray_y)
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

void	mouse_rotate(t_window *wind, int a, int flag)
{
	double	old_dir_x;
	double	old_plan_x;
	double	angle;

	if (flag)
		mlx_get_mouse_pos(wind->mlx, &a, &wind->x);
	angle = 0.05;
	if (a > WIDTH / 2)
		angle = -0.05;
	if (a != WIDTH / 2)
	{
		old_dir_x = wind->dir.x;
		wind->dir.x = wind->dir.x * cosf(angle) - wind->dir.y * sinf(angle);
		wind->dir.y = old_dir_x * sinf(angle) + wind->dir.y * cosf(angle);
		old_plan_x = wind->plan.x;
		wind->plan.x = wind->plan.x * cosf(angle) - wind->plan.y * sinf(angle);
		wind->plan.y = old_plan_x * sin(angle) + wind->plan.y * cosf(angle);
		mlx_set_mouse_pos(wind->mlx, WIDTH / 2, HEIGHT / 2);
	}
}

int	get_pixel_color(mlx_texture_t *tex, t_vline *line)
{
	return (get_rgba(tex->pixels[64 * line->tex.y * 4 + line->tex.x * 4], \
				tex->pixels[64 * line->tex.y * 4 + line->tex.x * 4 + 1], \
				tex->pixels[64 * line->tex.y * 4 + line->tex.x * 4 + 2], \
				tex->pixels[64 * line->tex.y * 4 + line->tex.x * 4
				+ 3]));
}

void	fill_buff(t_global *glob, t_ray ray, int x, t_vline *line)
{
	double			step;
	double			tex_pos;
	int				i;
	mlx_texture_t	*tex;

	step = 1.0 * glob->scene->text_arr[2]->height / line->height;
	tex_pos = (line->start - HEIGHT / 2 + line->height / 2) * step;
	tex = glob->scene->text_arr[tex_num(ray.side, ray.dir.x, ray.dir.y)];
	i = line->start;
	while (line->start < line->end)
	{
		line->tex.y = (int)tex_pos & (64 - 1);
		tex_pos += step;
		line->height = get_pixel_color(tex, line);
		if (ray.side == 1)
			line->height = (line->height >> 1) & 8355711;
		glob->buffer[x][line->start] = line->height;
		line->start++;
		i++;
	}
	while (i < HEIGHT)
		glob->buffer[x][i++] = get_rgba(glob->scene->f[0], glob->scene->f[1],
				glob->scene->f[2], 255);
}

void	hit_process(t_global *glob, t_ray ray, int x)
{
	t_vline	line;
	int		i;

	line.height = (int)(HEIGHT * 0.6 / ray.perpWallDist);
	line.start = -line.height / 2 + HEIGHT / 2;
	if (line.start < 0)
		line.start = 0;
	line.end = line.height / 2 + HEIGHT / 2;
	if (line.end >= HEIGHT)
		line.end = HEIGHT - 1;
	if (ray.side == 0)
		ray.wall_x = glob->wind->pos.y + ray.perpWallDist * ray.dir.y;
	else
		ray.wall_x = glob->wind->pos.x + ray.perpWallDist * ray.dir.x;
	ray.wall_x = ray.wall_x - (double)((int)ray.wall_x);
	line.tex.x = (int)(ray.wall_x * (double)64);
	if ((ray.side == 0 && ray.dir.x > 0) || (ray.side == 1 && ray.dir.y < 0))
		line.tex.x = 64 - line.tex.x - 1;
	i = 0;
	while (i < line.start)
		glob->buffer[x][i++] = get_rgba(glob->scene->c[0], glob->scene->c[1],
				glob->scene->c[2], 255);
	fill_buff(glob, ray, x, &line);
}

void	ray_pos_dir(t_window *wind, t_ray *ray)
{
	ray->dir.y = wind->dir.y + wind->plan.y * ray->cam.x;
	ray->sqr_map.x = (int)wind->pos.x;
	ray->sqr_map.y = (int)wind->pos.y;
	ray->dist.x = DBL_MAX;
	if (ray->dir.x)
		ray->dist.x = fabs(1.0 / ray->dir.x);
	ray->dist.y = DBL_MAX;
	if (ray->dir.y)
		ray->dist.y = fabs(1.0 / ray->dir.y);
	ray->step.x = -1.0;
	ray->sideDist.x = (wind->pos.x - ray->sqr_map.x) * ray->dist.x;
	if (ray->dir.x >= 0)
	{
		ray->step.x = 1.0;
		ray->sideDist.x = (ray->sqr_map.x + 1.0 - wind->pos.x) * ray->dist.x;
	}
	ray->step.y = -1.0;
	ray->sideDist.y = (wind->pos.y - ray->sqr_map.y) * ray->dist.y;
	if (ray->dir.y >= 0)
	{
		ray->step.y = 1.0;
		ray->sideDist.y = (ray->sqr_map.y + 1.0 - wind->pos.y) * ray->dist.y;
	}
}

int	check_for_wall(char **matrix_map, t_ray *ray)
{
	if (ray->sideDist.x < ray->sideDist.y)
	{
		ray->sideDist.x += ray->dist.x;
		ray->sqr_map.x += (int)ray->step.x;
		ray->side = 0;
	}
	else
	{
		ray->sideDist.y += ray->dist.y;
		ray->sqr_map.y += (int)ray->step.y;
		ray->side = 1;
	}
	if (matrix_map[(int)ray->sqr_map.x][(int)ray->sqr_map.y] == '1')
		return (1);
	return (0);
}

void	key_move(t_global *glob)
{
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_W))
		move(glob->wind->dir.x, glob->wind->dir.y, glob);
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_S))
		move(-glob->wind->dir.x, -glob->wind->dir.y, glob);
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_A))
		move(-glob->wind->dir.y, glob->wind->dir.x, glob);
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_D))
		move(glob->wind->dir.y, -glob->wind->dir.x, glob);
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_LEFT))
		mouse_rotate(glob->wind, 0, 0);
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_RIGHT))
		mouse_rotate(glob->wind, WIDTH, 0);
}

void	raycast(void *globb)
{
	int			x;
	t_ray		ray;
	t_global	*glob;

	glob = globb;
	mouse_rotate(glob->wind, 69, 1);
	key_move(glob);
	x = 0;
	while (x < WIDTH)
	{
		ray.cam.x = ((2 * x) / (double)WIDTH) - 1;
		ray.dir.x = glob->wind->dir.x + glob->wind->plan.x * ray.cam.x;
		ray_pos_dir(glob->wind, &ray);
		while (!check_for_wall(glob->scene->matrix_map, &ray))
			;
		if (ray.side == 0)
			ray.perpWallDist = (ray.sideDist.x - ray.dist.x);
		else
			ray.perpWallDist = (ray.sideDist.y - ray.dist.y);
		hit_process(glob, ray, x);
		x++;
	}
	draw_buff(glob, glob->buffer);
}

void	set_dir(t_window *wind, char c)
{
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

void	set_plan(t_window *wind, char c)
{
	if (c == 'N')
	{
		wind->plan.x = 0;
		wind->plan.y = 1;
	}
	if (c == 'S')
	{
		wind->plan.x = 0;
		wind->plan.y = -1;
	}
	if (c == 'W')
	{
		wind->plan.x = -1;
		wind->plan.y = 0;
	}
	if (c == 'E')
	{
		wind->plan.x = 1;
		wind->plan.y = 0;
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
		while (j < (int)ft_strlen(scene->matrix_map[i]))
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
	set_dir(wind, c);
	set_plan(wind, c);
}
