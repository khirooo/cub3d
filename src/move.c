/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:25:32 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/20 17:02:02 by kfergani         ###   ########.fr       */
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
	if (keycode == 123)
	{
		double	old_dir_x = glob->wind->dir.x;
		glob->wind->dir.x = glob->wind->dir.x * cosf(0.05) - glob->wind->dir.y * sinf(0.05);
		glob->wind->dir.y = old_dir_x * sinf(0.05) + glob->wind->dir.y * cosf(0.05);
		double	old_plan_x = glob->wind->plan.x;
		glob->wind->plan.x = glob->wind->plan.x * cosf(0.05) - glob->wind->plan.y * sinf(0.05);
      	glob->wind->plan.y = glob->wind->plan.x * sinf(0.05) + glob->wind->plan.y * cosf(0.05);
		//mlx_mouse_move(glob->wind->win, width / 2, height / 2);
		printf("pos(x, y)= %f, %f\ndir: %f, %f\n",  glob->wind->pos.x,  glob->wind->pos.y, glob->wind->dir.x, glob->wind->dir.y);
	}
	if (keycode == 124)
	{
		double	old_dir_x = glob->wind->dir.x;
		glob->wind->dir.x = glob->wind->dir.x * cosf(-0.05) - glob->wind->dir.y * sinf(-0.05);
		glob->wind->dir.y = old_dir_x * sinf(-0.05) + glob->wind->dir.y * cosf(-0.05);
		double	old_plan_x = glob->wind->plan.x;
		glob->wind->plan.x = glob->wind->plan.x * cosf(-0.05) - glob->wind->plan.y * sinf(-0.05);
      	glob->wind->plan.y = glob->wind->plan.x * sinf(-0.05) + glob->wind->plan.y * cosf(-0.05);
	}
	printf("keycode: %d\n", keycode);
    if (keycode == KEY_ESC)
        exit(0);
	return (0);
}