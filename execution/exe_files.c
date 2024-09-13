/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:17:45 by esellier          #+#    #+#             */
/*   Updated: 2024/09/13 18:02:56 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int		ft_heredoc()
{}*/

int	create_file(char *file, int i, t_data *data)
{
	int	fd;

	if (i == INPUT)
		fd = open(file, O_RDONLY);
	if (i == TRUNC)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (i == APPEND)
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (i == HEREDOC)
		//fd = ft_heredoc();
	if (fd == -1)
		return(error_exe(data, file, 0), 1);
	return (fd);
}
/*
if (i == INPUT) <
	if (access(file, F_OK) == 0 && access(file, R_OK) == 0)
			fd = open(file, O_RDONLY);
		if (fd == -1 || access(file, F_OK) != 0 || access(file, R_OK) != 0)
			return (error_exe(data, file, 0));
if (i == TRUNC) <
if(access(file, F_OK) == 0 && access(file, W_OK) != 0)
			return (fd);
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd == -1 || access(file, R_OK | W_OK) != 0)
			return (fd); 
*/