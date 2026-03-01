/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:19:50 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/01 12:39:28 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# define MAX_LOAD 0.75
# include <stdlib.h>
# include <stdbool.h>

typedef struct hash
{
	void	*array;
	int		count;
	int		capacity;
	int		new_capacity;
	size_t	key_size;
	size_t	value_size;

	bool	(*cmp)(const void *, const void *);
}	t_hashmap;

bool	str_cmp(const void *a, const void *b);
void	init_map(t_hashmap *map, size_t key_size,
			size_t value_size, bool (*cmp)(const void*, const void*));
bool	map_put(t_hashmap *map, void *key, void *value);
void	*map_get(t_hashmap *map, void *key);
void	map_clear(t_hashmap *map);
void	free_map(t_hashmap *map);
void	*ft_realloc(void *ptr, size_t new_size);
void	*ft_memset(void *pointer, int value, size_t count);
void	*ft_memcpy(void *dest, const void *src, size_t n);
bool	str_cmp(const void *a, const void *b);
#endif
