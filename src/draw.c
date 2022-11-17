/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:24:04 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/17 13:19:17 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void	draw_floceil(int x, int start, int end, t_window *wind, int color)

void	draw_wall(int x, int start, int end, t_window *wind, int color)
{
    int y;

    y = 0;
    while (y < start)
        my_mlx_pixel_put(wind->image, x, y++, 0xFFFFFF);
	while (start <= end)
	{
		my_mlx_pixel_put(wind->image, x, start, color);
		start++;
        y++;
	}
    while (y < height)
        my_mlx_pixel_put(wind->image, x, y++, 0x000000);

}