/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:04:56 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/24 17:49:28 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    play_music()
{
    // system("zsh -c \"while true; do; afplay ./track/long_ver.mp3; done &\"");
    system("zsh -c \"afplay ./track/long_ver.mp3 &\"");
}