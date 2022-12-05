/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:45:13 by nkolle            #+#    #+#             */
/*   Updated: 2022/12/05 16:45:24 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
