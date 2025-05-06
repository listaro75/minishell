/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:35:52 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:15:05 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	hex_len_ul(unsigned long n)
{
	int	len;

	len = 1;
	while (n > 15)
	{
		n /= 16;
		len++;
	}
	return (len);
}

static char	*to_hex_string(unsigned long value, int *out_len, int asc)
{
	int		len;
	char	*str;

	len = hex_len_ul(value);
	*out_len = len;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (len--)
	{
		if ((value % 16) < 10)
			str[len] = (value % 16) + '0';
		else
			str[len] = (value % 16) + asc;
		value /= 16;
	}
	return (str);
}

static int	print_ptr_null(t_format *f)
{
	int	len;
	int	padding;
	int	printed;

	len = 5;
	printed = 0;
	padding = 0;
	if (f->width > len)
		padding = f->width - len;
	if (!f->flag_minus)
		printed += print_padding(padding, ' ', f->fd);
	printed += write(f->fd, "(nil)", 5);
	if (f->flag_minus)
		printed += print_padding(padding, ' ', f->fd);
	return (printed);
}

static int	write_ptr(t_format *f, char *hex, int hex_len, int padding)
{
	int	len;

	len = 0;
	if (!f->flag_minus)
	{
		if (f->flag_zero)
			len += print_padding(padding, '0', f->fd);
		else
			len += print_padding(padding, ' ', f->fd);
	}
	len += write(f->fd, "0x", 2);
	len += write(f->fd, hex, hex_len);
	if (f->flag_minus)
		len += print_padding(padding, ' ', f->fd);
	return (len);
}

int	print_ptr(unsigned long ptr, t_format *f, int asc)
{
	char	*hex;
	int		hex_len;
	int		padding;
	int		total_len;
	int		len;

	if (ptr == 0)
		return (print_ptr_null(f));
	hex = to_hex_string(ptr, &hex_len, asc);
	if (!hex)
		return (0);
	total_len = hex_len + 2;
	padding = 0;
	if (f->width > total_len)
		padding = f->width - total_len;
	len = write_ptr(f, hex, hex_len, padding);
	free(hex);
	return (len);
}
