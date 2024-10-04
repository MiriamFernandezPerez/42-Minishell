/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by esellier          #+#    #+#             */
/*   Updated: 2024/10/04 19:59:13 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

//split
int			count_path(char *str, char c);
int			strlen_path(char *str, char c);
//void		free_array(char **array); (same in builtins)
char		**put_path(char **array, char *str, char c, int path);
char		**split_env(char *str);

//exe
int			builtins_exe(t_data *data, t_section *section);
int         classic_exe(t_data *data, t_section *section);
void        free_array_int(int **array);
int			ft_waitpid_status(t_section *section, t_data *data);
int         execution(t_data *data, t_section *section);

//exe_utils
char		**lst_to_arr(t_env *lst, t_data *data, char **array);
char		*ft_strjoin_three(char const *s1, char const *s2, char const *s3);
int			error_exe(t_data *data, char *arg, int i);
int			check_builtins(char **str);
void		exe_builtins_redi(t_data *data, int fd_in, int fd_out);

//exe_files
int			ft_heredoc(t_data *data, char *del);
int			create_file(char *file, int i, t_data *data, int fd);
void		create_pipe(t_data *data);
int			check_files(t_data *data, t_section *current, t_red *red);

//path
int			search_path(t_data *data, char **array, t_section *section);
char		*check_path(t_section *section, t_data *data, char *path_lst);
char		*find_path_cmd(char **array, int j, t_data *data, char *tmp);

//exe_section-utils
//t_section	*ft_initialize_section(void);
void		ft_free_section(t_section *section, t_section *previous);
void		close_fd(t_section *section);


#endif
