/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:42:38 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/04 19:36:44 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int	check_map(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while(j < ft_strlen(map[i]))
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ')
				return (1);
			if (map[i][j] == '0' && (i == 0 || !map[i + 1]
				|| ft_strlen(map[i - 1]) <= j || map[i - 1][j] == ' '
				|| ft_strlen(map[i + 1]) <= j || map[i + 1][j] == ' '
				|| j == 0 || !map[i][j + 1] || map[i][j - 1] == ' '
				|| map[i][j + 1] == ' '))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int check_rgb(int *rgb)
{
	int	i;

	if (!rgb)
		return (1);
	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (1);
		i++;
	}
	return (0);
}

int	parse_map(t_scene *scene)
{
	scene->matrix_map = ft_split(scene->str_map, '\n');
	if (check_map(scene->matrix_map) || check_rgb(scene->f) \
		|| check_rgb(scene->c))
	{
		printf("Error: not valid map\n");
		return (1);
	}
	return (0);
}