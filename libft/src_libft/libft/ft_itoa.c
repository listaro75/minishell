/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:59 by mhanarte          #+#    #+#             */
/*   Updated: 2024/11/22 15:06:06 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkinput(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = n * -1;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_fillstr(char *str, int count, int i, long int nb)
{
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
		i++;
	}
	str[count] = '\0';
	while (count > i)
	{
		count --;
		str[count] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int			count;
	char		*str;
	long int	nb;
	int			i;

	i = 0;
	nb = n;
	count = ft_checkinput(n);
	if (nb < 0 || nb == 0)
	{
		count++;
	}
	str = (char *) malloc (sizeof(char) * count + 1);
	if (!str)
		return (NULL);
	return (ft_fillstr(str, count, i, nb));
}

// int	main(void)
// {
// 	int	nb;
// 	char	*str;

// 	nb = -450;

// 	str = ft_itoa(nb);	
// }