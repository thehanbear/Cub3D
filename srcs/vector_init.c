/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 03:41:20 by hlee-sun          #+#    #+#             */
/*   Updated: 2025/01/16 17:39:17 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_vector	vec_new(double x, double y);
t_vector	vec_from_angle(float angle);

/* Creates and returns a new 2D vector with the given x and y components. */
t_vector	vec_new(double x, double y)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	return (v);
}

/* Creates and returns a 2D vector based on the given angle. The vector 
   represents the direction of the angle on the unit circle cos/sin). */
t_vector	vec_from_angle(float angle)
{
	return (vec_new(cos(angle), sin(angle)));
}
