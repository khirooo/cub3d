/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:07:08 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/04 19:12:48 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

// char	*get_n_word(char *line)
// {
// 	int		i;
// 	char	**words;

// 	words =  ft_split(line, ' ');
// 	i = 0;
// 	while (words[i] == ' ')
// 	{
// 		/* code */
// 	}
	
	
	
// }

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

void	print_map(char *map)
{
	char	**lines;
	int		i;

	lines = ft_split(map, '\n');
	i = 0;
	while (lines[i])
	{
		printf("%s\n", lines[i]);
		i++;
	}
	free_dp(lines);
}

void	print_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("%d, ", rgb[i]);
		i++;
	}
	printf("\n");
}

void	print_scene(t_scene *scene)
{
	printf("NO: %s\n", scene->no);
	printf("SO: %s\n", scene->so);
	printf("WE: %s\n", scene->we);
	printf("EA: %s\n", scene->ea);
	printf("F ");
	print_rgb(scene->f);
	printf("C ");
	print_rgb(scene->c);
	print_map(scene->str_map);
}