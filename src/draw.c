/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:24:04 by nkolle            #+#    #+#             */
/*   Updated: 2022/12/05 16:44:04 by nkolle           ###   ########.fr       */
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

int	get_pixel_color(mlx_texture_t *tex, t_vline *line)
{
	return (get_rgba(tex->pixels[64 * line->tex.y * 4 + line->tex.x * 4], \
				tex->pixels[64 * line->tex.y * 4 + line->tex.x * 4 + 1], \
				tex->pixels[64 * line->tex.y * 4 + line->tex.x * 4 + 2], \
				tex->pixels[64 * line->tex.y * 4 + line->tex.x * 4
				+ 3]));
}
