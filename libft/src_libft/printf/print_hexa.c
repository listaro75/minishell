/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:31:53 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:17:40 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

typedef struct s_hexa_fmt
{
	char	*str;
	int		str_len;
	int		pad_zeros;
	int		pad_spaces;
	int		total_len;
	int		with_prefix;
}			t_hexa_fmt;

static int	hexa_len(unsigned int n)
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

char	*utoa_base(unsigned int n, int upper)
{
	char	*base;
	char	*res;
	int		len;

	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = hexa_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len--)
	{
		res[len] = base[n % 16];
		n /= 16;
	}
	return (res);
}

static void	init_hexa_format(t_hexa_fmt *fmt, unsigned int n, t_format *f)
{
	fmt->pad_zeros = 0;
	fmt->pad_spaces = 0;
	fmt->with_prefix = 0;
	fmt->str = utoa_base(n, f->specifier == 'X');
	fmt->str_len = ft_strlen(fmt->str);
	if (f->precision_specified && f->precision == 0 && n == 0)
		fmt->str_len = 0;
	if (f->precision_specified && f->precision > fmt->str_len)
		fmt->pad_zeros = f->precision - fmt->str_len;
	if (f->flag_hash && n != 0)
		fmt->with_prefix = 2;
	fmt->total_len = fmt->str_len + fmt->pad_zeros + fmt->with_prefix;
	if (f->width > fmt->total_len)
		fmt->pad_spaces = f->width - fmt->total_len;
}

static int	write_hexa_body(t_hexa_fmt *fmt, t_format *f, int upper)
{
	int	len;

	len = 0;
	if (!f->flag_minus && (!f->flag_zero || f->precision_specified))
		len += print_padding(fmt->pad_spaces, ' ', f->fd);
	if (fmt->with_prefix)
	{
		if (upper)
			len += write(f->fd, "0X", 2);
		else
			len += write(f->fd, "0x", 2);
	}
	if (!f->precision_specified && f->flag_zero && !f->flag_minus)
		len += print_padding(fmt->pad_spaces, '0', f->fd);
	len += print_padding(fmt->pad_zeros, '0', f->fd);
	if (fmt->str_len)
		len += write(f->fd, fmt->str, fmt->str_len);
	if (f->flag_minus)
		len += print_padding(fmt->pad_spaces, ' ', f->fd);
	return (len);
}

int	print_hexa(unsigned int n, t_format *f, int upper)
{
	t_hexa_fmt	fmt;
	int			len;

	init_hexa_format(&fmt, n, f);
	len = write_hexa_body(&fmt, f, upper);
	free(fmt.str);
	return (len);
}
