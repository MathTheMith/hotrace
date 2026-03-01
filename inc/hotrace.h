/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:19:50 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/01 18:33:31 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# define MAX_LOAD 0.75

# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct rl
{
	char	*heap_line;
	char	*tmp;
	int		capacity;
	int		line_len;
	char	*result;
	char	line[4096];
}	t_rl;

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

size_t	ft_strlen(const char *s);
bool	str_cmp(const void *a, const void *b);
int		init_map(t_hashmap *map, size_t key_size,
			size_t value_size, bool (*cmp)(const void*, const void*));
int		map_put(t_hashmap *map, void *key, void *value);
void	*map_get(t_hashmap *map, void *key);
void	map_clean(t_hashmap *map);
void	*ft_memset(void *pointer, int value, size_t count);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	copy_values(t_hashmap *map, uint8_t *old_entries);
uint8_t	*decrease_malloc(t_hashmap *map, size_t entry_size);
uint8_t	*linear_probing(t_hashmap *map, void *array, void *key,
			size_t entry_size);
bool	is_null(uint8_t *bytes, size_t size);
int		resize_array(t_hashmap *map);
int		refill_buffer(char *buffer, int *buf_size, int *buf_pos);
int		handle_eof(t_rl *rl);
char	*finalize_line(t_rl *rl);
int		read_char(t_rl *rl, char *buffer, int *buf_pos);
void	ft_write(char *key, char *message);
#endif
