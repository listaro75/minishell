/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:48 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:11:29 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_char(char c, t_format *f)
{
	int	len;

	len = 0;
	if (!f->flag_minus)
		len += print_padding(f->width - 1, ' ', f->fd);
	len += write(f->fd, &c, 1);
	if (f->flag_minus)
		len += print_padding(f->width - 1, ' ', f->fd);
	return (len);
}
