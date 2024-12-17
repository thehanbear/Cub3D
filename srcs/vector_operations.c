/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 03:40:58 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/14 03:41:01 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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

t_vector	vec_inverse(t_vector v)
{
	return (vec_new(-v.x, -v.y));
}

t_vector	vec_normalize(t_vector v)
{
	return (vec_mul(v, 1 / vec_len(v)));
}
