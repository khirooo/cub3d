/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:14:08 by nkolle            #+#    #+#             */
/*   Updated: 2022/12/05 16:14:36 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
