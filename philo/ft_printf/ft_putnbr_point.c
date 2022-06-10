/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 04:50:36 by vbarbier          #+#    #+#             */
/*   Updated: 2021/12/18 17:54:48 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen_base(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

static int	ft_intlen(uintptr_t n, char *base)
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

static void	ft_print(uintptr_t n, char *base)
{
	unsigned long long int	nb;

	nb = n;
	if (nb > (unsigned long long int) ft_strlen_base(base) - 1)
	{
		ft_print(nb / ft_strlen_base(base), base);
		nb %= ft_strlen_base(base);
	}
	ft_putchar_fd(base[nb], 1);
}

static int	ft_condition_stop(char *base)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (ft_strlen_base(base) == 1 || ft_strlen_base(base) == 0)
		return (0);
	while (base[i])
	{
		if ((base[i] >= 9 && base[i] <= 13) || base[i] == 32)
			return (0);
		y = i + 1;
		while (base[y])
		{
			if (base[i] == base[y])
				return (0);
			y++;
		}
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	ft_putnbr_point(uintptr_t nbr, char *base)
{
	if (ft_condition_stop(base))
	{
		ft_putstr_fd("0x", 1);
		ft_print(nbr, base);
		return (ft_intlen(nbr, base) + 2);
	}
	return (0);
}
