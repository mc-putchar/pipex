/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 03:45:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/19 06:13:56 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memgrow(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	new = malloc(new_size);
	if (!new)
		return (NULL);
	if (ptr && new_size > old_size)
		new = ft_memcpy(new, ptr, old_size);
	return (free(ptr), new);
}
