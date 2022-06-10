/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:23:05 by vbarbier          #+#    #+#             */
/*   Updated: 2021/12/18 17:54:30 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_intlen(int n, char *base)
{
	int	i;
	int	lenbase;

	lenbase = ft_strlen(base);
	i = 1;
	if (n < 0)
		i++;
	while (n / lenbase)
	{
		i++;
		n = n / lenbase;
	}
	return (i);
}

static void	ft_putnbr_fd1(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	if (nb >= 10)
	{
		ft_putnbr_fd1(nb / 10, fd);
		ft_putnbr_fd1(nb % 10, fd);
	}
	if (nb < 10)
		ft_putchar_fd(nb + '0', fd);
}

int	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr_fd1(n, fd);
	return (ft_intlen(n, "0123456789"));
}
