/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:29:07 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:17:07 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

typedef struct s_uint_fmt
{
	char	*str;
	int		num_len;
	int		pad_zeros;
	int		pad_spaces;
	int		total_len;
}			t_uint_fmt;

static void	init_uint_format(t_uint_fmt *fmt, unsigned int n, t_format *f)
{
	fmt->pad_zeros = 0;
	fmt->pad_spaces = 0;
	fmt->str = ft_utoa(n);
	fmt->num_len = ft_strlen(fmt->str);
	if (f->precision_specified && f->precision == 0 && n == 0)
		fmt->num_len = 0;
	if (f->precision_specified && f->precision > fmt->num_len)
		fmt->pad_zeros = f->precision - fmt->num_len;
	fmt->total_len = fmt->num_len + fmt->pad_zeros;
	if (f->width > fmt->total_len)
		fmt->pad_spaces = f->width - fmt->total_len;
}

static int	write_unsigned_body(t_uint_fmt *fmt, t_format *f)
{
	int	len;

	len = 0;
	if (!f->flag_minus && (!f->flag_zero || f->precision_specified))
		len += print_padding(fmt->pad_spaces, ' ', f->fd);
	if (!f->precision_specified && f->flag_zero && !f->flag_minus)
		len += print_padding(fmt->pad_spaces, '0', f->fd);
	len += print_padding(fmt->pad_zeros, '0', f->fd);
	if (fmt->num_len)
		len += write(f->fd, fmt->str, fmt->num_len);
	if (f->flag_minus)
		len += print_padding(fmt->pad_spaces, ' ', f->fd);
	return (len);
}

int	print_unsigned(unsigned int n, t_format *f)
{
	t_uint_fmt	fmt;
	int			len;

	init_uint_format(&fmt, n, f);
	len = write_unsigned_body(&fmt, f);
	free(fmt.str);
	return (len);
}
