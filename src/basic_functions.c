/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:49:51 by mvachon           #+#    #+#             */
/*   Updated: 2026/03/01 12:37:41 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
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

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	len;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	len = ft_strlen((char *)ptr) + 1;
	if (len > new_size)
		len = new_size;
	ft_memcpy(new_ptr, ptr, len);
	free(ptr);
	return (new_ptr);
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
