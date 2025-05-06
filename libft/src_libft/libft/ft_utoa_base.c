/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:05:31 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:46:01 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa_base(unsigned long value, const char *base)
{
	char			*res;
	int				base_len;
	int				i;
	unsigned long	tmp;

	base_len = ft_strlen(base);
	if (base_len < 2)
		return (NULL);
	tmp = value;
	i = 1;
	while (tmp)
	{
		tmp /= base_len;
		i++;
	}
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	res[i] = '\0';
	while (i--)
	{
		res[i] = base[value % base_len];
		value /= base_len;
	}
	return (res);
}
