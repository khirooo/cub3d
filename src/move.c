/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:25:32 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/17 13:11:28 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    fck_norm(t_global *glob)
{
		glob->wind->pos.y += glob->wind->dir.y;
		glob->wind->pos.x += glob->wind->dir.x;
}

void    fck_norm1(t_global *glob)
{
		glob->wind->pos.y -= glob->wind->dir.y;
		glob->wind->pos.x -= glob->wind->dir.x;
}

int	key_hook(int keycode, t_global *glob)
{
	if (keycode == KEY_W &&
		glob->scene->matrix_map[(int)glob->wind->pos.x - 2][(int)glob->wind->pos.y] != '1')
            fck_norm(glob);
	if (keycode == KEY_S &&
		glob->scene->matrix_map[(int)glob->wind->pos.x + 2][(int)glob->wind->pos.y] != '1')
            fck_norm1(glob);
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
    if (keycode == KEY_ESC)
        exit(0);
	return (0);
}