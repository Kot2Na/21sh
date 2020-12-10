/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 21:55:03 by ksharlen          #+#    #+#             */
/*   Updated: 2020/12/08 23:08:57 by tvanessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <sys/types.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>

# include "gl.h"
# include "libft.h"
# include "sh_limits.h"
# include "sh_struct.h"
# include "sh_init.h"
# include "internal_utilities.h"
# include "input_init.h"
# include "input_macros.h"
# include "input_parse_key.h"
# include "parser.h"
# include "exec.h"

#endif
