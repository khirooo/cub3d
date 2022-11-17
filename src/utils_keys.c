/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:00:02 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/17 12:27:27 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void    Right_Arrow(t_global *glob)
// {
// 	if (glob->wind->dir.x == -1)
//     {
//         printf("North facing\n");
// 		glob->wind->dir.x += 1;
// 		glob->wind->dir.y += 1;
//     }
// 	else if (glob->wind->dir.x == 0 && glob->wind->dir.y == 1)
//     {
//         printf("East facing\n");
//         glob->wind->dir.x += 1;
// 		glob->wind->dir.y -= 1;   
//     }
//     else if (glob->wind->dir.x == 1)
//     {
//         printf("South facing\n");
//         glob->wind->dir.x -= 1;
// 		glob->wind->dir.y -= 1;
//     }
//     else
//     {
//         printf("West facing\n");
//         glob->wind->dir.x -= 1;
// 		glob->wind->dir.y += 1;
//     }
// }

// void    Left_Arrow(t_global *glob)
// {
// 	if (glob->wind->dir.x == -1)
//     {
// 		glob->wind->dir.x += 1;
// 		glob->wind->dir.y -= 1;
//     }
// 	else if (glob->wind->dir.x == 0 && glob->wind->dir.y == -1)
//     {
//         glob->wind->dir.x += 1;
// 		glob->wind->dir.y += 1;   
//     }
//     else if (glob->wind->dir.x == 1)
//     {
//         glob->wind->dir.x -= 1;
// 		glob->wind->dir.y += 1;
//     }
//     else
//     {
//         glob->wind->dir.x -= 1;
// 		glob->wind->dir.y -= 1;
//     }
// }