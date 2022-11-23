/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:24:04 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/23 15:35:41 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int createRGB(int r, int g, int b)
{   
    return (r << 24 | g << 16 | b << 8 | 255);
}

void	draw_wall(int x, int start, int end, t_window *wind, int color, t_global *glob)
{
    int y;

    y = 0;
    while (y < start)
        mlx_put_pixel(wind->image, x, y++, createRGB(glob->scene->f[0], glob->scene->f[1], glob->scene->f[2]));
	while (start <= end)
	{
		//printf("runing %d, %d, %d\n", start, end, color);
		mlx_put_pixel(wind->image, x, start, color);
		//my_mlx_pixel_put(wind->image, x, start, color);
		start++;
        y++;
	}
    while (y < HEIGHT)
        mlx_put_pixel(wind->image, x, y++, createRGB(glob->scene->c[0], glob->scene->c[1], glob->scene->c[2]));

}