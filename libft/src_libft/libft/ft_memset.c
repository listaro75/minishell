/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:15:27 by mhanarte          #+#    #+#             */
/*   Updated: 2024/11/22 15:00:15 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}

// int	main(void)
// {
// //	char	test[]="bonjour";
// //	char	str[]="";
// //	size_t	n;
// 	//size_t	t;

// 	//t = 4;
// //	n = 14;
// //	memset(test, '-', n);
//   //     printf("%s\n", test);
//     //    ft_memset(str, '8', t);
//         printf("%s\n", ft_memset((void *)0,'a',12));

// }*/
