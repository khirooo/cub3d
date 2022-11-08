/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:09:55 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/05 21:38:26 by kfergani         ###   ########.fr       */
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
	print_scene(scene);
	open_window(scene);
	return (0);
}


// #define screenWidth 640
// #define screenHeight 480
// #define mapWidth 24
// #define mapHeight 24

// int worldMap[mapWidth][mapHeight]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

// int main(int argc, char *argv[])
// {
//   double posX = 22, posY = 12;
//   double dirX = -1, dirY = 0;
//   double planeX = 0, planeY = 0.66;

//   double time = 0;
//   double oldTime = 0;

//   screen(screenWidth, screenHeight, 0, "Raycaster");
//   while(!done())
//   {
//     for(int x = 0; x < w; x++)
//     {
//       double cameraX = 2 * x / (double)w - 1;
//       double rayDirX = dirX + planeX * cameraX;
//       double rayDirY = dirY + planeY * cameraX;
//       int mapX = int(posX);
//       int mapY = int(posY);

//       double sideDistX;
//       double sideDistY;

//       double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
//       double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

//       double perpWallDist;

//       int stepX;
//       int stepY;

//       int hit = 0;
//       int side;
//       if(rayDirX < 0)
//       {
//         stepX = -1;
//         sideDistX = (posX - mapX) * deltaDistX;
//       }
//       else
//       {
//         stepX = 1;
//         sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//       }
//       if(rayDirY < 0)
//       {
//         stepY = -1;
//         sideDistY = (posY - mapY) * deltaDistY;
//       }
//       else
//       {
//         stepY = 1;
//         sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//       }
//       while(hit == 0)
//       {
//         if(sideDistX < sideDistY)
//         {
//           sideDistX += deltaDistX;
//           mapX += stepX;
//           side = 0;
//         }
//         else
//         {
//           sideDistY += deltaDistY;
//           mapY += stepY;
//           side = 1;
//         }
//         if(worldMap[mapX][mapY] > 0) hit = 1;
//       }
     
//       if(side == 0) perpWallDist = (sideDistX - deltaDistX);
//       else          perpWallDist = (sideDistY - deltaDistY);

//       int lineHeight = (int)(h / perpWallDist);

//       int drawStart = -lineHeight / 2 + h / 2;
//       if(drawStart < 0) drawStart = 0;
//       int drawEnd = lineHeight / 2 + h / 2;
//       if(drawEnd >= h) drawEnd = h - 1;

//       ColorRGB color;
//       switch(worldMap[mapX][mapY])
//       {
//         case 1:  color = RGB_Red;    break;
//         case 2:  color = RGB_Green;  break;
//         case 3:  color = RGB_Blue;   break;
//         case 4:  color = RGB_White;  break;
//         default: color = RGB_Yellow; break;
//       }

//       if(side == 1) {color = color / 2;}

//       verLine(x, drawStart, drawEnd, color);
//     }
//     oldTime = time;
//     time = getTicks();
//     double frameTime = (time - oldTime) / 1000.0;
//     print(1.0 / frameTime);
//     redraw();
//     cls();

//     double moveSpeed = frameTime * 5.0;
//     double rotSpeed = frameTime * 3.0;
//     readKeys();

//     if(keyDown(SDLK_UP))
//     {
//       if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
//       if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
//     }

//     if(keyDown(SDLK_DOWN))
//     {
//       if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
//       if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
//     }

//     if(keyDown(SDLK_RIGHT))
//     {

//       double oldDirX = dirX;
//       dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//       dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//       double oldPlaneX = planeX;
//       planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//       planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//     }

//     if(keyDown(SDLK_LEFT))
//     {
//       double oldDirX = dirX;
//       dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//       dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//       double oldPlaneX = planeX;
//       planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//       planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//     }
//   }
// }
