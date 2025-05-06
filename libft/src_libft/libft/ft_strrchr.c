/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:01:07 by mhanarte          #+#    #+#             */
/*   Updated: 2024/11/21 15:25:35 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*find;

	find = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			find = ((char *)(s + i));
		i++;
	}
	if (s[i] == (unsigned char)c)
		find = (char *)(s + i);
	return (find);
}
