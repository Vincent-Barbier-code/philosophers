/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 06:48:22 by vbarbier          #+#    #+#             */
/*   Updated: 2021/12/18 17:55:05 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_intlen(unsigned int n, char *base)
{
	int	i;
	int	lenbase;

	lenbase = ft_strlen(base);
	i = 1;
	while (n / lenbase)
	{
		i++;
		n = n / lenbase;
	}
	return (i);
}

static void	ft_putnbr_fd1(unsigned int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb >= 10)
	{
		ft_putnbr_fd1(nb / 10, fd);
		ft_putnbr_fd1(nb % 10, fd);
	}
	if (nb < 10)
		ft_putchar_fd(nb + '0', fd);
}

int	ft_putnbr_unsigned(unsigned int n, int fd)
{
	ft_putnbr_fd1(n, fd);
	return (ft_intlen(n, "0123456789"));
}
