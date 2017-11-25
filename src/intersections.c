/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-dyc <bvan-dyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:09:07 by bvan-dyc          #+#    #+#             */
/*   Updated: 2017/10/31 15:46:52 by bvan-dyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/rtv1.h"

int		rt_intersectsphere(t_ray *r, t_item *s, double *t)
{
	t_inter m;

	m.ret = FALSE;
	m.dist = rt_vectorsub(&r->start, &s->pos);
	m.a = rt_vecdot(&r->dir, &r->dir);
	m.b = 2 * rt_vecdot(&r->dir, &m.dist);
	m.c = rt_vecdot(&m.dist, &m.dist) - (s->size * s->size);
	m.discr = m.b * m.b - 4 * m.a * m.c;
	if (m.discr < 0)
		m.ret = FALSE;
	m.t0 = (-m.b + sqrtf(m.discr)) / (2);
	m.t1 = (-m.b - sqrtf(m.discr)) / (2);
	if (m.t0 > m.t1)
		m.t0 = m.t1;
	if ((m.t0 > EPSILON) && (m.t0 < *t))
	{
		*t = m.t0;
		m.ret = TRUE;
	}
	else
		m.ret = FALSE;
	return (m.ret);
}

int		rt_intersectcone(t_ray *r, t_item *c, double *t)
{
	t_inter m;

	m.dist = rt_vectorsub(&r->start, &c->pos);
	m.norm = rt_vectornorm_r(&c->dir);
	m.a = rt_vecdot(&r->dir, &r->dir) - (1 + pow(tan(c->size), 2)) *
		pow(rt_vecdot(&r->dir, &m.norm), 2);
	m.b = 2 * (rt_vecdot(&r->dir, &m.dist) - (1 + pow(tan(c->size), 2))
		* rt_vecdot(&r->dir, &m.norm) * rt_vecdot(&m.dist, &m.norm));
	m.c = rt_vecdot(&m.dist, &m.dist) - (1 +
		pow(tan(c->size), 2)) * pow(rt_vecdot(&m.dist, &m.norm), 2);
	m.discr = m.b * m.b - 4 * m.a * m.c;
	if (m.discr < 0)
		return (FALSE);
	m.t0 = (-m.b + sqrtf(m.discr)) / (2 * m.a);
	m.t1 = (-m.b - sqrtf(m.discr)) / (2 * m.a);
	if (m.t0 > m.t1)
		m.t0 = m.t1;
	m.ret = TRUE;
	if ((m.t0 > EPSILON) && (m.t0 < *t))
		*t = m.t0;
	else
		m.ret = FALSE;
	r->dist = m.dist;
	return (m.ret);
}

int		rt_intersectcylinder(t_ray *r, t_item *c, double *t)
{
	t_inter m;

	m.dist = rt_vectorsub(&r->start, &c->pos);
	m.norm = rt_vectornorm_r(&c->dir);
	m.a = rt_vecdot(&r->dir, &r->dir) - pow(rt_vecdot(&r->dir, &m.norm), 2);
	m.b = 2 * (rt_vecdot(&r->dir, &m.dist) -
		(rt_vecdot(&r->dir, &m.norm) * rt_vecdot(&m.dist, &m.norm)));
	m.c = rt_vecdot(&m.dist, &m.dist) -
		pow(rt_vecdot(&m.dist, &m.norm), 2) - c->size * c->size;
	m.discr = m.b * m.b - 4 * m.a * m.c;
	if (m.discr < 0)
		return (FALSE);
	m.t0 = (-m.b + sqrtf(m.discr)) / (2 * m.a);
	m.t1 = (-m.b - sqrtf(m.discr)) / (2 * m.a);
	if (m.t0 > m.t1)
		m.t0 = m.t1;
	if ((m.t0 > EPSILON) && (m.t0 < *t))
	{
		*t = m.t0;
		m.ret = TRUE;
	}
	else
		m.ret = FALSE;
	r->dist = m.dist;
	return (m.ret);
}

int		rt_intersectplane(t_ray *r, t_item *p, double *t)
{
	double		denom;

	denom = ((rt_vecdot(&p->dir, &p->pos) -
			rt_vecdot(&p->dir, &r->start)) / rt_vecdot(&p->dir, &r->dir));
	if (denom < EPSILON)
		return (FALSE);
	*t = denom;
	if (t >= 0)
		return (TRUE);
	return (FALSE);
}

int 	rt_intersectdisk(t_ray *r, t_item *d, double *t)
{
	t_vector 	tmp;
	t_vector 	p;
	t_vector	v;
	float		d2;

	if (rt_intersectplane(r, d, t))
	{
		tmp = rt_vectorscale(*t, &r->dir);
		p = rt_vectoradd(&r->start, &tmp);
		v = rt_vectorsub(&p, &d->pos);
		d2 = rt_vecdot(&v, &v);
		return (sqrtf(d2) <= d->size);
	}
   return FALSE;
}

int		rt_intersecttriangle(t_env *e, t_ray *r, t_item *t, double *result, int state)
{
	t_triter m;

	m.edge1 = rt_vectorsub(&t->p2, &t->p1);
	m.edge2 = rt_vectorsub(&t->p3, &t->p1);

	m.s1 = rt_vectorcross(&r->dir, &m.edge2);

	m.det = rt_vecdot(&m.edge1, &m.s1);
	if (m.det > -EPSILON && m.det < EPSILON)
		return (FALSE);

	m.invdet = 1 / m.det;

	m.s2 = rt_vectorsub(&r->start, &t->p1);

	m.u = rt_vecdot(&m.s2, &m.s1) * m.invdet;

	if (m.u < 0 || m.u > 1)
		return (FALSE);

	m.s3 = rt_vectorcross(&m.s2, &m.edge1);

	m.v = rt_vecdot(&r->dir, &m.s3) * m.invdet;

	if (m.v < 0 || (m.u + m.v) > 1)
		return (FALSE);

	m.tmp = rt_vecdot(&m.edge2, &m.s3) * m.invdet;

	if ((m.tmp < 0) || (m.tmp > *result))
		return (FALSE);

	*result = m.tmp - 0.005;
	if (state == 1)
		e->norm = rt_vectorcross(&m.edge2, &m.edge1);

	return (TRUE);
}
