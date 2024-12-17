/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:54:55 by jbremser          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/08 13:11:26 by jbremser         ###   ########.fr       */
=======
/*   Updated: 2024/09/24 16:00:42 by jbremser         ###   ########.fr       */
>>>>>>> 5dbf18f (added libft)
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

<<<<<<< HEAD
int ft_strcmp(const char *s1, const char *s2)
{
    unsigned char	*s1a;
	unsigned char	*s2a;
    size_t i;

    i = 0;
    s1a = (unsigned char *)s1;
	s2a = (unsigned char *)s2;
    while ((s1a[i]) || (s2a[i]))
    {
=======
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1a;
	unsigned char	*s2a;
	size_t			i;

	i = 0;
	s1a = (unsigned char *)s1;
	s2a = (unsigned char *)s2;
	while ((s1a[i]) || (s2a[i]))
	{
>>>>>>> 5dbf18f (added libft)
		if (s1a[i] != s2a[i])
			return (s1a[i] - s2a[i]);
		else
			i++;
	}
	return (0);
}
