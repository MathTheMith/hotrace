/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:40:08 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/01 18:34:05 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "hotrace.h"

void	ft_write(char *key, char *message)
{
	write(1, key, ft_strlen(key));
	write(1, message, ft_strlen(message));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

bool	str_cmp(const void *a, const void *b)
{
	const char	*sa = *(const char**)a;
	const char	*sb = *(const char**)b;

	return (ft_strcmp(sa, sb) == 0);
}
