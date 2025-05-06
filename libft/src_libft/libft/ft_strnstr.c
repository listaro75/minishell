/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:29:55 by mhanarte          #+#    #+#             */
/*   Updated: 2024/11/21 15:25:29 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size;

	size = ft_strlen((char *)little);
	j = 0;
	i = 0;
	if (little[i] == 0)
		return ((char *)big);
	while (big[i] != 0)
	{
		if (big[i] == little[j] && i + size <= len)
		{
			while (big[i + j] == little[j])
			{
				j++;
				if (little[j] == 0)
					return ((char *)(big + i));
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
