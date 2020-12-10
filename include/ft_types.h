/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:53:08 by mozzart           #+#    #+#             */
/*   Updated: 2020/12/10 01:14:16 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_H
# define FT_TYPES_H
# ifndef LIBC_H
#  include <libc.h>
# endif
# ifdef _UINT8_T
typedef uint8_t t_uc;
# else
typedef unsigned char t_uc;
# endif
# ifdef _UINT16_
typedef uint16_t t_us;
# else
typedef unsigned short t_us;
# endif
# ifdef _UINT32_T
typedef uint32_t t_uint;
# else
typedef unsigned intt_uint;
# endif
# ifdef _UINT64_T
typedef uint64_t t_ull;
# else
typedef unsigned long long t_ull;
# endif
# ifndef t_options
typedef t_uint t_options;
# endif
# ifndef t_opts
typedef t_options t_opts;
# endif
# ifndef t_bool
typedef enum	e_bool
{
	ft_false,
	ft_true
}				t_bool;
typedef t_bool	t_bl;
# endif

#endif
