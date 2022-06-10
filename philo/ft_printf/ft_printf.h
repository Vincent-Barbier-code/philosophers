/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:19:09 by vbarbier          #+#    #+#             */
/*   Updated: 2021/12/18 17:54:11 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdint.h>

void	ft_putchar_fd(char c, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *str, int fd);
size_t	ft_strlen(const char *str);
int		ft_printf(const char *str, ...);
int		ft_putnbr_base(unsigned int nbr, char *base);
char	*ft_itoa(int n);
int		ft_putnbr_point(uintptr_t nbr, char *base);
int		ft_putnbr_unsigned(unsigned int n, int fd);

#endif