/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:09:55 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/05 20:08:03 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_err(char *err)
{
	write(2, err, ft_strlen(err));
}

int	main(int argc, char *argv[])
{
	t_scene	*scene;

	if (argc < 2)
	{
		print_err("error: provide a scene discription file\n");
		return (1);
	}
	scene = parse_scene_file(argv[1]);
	if (!scene || parse_map(scene))
		return (1);
	play_music();
	open_window(scene);
	return (0);
}
