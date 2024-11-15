/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 03:41:08 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/15 02:04:48 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_vector	vec_rotate(t_vector v, int angle)
{
	t_vector	v_rotated;

	v_rotated = vec_mul(vec_new(cos(vec_angle(v) + (M_PI / 180 * angle)),
				-sin(vec_angle(v) + (M_PI / 180 * angle))), vec_len(v));
	return (v_rotated);
}
