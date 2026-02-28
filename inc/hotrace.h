/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:19:50 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/28 18:12:12 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
#define HOTRACE_H

#include <stdlib.h>
#include <stdbool.h>

#define MAX_LOAD 0.75

typedef struct
{
	void* 	array;
	int 	count;
	int		capacity;
	int		new_capacity;
	size_t	key_size;
	size_t	value_size;

	bool	(*cmp)(const void*, const void*);
} hashmap;

bool str_cmp(const void* a, const void* b);

#endif
