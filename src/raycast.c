/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:47:25 by nkolle            #+#    #+#             */
/*   Updated: 2022/12/05 17:08:49 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	line.height = (int)(HEIGHT * 0.6 / ray.perpwalldist);
	line.start = -line.height / 2 + HEIGHT / 2;
	if (line.start < 0)
		line.start = 0;
	line.end = line.height / 2 + HEIGHT / 2;
	if (line.end >= HEIGHT)
		line.end = HEIGHT - 1;
	if (ray.side == 0)
		ray.wall_x = glob->wind->pos.y + ray.perpwalldist * ray.dir.y;
	else
		ray.wall_x = glob->wind->pos.x + ray.perpwalldist * ray.dir.x;
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
	ray->sidedist.x = (wind->pos.x - ray->sqr_map.x) * ray->dist.x;
	if (ray->dir.x >= 0)
	{
		ray->step.x = 1.0;
		ray->sidedist.x = (ray->sqr_map.x + 1.0 - wind->pos.x) * ray->dist.x;
	}
	ray->step.y = -1.0;
	ray->sidedist.y = (wind->pos.y - ray->sqr_map.y) * ray->dist.y;
	if (ray->dir.y >= 0)
	{
		ray->step.y = 1.0;
		ray->sidedist.y = (ray->sqr_map.y + 1.0 - wind->pos.y) * ray->dist.y;
	}
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
			ray.perpwalldist = (ray.sidedist.x - ray.dist.x);
		else
			ray.perpwalldist = (ray.sidedist.y - ray.dist.y);
		hit_process(glob, ray, x);
		x++;
	}
	draw_buff(glob, glob->buffer);
}
