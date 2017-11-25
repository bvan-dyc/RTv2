/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectortools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-dyc <bvan-dyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:09:07 by bvan-dyc          #+#    #+#             */
/*   Updated: 2017/10/31 14:36:23 by bvan-dyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/rtv1.h"

t_vector	rt_vectorsub(t_vector *v1, t_vector *v2)
{
	t_vector res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}

void		rt_vectornorm(t_vector *v)
{
	double	n;

	n = 1.0 / sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x *= n;
	v->y *= n;
	v->z *= n;
}

t_vector		rt_vectornorm_r(t_vector *v)
{
	double	n;
	t_vector res;

	n = 1.0 / sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	res.x = v->x * n;
	res.y = v->y * n;
	res.z = v->z * n;
	return (res);
}

double		rt_vecdot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector	rt_vectorscale(double c, t_vector *v)
{
	t_vector res;

	res.x = v->x * c;
	res.y = v->y * c;
	res.z = v->z * c;
	return (res);
}

t_vector rt_vectorcross(t_vector *v1, t_vector *v2)
{
	t_vector res;

	res.x = (v1->y * v2->z) - (v1->z * v2->y);
	res.y = (v1->z * v2->x) - (v1->x * v2->z);
	res.z = (v1->x * v2->y) - (v1->y * v2->x);

	return res;
}

t_vector	rt_vectoradd(t_vector *v1, t_vector *v2)
{
	t_vector res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

t_vector rt_rotatex(t_vector v, double alpha)
{
	t_vector res;

	res.x = v.x;
	res.y = v.y * cos(alpha) - v.z * sin(alpha);
	res.z = v.y * sin(alpha) + v.z * cos(alpha);
	return (res);
}

t_vector rt_rotatey(t_vector v, double alpha)
{
	t_vector res;

	res.x = v.x * cos(alpha) + v.z * sin(alpha);
	res.y = v.y;
	res.z = v.z * cos(alpha) - v.x * sin(alpha);
	return (res);
}

t_vector rt_rotatez(t_vector v, double alpha)
{
	t_vector res;

	res.x = v.x * cos(alpha) - v.y * sin(alpha);
	res.y = v.x * sin(alpha) + v.y * cos(alpha);
	res.z = v.z;
	return (res);
}

t_vector	rt_rotatevector(t_vector vector, t_vector rotator)
{
	vector = rt_rotatex(vector, PI * rotator.x / 180);
	vector = rt_rotatey(vector, PI * rotator.y / 180);
	vector = rt_rotatez(vector, PI * rotator.z / 180);
	return (vector);
}
