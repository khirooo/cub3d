/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:36:56 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/28 03:42:44 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	add_to_map(t_scene *scene, char *line)
{
	int	i;

	if (scene->c == NULL || scene->f == NULL || scene->ea == NULL
		|| scene->no == NULL || scene->so == NULL || scene->we == NULL)
		return (1);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (scene->str_map != NULL && is_empty(line))
		return (1);
	scene->str_map = ft_strjoin_withnull(scene->str_map, line, 1);
	return (0);
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

void	load_textures(t_scene *scene)
{
	scene->text_arr = malloc(sizeof(mlx_texture_t *) * 8);
	scene->text_arr[0] = mlx_load_png(scene->no);
	scene->text_arr[1] = mlx_load_png(scene->so);
	scene->text_arr[2] = mlx_load_png(scene->we);
	scene->text_arr[3] = mlx_load_png(scene->ea);
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
