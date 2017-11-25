/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-dyc <bvan-dyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:09:07 by bvan-dyc          #+#    #+#             */
/*   Updated: 2017/10/31 17:59:25 by bvan-dyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/rtv1.h"

void		rt_error(int error)
{
	if (error == NOARGS || error == INVALIDFILE)
	{
		ft_putstr_fd("RTV1 requires a valid file to properly function\n", 2);
		exit(2);
	}
	else if (error == TOOMANYARGS)
	{
		ft_putstr_fd("RTV1 can only process one file at a time\n", 2);
		exit(2);
	}
	else if (error == INVALIDFORMAT)
	{
		ft_putstr_fd("File has an invalid format\n", 2);
		exit(2);
	}
}

static int	cross_close(t_env *e)
{
	mlx_destroy_window(e->mlx, e->win);
	rt_envfreer(e);
	exit(0);
	return (0);
}

int			expose_hook(t_env *e)
{
	rt_draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0, 0);
	if (e->hidemenu == 0 || e->hidemenu == 1)
		display_data(e);
	if (e->hidemenu == 1)
		display_menu(e);
	if (e->hidemenu == 2)
		shadow_print(e, 50, WIN_H - 50, "HELP (H)");
	return (0);
}

void		env_init(t_env *e, char *file)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIN_W, WIN_H, "RT");
	e->img_ptr = mlx_new_image(e->mlx, WIN_W, WIN_H);
	e->img = mlx_get_data_addr(e->img_ptr, &e->bits_per_pixel, \
	&e->size_line, &e->endian);
	e->disableshadow = FALSE;
	e->ss = 0;
	e->numitems = 0;
	e->citem = 0;
	e->numlights = 0;
	e->culight = 0;
	e->camdir.x = 0;
	e->camdir.y = 0;
	e->camdir.z = 1;
	e->campos.x = 0;
	e->campos.y = 0;
	e->campos.z = -10000;
	e->hidemenu = 0;
	e->maxlvl = 1;
	e->select = 0;
	e->mode = 0;
	e->filtermode = 0;
	e->increment = 10;
	e->scene = makescene(e, file);
	e->filter.red = 0;
	e->filter.green = 0;
	e->filter.blue = 0;
}

int			main(int ac, char **av)
{
	t_env *e;

	if (!(e = (t_env *)malloc(sizeof(t_env))))
		return (0);
	if (ac == 2 && av[1])
	{
		env_init(e, av[1]);
		if (e->ss == 0)
			rt_error(INVALIDFILE);
		parsecore(e);
		mlx_expose_hook(e->win, expose_hook, e);
		mlx_hook(e->win, CROSS_PRESS, KEY_PRESS_MASK, cross_close, e);
		mlx_key_hook(e->win, key_hook, e);
		mlx_loop(e->mlx);
	}
	else if (ac == 1)
		rt_error(NOARGS);
	else
		rt_error(TOOMANYARGS);
	rt_envfreer(e);
	return (0);
}
