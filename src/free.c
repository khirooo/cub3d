/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:39:52 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/05 20:06:10 by nkolle           ###   ########.fr       */
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

void	change_scene(t_global *glob)
{
	if (glob->mode == 1)
	{
		glob->scene->c = get_rgb(ft_strdup("0,0,0"));
		glob->scene->f = get_rgb(ft_strdup("0,0,0"));
		glob->scene->no = ft_strdup("./textures/Wall/lightspeed.png");
		glob->scene->so = ft_strdup("./textures/Wall/lightspeed.png");
		glob->scene->we = ft_strdup("./textures/Wall/arrows_right.png");
		glob->scene->ea = ft_strdup("./textures/Wall/arrows_right.png");
		system("zsh -c \"afplay ./track/Nightmode.mp3 &\"");
		glob->mode = 2;
	}
	else
	{
		glob->scene->c = get_rgb(ft_strdup("135,206,235"));
		glob->scene->f = get_rgb(ft_strdup("34,139,34"));
		glob->scene->no = ft_strdup("./textures/Wall/forest.png");
		glob->scene->so = ft_strdup("./textures/Wall/forest.png");
		glob->scene->we = ft_strdup("./textures/Wall/forest.png");
		glob->scene->ea = ft_strdup("./textures/Wall/forest.png");
		system("zsh -c \"afplay ./track/chillmode.mp3 &\"");
		glob->mode = 1;
	}
}

void	switch_scene(t_global *glob)
{
	free(glob->scene->no);
	free(glob->scene->so);
	free(glob->scene->we);
	free(glob->scene->ea);
	free(glob->scene->f);
	free(glob->scene->c);
	system("killall afplay");
	change_scene(glob);
	load_textures(glob->scene);
}
