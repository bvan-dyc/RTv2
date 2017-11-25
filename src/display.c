/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-dyc <bvan-dyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:09:07 by bvan-dyc          #+#    #+#             */
/*   Updated: 2017/10/31 17:59:25 by bvan-dyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/rtv1.h"

void		display_campos(t_env *e)
{
	mlx_string_put(e->mlx, e->win, WIN_W - 230, 50, PURPLE, "SCENE DATA");
	shadow_print(e, WIN_W - 230, 70, "CAMPOS.");
	shadow_print(e, WIN_W - 230, 90, "CAMPOS.");
	shadow_print(e, WIN_W - 230, 110, "CAMPOS.");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 70, RED, "x");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 90, GREEN, "y");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 110, BLUE, "z");
	shadow_print(e, WIN_W - 130, 70, ft_itoa(e->campos.x));
	shadow_print(e, WIN_W - 130, 90, ft_itoa(e->campos.y));
	shadow_print(e, WIN_W - 130, 110, ft_itoa(e->campos.z));
}

void		display_camdir(t_env *e)
{
	shadow_print(e, WIN_W - 230, 140, "CAMDIR.");
	shadow_print(e, WIN_W - 230, 160, "CAMDIR.");
	shadow_print(e, WIN_W - 230, 180, "CAMDIR.");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 140, RED, "x");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 160, GREEN, "y");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 180, BLUE, "z");
	shadow_print(e, WIN_W - 130, 140, ft_itoa(e->camdir.x * 100));
	shadow_print(e, WIN_W - 130, 160, ft_itoa(e->camdir.y * 100));
	shadow_print(e, WIN_W - 130, 180, ft_itoa(e->camdir.z * 100));
}

void		display_scenedata(t_env *e)
{
	shadow_print(e, WIN_W - 230, 210, "SHADOWS:");
	if (e->disableshadow == 0)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 210, BLUE, "DEFAULT");
	if (e->disableshadow == 1)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 210, RED, "OFF");
	shadow_print(e, WIN_W - 230, 230, "REFLECT:");
	shadow_print(e, WIN_W - 130, 230, ft_itoa(e->maxlvl));
}

void		display_filter(t_env *e)
{
	shadow_print(e, WIN_W - 230, 250, "FILTER:");
	if (e->filtermode == DEFAULT)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 250, RED, "RGB");
	if (e->filtermode == GRAYSCALE)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 250, DGRAY, "GRAYSCALE");
	if (e->filtermode == SEPIA)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 250, BROWN, "SEPIA");
	if (e->filtermode == INVERTED)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 250, BLUE, "INVERTED");
}

void		display_itempos(t_env *e)
{
	shadow_print(e, WIN_W - 230, 370, "ITEMPOS.");
	shadow_print(e, WIN_W - 230, 390, "ITEMPOS.");
	shadow_print(e, WIN_W - 230, 410, "ITEMPOS.");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 370, RED, "x");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 390, GREEN, "y");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 410, BLUE, "z");
	shadow_print(e, WIN_W - 130, 370, ft_itoa(e->items[e->select].pos.x));
	shadow_print(e, WIN_W - 130, 390, ft_itoa(e->items[e->select].pos.y));
	shadow_print(e, WIN_W - 130, 410, ft_itoa(e->items[e->select].pos.z));
}

void		display_itemrgb(t_env *e)
{
	mlx_string_put(e->mlx, e->win, WIN_W - 230, 280, PURPLE, "ITEM DATA");
	shadow_print(e, WIN_W - 230, 300, "ITEM.");
	shadow_print(e, WIN_W - 230, 320, "ITEM.");
	shadow_print(e, WIN_W - 230, 340, "ITEM.");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 300, RED, "R");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 320, GREEN, "G");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 340, BLUE, "B");
	shadow_print(e, WIN_W - 130, 300, ft_itoa(e->items[e->select].colour.red));
	shadow_print(e, WIN_W - 130, 320, ft_itoa(e->items[e->select].colour.green));
	shadow_print(e, WIN_W - 130, 340, ft_itoa(e->items[e->select].colour.blue));
}

void		display_itemname(t_env *e)
{
	if (e->items[e->select].type == SPHERE)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 280, PURPLE, "(SPHERE)");
	if (e->items[e->select].type == CYL)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 280, PURPLE, "(CYLINDER)");
	if (e->items[e->select].type == CONE)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 280, PURPLE, "(CONE)");
	if (e->items[e->select].type == TRIANGLE)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 280, PURPLE, "(TRIANGLE)");
	if (e->items[e->select].type == PLANE)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 280, PURPLE, "(PLANE)");
	if (e->items[e->select].type == DISK)
		mlx_string_put(e->mlx, e->win, WIN_W - 130, 280, PURPLE, "(DISK)");
}

void		display_itemdir(t_env *e)
{
	shadow_print(e, WIN_W - 230, 490, "ITEMDIR.");
	shadow_print(e, WIN_W - 230, 510, "ITEMDIR.");
	shadow_print(e, WIN_W - 230, 530, "ITEMDIR.");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 490, RED, "x");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 510, GREEN, "y");
	mlx_string_put(e->mlx, e->win, WIN_W - 150, 530, BLUE, "z");
	shadow_print(e, WIN_W - 130, 490, ft_itoa((e->items[e->select].dir.x * 100)));
	shadow_print(e, WIN_W - 130, 510, ft_itoa((e->items[e->select].dir.y * 100)));
	shadow_print(e, WIN_W - 130, 530, ft_itoa((e->items[e->select].dir.z * 100)));
}

void		display_itemmisc(t_env *e)
{
	if (e->items[e->select].type != PLANE && e->items[e->select].type != TRIANGLE)
	{
		shadow_print(e, WIN_W - 230, 440, "SIZE");
		shadow_print(e, WIN_W - 130, 440, ft_itoa(e->items[e->select].size));
		shadow_print(e, WIN_W - 230, 460, "REFLECT");
		shadow_print(e, WIN_W - 130, 460, ft_itoa(e->items[e->select].reflection));
	}
}

void		display_triangle(t_env *e)
{
		shadow_print(e, WIN_W - 230, 370, "ITEMp1.");
		shadow_print(e, WIN_W - 230, 390, "ITEMp1.");
		shadow_print(e, WIN_W - 230, 410, "ITEMp1.");
		mlx_string_put(e->mlx, e->win, WIN_W - 150, 370, RED, "x");
		mlx_string_put(e->mlx, e->win, WIN_W - 150, 390, GREEN, "y");
		mlx_string_put(e->mlx, e->win, WIN_W - 150, 410, BLUE, "z");
		shadow_print(e, WIN_W - 130, 370, ft_itoa(e->items[e->select].p1.x));
		shadow_print(e, WIN_W - 130, 390, ft_itoa(e->items[e->select].p1.y));
		shadow_print(e, WIN_W - 130, 410, ft_itoa(e->items[e->select].p1.z));
		shadow_print(e, WIN_W - 230, 430, "ITEMP2.");
		shadow_print(e, WIN_W - 230, 450, "ITEMP2.");
		shadow_print(e, WIN_W - 230, 470, "ITEMP2.");
		mlx_string_put(e->mlx, e->win, WIN_W - 150, 430, RED, "x");
		mlx_string_put(e->mlx, e->win, WIN_W - 150, 450, GREEN, "y");
		mlx_string_put(e->mlx, e->win, WIN_W - 150, 470, BLUE, "z");
		shadow_print(e, WIN_W - 130, 430, ft_itoa(e->items[e->select].p2.x));
		shadow_print(e, WIN_W - 130, 450, ft_itoa(e->items[e->select].p2.y));
		shadow_print(e, WIN_W - 130, 470, ft_itoa(e->items[e->select].p2.z));
		shadow_print(e, WIN_W - 230, 490, "ITEMP3.");
		shadow_print(e, WIN_W - 230, 510, "ITEMP3.");
		shadow_print(e, WIN_W - 230, 530, "ITEMP3.");
		mlx_string_put(e->mlx, e->win, WIN_W - 150, 490, RED, "x");
		mlx_string_put(e->mlx, e->win, WIN_W - 150, 510, GREEN, "y");
		mlx_string_put(e->mlx, e->win, WIN_W - 150, 530, BLUE, "z");
		shadow_print(e, WIN_W - 130, 490, ft_itoa(e->items[e->select].p3.x));
		shadow_print(e, WIN_W - 130, 510, ft_itoa(e->items[e->select].p3.y));
		shadow_print(e, WIN_W - 130, 530, ft_itoa(e->items[e->select].p3.z));
}

void		display_mode(t_env *e)
{
	shadow_print(e, WIN_W - 220, WIN_H - 140, "MODE:");
	if (e->mode == COLOR)
		mlx_string_put(e->mlx, e->win, WIN_W - 170, WIN_H - 140, RED, "COLOR");
	if (e->mode == POSITION)
		mlx_string_put(e->mlx, e->win, WIN_W - 170, WIN_H - 140, PURPLE, "POSITION");
	if (e->mode == SIZE)
		mlx_string_put(e->mlx, e->win, WIN_W - 170, WIN_H - 140, GREEN, "SIZE");
	if (e->mode == DIRECTION)
		mlx_string_put(e->mlx, e->win, WIN_W - 170, WIN_H - 140, YELLOW, "DIRECTION");
	if (e->mode == CAMERA)
		mlx_string_put(e->mlx, e->win, WIN_W - 170, WIN_H - 140, BLUE, "CAMERA");
	if (e->mode == FILTER)
		mlx_string_put(e->mlx, e->win, WIN_W - 170, WIN_H - 140, PINK, "FILTER");
}

void		display_menu(t_env *e)
{
	shadow_print(e, 20, 35, "Use 'M' to switch edit mode");
	shadow_print(e, 20, 125, "(Use 'H' to hide menu and data)");
	if (e->mode == COLOR || e->mode == FILTER)
	{
		shadow_print(e, 20, 50, "Use ASD to manipulate colors:");
		shadow_print(e, 20, 70, "- Red (Q) Green (S) Blue (D)");
	}
	if (e->mode == POSITION)
		shadow_print(e, 20, 50, "Use AD(x)WS(y)RF(z) to move the object");
	if (e->mode == SIZE)
		shadow_print(e, 20, 50, "Use Q<->D to change the object size");
	if (e->mode == DIRECTION)
		shadow_print(e, 20, 50, "Use W(z)A(x)S(y) to rotate the object");
	if (e->mode == CAMERA)
		shadow_print(e, 20, 50, "Use WASD and arrow keys to move the camera");
}

void		display_data(t_env *e)
{
	display_campos(e);
	display_camdir(e);
	if (e->items[e->select].type != TRIANGLE)
		display_itempos(e);
	if (e->items[e->select].type == TRIANGLE)
		display_triangle(e);
	if (e->items[e->select].type == CYL || e->items[e->select].type == CONE || e->items[e->select].type == PLANE)
		display_itemdir(e);
	display_itemmisc(e);
	display_scenedata(e);
	display_filter(e);
	display_itemrgb(e);
	display_itemname(e);
	display_mode(e);
}
