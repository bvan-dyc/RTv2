/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-dyc <bvan-dyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:09:07 by bvan-dyc          #+#    #+#             */
/*   Updated: 2017/10/31 15:46:34 by bvan-dyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/rtv1.h"
#include <stdio.h>

void		rt_inititem(t_env *e)
{
	e->items[e->citem].pos.x = 0;
	e->items[e->citem].pos.y = 0;
	e->items[e->citem].pos.z = 0;
	e->items[e->citem].dir.x = 0;
	e->items[e->citem].dir.y = 0;
	e->items[e->citem].dir.z = 0;
	e->items[e->citem].colour.red = 0;
	e->items[e->citem].colour.green = 0;
	e->items[e->citem].colour.blue = 0;
	e->items[e->citem].size = 0;
	e->items[e->citem].reflection = 0;
	e->items[e->citem].refraction = 1.1;
	e->items[e->citem].p1.x = 0;
	e->items[e->citem].p1.y = 0;
	e->items[e->citem].p1.z = 0;
	e->items[e->citem].p2.x = 0;
	e->items[e->citem].p2.y = 0;
	e->items[e->citem].p2.z = 0;
	e->items[e->citem].p3.x = 0;
	e->items[e->citem].p3.y = 0;
	e->items[e->citem].p3.z = 0;
	e->items[e->citem].min.x = -10000;
	e->items[e->citem].min.y = -10000;
	e->items[e->citem].min.z = -10000;
	e->items[e->citem].max.x = 10000;
	e->items[e->citem].max.y = 10000;
	e->items[e->citem].max.z = 10000;
}

int			rt_checkrgbpos(t_env *e, int red)
{
	int end;

	if (ft_strncmp(e->scene[red + 2], "\tpos:(", 6) != 0 || \
			ft_strncmp(e->scene[red + 3], "\trgb:(", 6) != 0)
		return (0);
	end = 6;
	e->items[e->citem].pos.x = ft_atoicount(e->scene[red + 2], &end);
	e->items[e->citem].pos.y = ft_atoicount(e->scene[red + 2], &end);
	e->items[e->citem].pos.z = ft_atoicount(e->scene[red + 2], &end);
	if (e->scene[red + 2][end] != ')')
		return (0);
	end = 6;
	e->items[e->citem].colour.red = ft_atoicount(e->scene[red + 3], &end);
	e->items[e->citem].colour.green = ft_atoicount(e->scene[red + 3], &end);
	e->items[e->citem].colour.blue = ft_atoicount(e->scene[red + 3], &end);
	if (e->scene[red + 3][end] != ')')
		return (0);
	return (1);
}

int			rt_makecylcone(t_env *e, int *red, int type)
{
	int end;

	rt_inititem(e);
	e->items[e->citem].type = type;
	if (ft_strcmp(e->scene[*red + 1], "{") != 0 || \
			ft_strcmp(e->scene[*red + 7], "}") != 0)
		return (0);
	if (rt_checkrgbpos(e, *red) == 0 || \
			ft_strncmp(e->scene[*red + 4], "\tdir:(", 6))
		return (0);
	end = 6;
	e->items[e->citem].dir.x = (double)ft_atoicount(e->scene[*red + 4], &end);
	e->items[e->citem].dir.y = (double)ft_atoicount(e->scene[*red + 4], &end);
	e->items[e->citem].dir.z = (double)ft_atoicount(e->scene[*red + 4], &end);
	if (e->scene[*red + 4][end] != ')')
		return (0);
	if ((ft_strncmp(e->scene[*red + 5], "\tsize: ", 7) != 0) ||\
		(ft_strncmp(e->scene[*red + 6], "\treflect: ", 10) != 0))
		return (0);
	end = 7;
	e->items[e->citem].size = ft_atoicount(e->scene[*red + 5], &end);
	end = 10;
	e->items[e->citem].reflection = ft_atoicount(e->scene[*red + 6], &end);
	e->citem++;
	*red += 8;
	return (1);
}

int			rt_makesphere(t_env *e, int *red)
{
	int end;

	rt_inititem(e);
	e->items[e->citem].type = SPHERE;
	if (ft_strcmp(e->scene[*red + 1], "{") != 0 || \
			ft_strcmp(e->scene[*red + 6], "}") != 0)
		return (0);
	if (rt_checkrgbpos(e, *red) == 0)
		return (0);
	if (ft_strncmp(e->scene[*red + 4], "\tradius: ", 9) != 0 || \
			ft_strncmp(e->scene[*red + 5], "\treflect: ", 10) != 0)
		return (0);
	end = 9;
	e->items[e->citem].size = ft_atoicount(e->scene[*red + 4], &end);
	end = 10;
	e->items[e->citem].reflection = ft_atoicount(e->scene[*red + 5], &end);
	e->citem++;
	*red += 7;
	return (1);
}

int			rt_makedisk(t_env *e, int *red)
{
	int end;

	rt_inititem(e);
	e->items[e->citem].type = DISK;
	if (ft_strcmp(e->scene[*red + 1], "{") != 0 || \
			ft_strcmp(e->scene[*red + 6], "}") != 0)
		return (0);
	if (rt_checkrgbpos(e, *red) == 0 || \
			ft_strncmp(e->scene[*red + 4], "\tdir:(", 6))
		return (0);
	end = 6;
	e->items[e->citem].dir.x = (double)ft_atoicount(e->scene[*red + 4], &end);
	e->items[e->citem].dir.y = (double)ft_atoicount(e->scene[*red + 4], &end);
	e->items[e->citem].dir.z = (double)ft_atoicount(e->scene[*red + 4], &end);
	if (e->scene[*red + 4][end] != ')')
		return (0);
	if (ft_strncmp(e->scene[*red + 5], "\tsize: ", 7) != 0)
		return (0);
	end = 7;
	e->items[e->citem].size = ft_atoicount(e->scene[*red + 5], &end);
	e->citem++;
	*red += 7;
	return (1);
}

int			rt_makeplane(t_env *e, int *red)
{
	int end;

	rt_inititem(e);
	e->items[e->citem].type = PLANE;
	if (ft_strcmp(e->scene[*red + 1], "{") != 0 || \
			ft_strcmp(e->scene[*red + 5], "}") != 0)
		return (0);
	if (rt_checkrgbpos(e, *red) == 0)
		return (0);
	if (ft_strncmp(e->scene[*red + 4], "\tdir:(", 6))
		return (0);
	end = 6;
	e->items[e->citem].dir.x = (double)ft_atoicount(e->scene[*red + 4], &end);
	e->items[e->citem].dir.y = (double)ft_atoicount(e->scene[*red + 4], &end);
	e->items[e->citem].dir.z = (double)ft_atoicount(e->scene[*red + 4], &end);
	if (e->scene[*red + 4][end] != ')')
		return (0);
	e->citem++;
	*red += 6;
	return (1);
}

int			rt_maketriangle(t_env *e, int *red)
{
	int end;

	rt_inititem(e);
	e->items[e->citem].type = TRIANGLE;
	if (ft_strcmp(e->scene[*red + 1], "{") != 0 || \
			ft_strcmp(e->scene[*red + 6], "}") != 0)
		return(0);
	if (ft_strncmp(e->scene[*red + 2], "\tp1:(", 5) != 0 || \
		ft_strncmp(e->scene[*red + 3], "\tp2:(", 5) != 0 || \
		ft_strncmp(e->scene[*red + 4], "\tp3:(", 5) != 0 || \
		ft_strncmp(e->scene[*red + 5], "\trgb:(", 6) != 0)
		return(0);
	end = 5;
	e->items[e->citem].p1.x = ft_atoicount(e->scene[*red + 2], &end);
	e->items[e->citem].p1.y = ft_atoicount(e->scene[*red + 2], &end);
	e->items[e->citem].p1.z = ft_atoicount(e->scene[*red + 2], &end);
	if (e->scene[*red + 2][end] != ')')
		return (0);
	end = 5;
	e->items[e->citem].p2.x = ft_atoicount(e->scene[*red + 3], &end);
	e->items[e->citem].p2.y = ft_atoicount(e->scene[*red + 3], &end);
	e->items[e->citem].p2.z = ft_atoicount(e->scene[*red + 3], &end);
	if (e->scene[*red + 3][end] != ')')
		return (0);
	end = 5;
	e->items[e->citem].p3.x = ft_atoicount(e->scene[*red + 4], &end);
	e->items[e->citem].p3.y = ft_atoicount(e->scene[*red + 4], &end);
	e->items[e->citem].p3.z = ft_atoicount(e->scene[*red + 4], &end);
	if (e->scene[*red + 4][end] != ')')
		return (0);
	end = 6;
	e->items[e->citem].colour.red = ft_atoicount(e->scene[*red + 5], &end);
	e->items[e->citem].colour.green = ft_atoicount(e->scene[*red + 5], &end);
	e->items[e->citem].colour.blue = ft_atoicount(e->scene[*red + 5], &end);
	if (e->scene[*red + 5][end] != ')')
		return (0);
	e->citem++;
	*red += 7;
	return (1);
}

int			rt_makelight(t_env *e, int *red)
{
	int end;

	if (ft_strcmp(e->scene[*red + 1], "{") != 0 || \
			ft_strcmp(e->scene[*red + 4], "}") != 0)
		return (0);
	if (ft_strncmp(e->scene[*red + 2], "\tpos:(", 6) != 0 || \
			ft_strncmp(e->scene[*red + 3], "\trgb:(", 6) != 0)
		return (0);
	end = 6;
	e->lights[e->culight].pos.x = ft_atoicount(e->scene[*red + 2], &end);
	e->lights[e->culight].pos.y = ft_atoicount(e->scene[*red + 2], &end);
	e->lights[e->culight].pos.z = ft_atoicount(e->scene[*red + 2], &end);
	if (e->scene[*red + 2][end] != ')')
		return (0);
	end = 6;
	e->lights[e->culight].colour.red = ft_atoicount(e->scene[*red + 3], &end);
	e->lights[e->culight].colour.green = ft_atoicount(e->scene[*red + 3], &end);
	e->lights[e->culight].colour.blue = ft_atoicount(e->scene[*red + 3], &end);
	if (e->scene[*red + 3][end] != ')')
		return (0);
	e->culight++;
	*red += 5;
	return (1);
}
