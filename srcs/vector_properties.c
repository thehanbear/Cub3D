/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 03:40:50 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/14 03:40:52 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

double	vec_len(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

int	vec_equal(t_vector v1, t_vector v2)
{
	if (v1.x == v2.x && v1.y == v2.y)
		return (true);
	return (false);
}

double	vec_angle(t_vector v)
{
	t_vector v_norm;

	v_norm = vec_normalize(v);
	if (-v_norm.y < 0)
		return (-acos(v_norm.x));
	return (acos(v_norm.x));
}

double	vec_dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

void	vec_print(t_vector v)
{
	printf("(%f, %f)\n", v.x, v.y);
}
