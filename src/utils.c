/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:36:56 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/05 16:59:23 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_n_word(t_scene *scene, char *s, int n)
{
	char	*word;
	char	**words;
	int		i;

	words = ft_split(s, ' ');
	i = 0;
	while (words[i] && *words[i] != '\n')
		i++;
	if (i != 2 && (!ft_strcmp(words[0], "NO") || !ft_strcmp(words[0], "EA")
			|| !ft_strcmp(words[0], "SO") || !ft_strcmp(words[0], "WE")
			|| !ft_strcmp(words[0], "F") || !ft_strcmp(words[0], "C")))
		return (NULL);
	if (scene->c && scene->f && scene->ea && scene->no && scene->so
		&& scene->we)
		word = ft_strdup("map");
	else if (i != 2)
		return (NULL);
	else
		word = ft_strtrim(words[n - 1], "\n");
	free_dp(words);
	return (word);
}

int	check_walls_texture(t_scene *scene, char *line, char *type)
{
	if ((!ft_strcmp(type, "NO") && scene->no != NULL) || (!ft_strcmp(type, "EA")
			&& scene->ea != NULL) || (!ft_strcmp(type, "WE")
			&& scene->we != NULL) || (!ft_strcmp(type, "SO")
			&& scene->so != NULL) || (!ft_strcmp(type, "F") && scene->f != NULL)
		|| (!ft_strcmp(type, "C") && scene->c != NULL))
	{
		free(type);
		return (1);
	}
	if (!ft_strcmp(type, "NO"))
		scene->no = get_n_word(scene, line, 2);
	else if (!ft_strcmp(type, "EA"))
		scene->ea = get_n_word(scene, line, 2);
	else if (!ft_strcmp(type, "WE"))
		scene->we = get_n_word(scene, line, 2);
	else if (!ft_strcmp(type, "SO"))
		scene->so = get_n_word(scene, line, 2);
	if (!ft_strcmp(type, "F"))
		scene->f = get_rgb(get_n_word(scene, line, 2));
	else if (!ft_strcmp(type, "C"))
		scene->c = get_rgb(get_n_word(scene, line, 2));
	return (0);
}

int	update_scene(t_scene *scene, char *line)
{
	char	*type;

	type = get_n_word(scene, line, 1);
	if (!type)
		return (1);
	if (!ft_strcmp(type, "map"))
	{
		free(type);
		return (add_to_map(scene, line));
	}
	if (check_walls_texture(scene, line, type) == 0)
		return (0);
	else
		return (1);
}

t_scene	*fill_scene(t_scene *scene, char *line, int fd)
{
	while (line)
	{
		if (scene->str_map || !is_empty(line))
		{
			if (update_scene(scene, line))
			{
				print_err("error: scene file is not valid\n");
				return (NULL);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	return (scene);
}

t_scene	*parse_scene_file(char *file)
{
	int		fd;
	t_scene	*scene;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_err("error: could not open scene description file\n");
		return (NULL);
	}
	if (init_scene(&scene))
	{
		print_err("error: malloc fail\n");
		return (NULL);
	}
	line = get_next_line(fd);
	if (!fill_scene(scene, line, fd))
		return (NULL);
	load_textures(scene);
	return (scene);
}
