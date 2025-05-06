/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:21:17 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:12:57 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	get_print_len(char *str, t_format *f)
{
	int	len;

	len = ft_strlen(str);
	if (f->precision_specified && f->precision < len)
		return (f->precision);
	return (len);
}

static int	write_string(char *str, int len, int padding, t_format *f)
{
	int	printed;

	printed = 0;
	if (!f->flag_minus)
		printed += print_padding(padding, ' ', f->fd);
	printed += write(f->fd, str, len);
	if (f->flag_minus)
		printed += print_padding(padding, ' ', f->fd);
	return (printed);
}

int	print_string(char *str, t_format *f)
{
	int	print_len;
	int	padding;

	if (!str)
		str = "(null)";
	print_len = get_print_len(str, f);
	if (str[0] == '(' && f->precision_specified && f->precision < 6)
		return (print_string_spe(f));
	padding = 0;
	if (f->width > print_len)
		padding = f->width - print_len;
	return (write_string(str, print_len, padding, f));
}

int	print_string_spe(t_format *f)
{
	int	i;

	i = 0;
	while (i < f->width)
		i += write(f->fd, " ", 1);
	return (i);
}
