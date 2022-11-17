/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:24:04 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/17 18:24:25 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		convert_rgb(int *arr)
{
	return ((arr[0] & 0xff) << 16) + ((arr[1] & 0xff) << 8) + (arr[2] & 0xff);
}

void	draw_wall(int x, int start, int end, t_window *wind, int color, t_global *glob)
{
    int y;

    y = 0;
    while (y < start)
        my_mlx_pixel_put(wind->image, x, y++, convert_rgb(glob->scene->c));
	while (start <= end)
	{
		my_mlx_pixel_put(wind->image, x, start, color);
		start++;
        y++;
	}
    while (y < height)
        my_mlx_pixel_put(wind->image, x, y++, convert_rgb(glob->scene->f));


	


} 