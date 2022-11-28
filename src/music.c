/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:04:56 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/28 03:56:23 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_music(void)
{
	// system("zsh -c \"while true; do; afplay ./track/long_ver.mp3; done &\"");
	system("zsh -c \"afplay ./track/long_ver.mp3 &\"");
}
