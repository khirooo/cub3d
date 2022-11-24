/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:39:52 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/23 18:03:41 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_char_matrix(char **m)
{
	int	i;

	i = 0;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
	free(m);
}

void	free_scene(t_scene *scene)
{
	free(scene->no);
	free(scene->so);
	free(scene->we);
	free(scene->ea);
	free(scene->f);
	free(scene->c);
	free(scene->str_map);
	free_char_matrix(scene->matrix_map);
	free(scene->text_arr);
	free(scene);
}

void	free_glob(t_global *glob)
{
	free_scene(glob->scene);
	mlx_delete_image(glob->wind->mlx, glob->wind->image);
}

