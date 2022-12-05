/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:07:08 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/05 16:55:21 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty(char *line)
{
	if (!*line)
		return (1);
	while (*line && *line == ' ')
		line++;
	if (!*line || *line == '\n')
		return (1);
	return (0);
}

void	free_dp(char **i)
{
	if (!i)
		return ;
	while (*i)
	{
		free(*i);
		*i = NULL;
		i++;
	}
}

void	load_textures(t_scene *scene)
{
	scene->text_arr = malloc(sizeof(mlx_texture_t *) * 8);
	scene->text_arr[0] = mlx_load_png(scene->no);
	scene->text_arr[1] = mlx_load_png(scene->so);
	scene->text_arr[2] = mlx_load_png(scene->we);
	scene->text_arr[3] = mlx_load_png(scene->ea);
}

int	*get_rgb(char *line)
{
	int		*int_rgb;
	char	**char_rgb;
	int		i;

	char_rgb = ft_split(line, ',');
	free(line);
	int_rgb = (int *)malloc(3 * sizeof(int));
	if (!char_rgb || !int_rgb)
		return (NULL);
	i = 0;
	while (i < 3 && char_rgb[i] != NULL)
	{
		int_rgb[i] = ft_atoi(char_rgb[i]);
		i++;
	}
	if (char_rgb[i] != NULL || i != 3)
		return (NULL);
	return (int_rgb);
}

int	init_scene(t_scene **scene)
{
	(*scene) = (t_scene *)malloc(sizeof(t_scene));
	if (!(*scene))
		return (1);
	(*scene)->ea = NULL;
	(*scene)->so = NULL;
	(*scene)->we = NULL;
	(*scene)->no = NULL;
	(*scene)->f = NULL;
	(*scene)->c = NULL;
	(*scene)->str_map = NULL;
	return (0);
}
// void	print_map(char *map)
// {
// 	char	**lines;
// 	int		i;

// 	lines = ft_split(map, '\n');
// 	i = 0;
// 	while (lines[i])
// 	{
// 		printf("%s\n", lines[i]);
// 		i++;
// 	}
// 	free_dp(lines);
// }

// void	print_rgb(int *rgb)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 3)
// 	{
// 		printf("%d, ", rgb[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

// void	print_scene(t_scene *scene)
// {
// 	printf("NO: %s\n", scene->no);
// 	printf("SO: %s\n", scene->so);
// 	printf("WE: %s\n", scene->we);
// 	printf("EA: %s\n", scene->ea);
// 	printf("F ");
// 	print_rgb(scene->f);
// 	printf("C ");
// 	print_rgb(scene->c);
// 	print_map(scene->str_map);
// }
