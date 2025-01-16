/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 03:40:58 by hlee-sun          #+#    #+#             */
/*   Updated: 2025/01/16 17:42:47 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_sub(t_vector v1, t_vector v2);
t_vector	vec_mul(t_vector v, double n);
double		vec_len(t_vector v);

/*Adds, subtracts, or multiplys two vectors v1 and v2, and returns the result*/
t_vector	vec_add(t_vector v1, t_vector v2)
{
	return (vec_new(v1.x + v2.x, v1.y + v2.y));
}

t_vector	vec_sub(t_vector v1, t_vector v2)
{
	return (vec_new(v1.x - v2.x, v1.y - v2.y));
}

t_vector	vec_mul(t_vector v, double n)
{
	return (vec_new(v.x * n, v.y * n));
}

/* Returns the length of the vector v using the Pythagorean theorem. */
double	vec_len(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}
