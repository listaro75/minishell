/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:01:39 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:19:10 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	check_flag(t_format *f)
{
	if (f->flag_hash == 0 && f->flag_minus == 0 && f->flag_plus == 0
		&& f->flag_space == 0 && f->flag_zero == 0
		&& f->precision_specified == 0)
		return (0);
	return (1);
}

void	init_pads(int *pad_zeros, int *pad_spaces, int *total_len)
{
	*pad_zeros = 0;
	*pad_spaces = 0;
	*total_len = 0;
}

int	print_padding(int count, char c, int fd)
{
	int	len;

	len = 0;
	while (count > 0)
	{
		len += write(fd, &c, 1);
		count--;
	}
	return (len);
}
