/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 03:41:20 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/15 02:05:05 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_vector	vec_new(double x, double y)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vector	vec_from_angle(float angle)
{
    return (vec_new(cos(angle), -sin(angle)));
}
