/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-dyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:09:07 by bvan-dyc          #+#    #+#             */
/*   Updated: 2017/02/17 16:09:08 by bvan-dyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/rtv1.h"
#include <stdio.h>

static void	special_keys(int keycode, t_env *e)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		(void)e;
		exit(1);
	}
}

static void	cam_keys(int keycode, t_env *e)
{
	if (e->mode == CAMERA)
	{
		if (keycode == KEY_UP) // 126
			e->campos.y -= e->increment;
		if (keycode == KEY_DOWN) // 124
			e->campos.y += e->increment;
		if (keycode == KEY_LEFT) // 123
			e->campos.x -= e->increment;
		if (keycode == KEY_RIGHT) // 125
			e->campos.x += e->increment;
		if (keycode == 12)
			e->camdir.x += 0.1;
		if (keycode == 0)
			e->camdir.x -= 0.1;
		if (keycode == 13)
			e->camdir.y += 0.1;
		if (keycode == 1)
			e->camdir.y -= 0.1;
		if (keycode == 14)
			e->camdir.z += 0.1;
		if (keycode == 2)
			e->camdir.z -= 0.1;
	}
/*
	if (keycode == 123 && (tmppos = e->campos.x) < 20000)
	{
		e->campos.x = e->campos.x * cosf(0.05) + e->campos.z * sinf(0.05);
		e->campos.z = tmppos * (-sinf(0.05)) + e->campos.z * cosf(0.05);
	}
	if (keycode == 124 && (tmppos = e->campos.x) > -20000)
	{
		e->campos.x = e->campos.x * cosf(-0.05) + e->campos.z * sinf(-0.05);
		e->campos.z = tmppos * (-sinf(-0.05)) + e->campos.z * cosf(-0.05);
	}
	else if (keycode == 125 && (tmppos = e->campos.y) > -20000)
	{
		e->campos.y = e->campos.y * cosf(-0.05) + e->campos.z * (-sinf(-0.05));
		e->campos.z = tmppos * sinf(-0.05) + e->campos.z * cosf(-0.05);
	}
	else if (keycode == 126 && (tmppos = e->campos.y) < 20000)
	{
		e->campos.y = e->campos.y * cosf(0.05) + e->campos.z * (-sinf(0.05));
		e->campos.z = tmppos * sinf(0.05) + e->campos.z * cosf(0.05);
	}
	*/
}

static void	letter_keys(int keycode, t_env *e)
{
	if (keycode == KEY_H)
		e->hidemenu += (e->hidemenu == 2 ? -2 : 1);
	if (keycode == 30)
		e->increment += 1;
	if (keycode == 42)
		e->increment -= 1;
	if (keycode == 38)
		e->disableshadow = (e->disableshadow == 0 ? 1 : 0);
	if (keycode == 41)
		e->mode += (e->mode == 5 ? -5 : 1);
	if (keycode == 31 && e->maxlvl > 1)
		e->maxlvl -= 1;
	if (keycode == 35 && e->maxlvl <= 50)
		e->maxlvl += 1;
	if (keycode == 48)
	{
		e->select++;
		if (e->select == e->numitems)
			e->select = 0;
	}
	if (e->mode == COLOR)
	{
		if (keycode == 0)
			e->items[e->select].colour.red += (e->items[e->select].colour.red >= 255 ? -255 : e->increment);
		if (keycode == 1)
			e->items[e->select].colour.green += (e->items[e->select].colour.green >= 255 ? -255 : e->increment);
		if (keycode == 2)
			e->items[e->select].colour.blue += (e->items[e->select].colour.blue >= 255 ? -255 : e->increment);
	}
	if (e->mode == SIZE)
	{
		if (keycode == 13)
			e->items[e->select].size += e->increment;
		if (keycode == 1 && e->items[e->select].size > e->increment)
			e->items[e->select].size -= e->increment;
	}
	if (e->mode == POSITION)
	{
		if (keycode == 13)
		{
			e->items[e->select].pos.y -= e->increment;
			e->items[e->select].p1.y -= e->increment;
			e->items[e->select].p2.y -= e->increment;
			e->items[e->select].p3.y -= e->increment;
		}
		if (keycode == 0)
		{
			e->items[e->select].pos.x -= e->increment;
			e->items[e->select].p1.x -= e->increment;
			e->items[e->select].p2.x -= e->increment;
			e->items[e->select].p3.x -= e->increment;
		}
		if (keycode == 1)
		{
			e->items[e->select].pos.y += e->increment;
			e->items[e->select].p1.y += e->increment;
			e->items[e->select].p2.y += e->increment;
			e->items[e->select].p3.y += e->increment;
		}
		if (keycode == 2)
		{
			e->items[e->select].pos.x += e->increment;
			e->items[e->select].p1.x += e->increment;
			e->items[e->select].p2.x += e->increment;
			e->items[e->select].p3.x += e->increment;
		}
		if (keycode == 3)
		{
			e->items[e->select].pos.z += e->increment;
			e->items[e->select].p1.z += e->increment;
			e->items[e->select].p2.z += e->increment;
			e->items[e->select].p3.z += e->increment;
		}
		if (keycode == 15)
		{
			e->items[e->select].pos.z -= e->increment;
			e->items[e->select].p1.z -= e->increment;
			e->items[e->select].p2.z -= e->increment;
			e->items[e->select].p3.z -= e->increment;
		}
	}
	if (e->mode == DIRECTION)
	{
		if (keycode == 12)
			e->items[e->select].dir.x += e->increment / 100;
		if (keycode == 0)
			e->items[e->select].dir.x -= e->increment / 100;
		if (keycode == 13)
			e->items[e->select].dir.y += e->increment / 100;
		if (keycode == 1)
			e->items[e->select].dir.y -= e->increment / 100;
		if (keycode == 14)
			e->items[e->select].dir.z += e->increment / 100;
		if (keycode == 2)
			e->items[e->select].dir.z -= e->increment / 100;
	}
	if (e->mode == FILTER)
	{
		if (keycode == 13)
			e->filtermode += (e->filtermode >= 3 ? -3 : 1);
		if (keycode == 0)
			e->filter.red += (e->filter.red >= 255 ? -255 : e->increment);
		if (keycode == 1)
			e->filter.green += (e->filter.green >= 255 ? -255 : e->increment);
		if (keycode == 2)
			e->filter.blue += (e->filter.blue >= 255 ? -255 : e->increment);
	}
}

int			key_hook(int keycode, t_env *e)
{
	printf("keycode = %d\n", keycode);
	special_keys(keycode, e);
	letter_keys(keycode,e);
	cam_keys(keycode, e);
	expose_hook(e);
	return (0);
}
