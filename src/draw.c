/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:24:04 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/20 19:14:17 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	my_mlx_pixel_put(mlx_image_t *image, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// void	draw_floceil(int x, int start, int end, t_window *wind, int color)

void	draw_wall(int x, int start, int end, t_window *wind, int color)
{
    int y;

    y = 0;
    // while (y < start)
    //     my_mlx_pixel_put(wind->image, x, y++, 0xFFFFFF);
	while (start <= end)
	{
		printf("runing %d, %d, %d\n", start, end, color);
		mlx_put_pixel(wind->image, x, start, color);
		//my_mlx_pixel_put(wind->image, x, start, color);
		start++;
        y++;
	}
    // while (y < height)
    //     //my_mlx_pixel_put(wind->image, x, y++, 0x000000);

}