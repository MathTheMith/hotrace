/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:49:51 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/01 18:34:51 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	__asm__ volatile (
		"rep movsb"
		: "+D"(dest), "+S"(src), "+c"(n)
		:
		: "memory"
	);
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	const char	*p = s;

	while (*p)
		p++;
	return (p - s);
}

void	*ft_memset(void *pointer, int value, size_t count)
{
	__asm__ volatile (
		"rep stosb"
		: "+D"(pointer), "+c"(count)
		: "a"(value)
		: "memory"
	);
	return (pointer);
}
