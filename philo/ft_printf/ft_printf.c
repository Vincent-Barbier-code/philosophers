/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:46:36 by vbarbier          #+#    #+#             */
/*   Updated: 2022/01/07 15:17:10 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_put2(char c, va_list args)
{	
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int), 1));
	return (0);
}

static int	ft_put1(char c, va_list args)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		return (1);
	}
	if (c == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	if (c == 'p')
		return (ft_putnbr_point(va_arg(args, uintptr_t), "0123456789abcdef"));
	if (c == 'x')
		return (ft_putnbr_base(va_arg(args, int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_putnbr_base(va_arg(args, int), "0123456789ABCDEF"));
	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	else
		return (ft_put2(c, args));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		taille;
	int		i;

	va_start(args, str);
	i = 0;
	taille = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i])
		{
			i++;
			taille = taille + ft_put1(str[i++], args);
		}
		if (str[i] != '%' && str[i])
		{
			ft_putchar_fd(str[i++], 1);
			taille = taille + 1;
		}
	}
	va_end(args);
	return (taille);
}
