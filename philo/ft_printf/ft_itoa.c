/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:49:27 by vbarbier          #+#    #+#             */
/*   Updated: 2021/12/13 02:59:36 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_intlen(int n)
{
	int	i;

	i = 1;
	while (n / 10)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*ft_mem(int n)
{
	int		len;
	char	*str;

	len = ft_intlen(n);
	if (n < 0)
		str = malloc(len * sizeof(char) + 2);
	else
		str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	else
		return (str);
}

static int	ft_puissance(int n)
{
	int	nb;

	n = n - 1;
	nb = 1;
	while (n != 0)
	{
		nb *= 10;
		n--;
	}
	return (nb);
}

static char	*ft_onsenfout(int i, long int nb, int n, char *str)
{
	int	a;

	a = 0;
	if (nb < 0)
	{
		str[a++] = '-';
		nb = -nb;
		n = -n;
	}
	while (i != 0)
	{
		nb = nb / ft_puissance(i);
		str[a++] = nb + '0';
		n = n - nb * ft_puissance(i--);
		nb = n;
	}
	str[a] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	i;
	long int	nb;

	i = ft_intlen(n);
	str = ft_mem(n);
	if (str == NULL)
		return (NULL);
	nb = n;
	str = ft_onsenfout(i, nb, n, str);
	return (str);
}
