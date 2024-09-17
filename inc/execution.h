/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by esellier          #+#    #+#             */
/*   Updated: 2024/09/17 18:56:54 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_red // Miriam expand
{
	char		*file;
	int			redi; //HEREDOC/APPEND/INPUT/TRUNC
	t_red		*next;
}				t_red;

typedef struct s_section
{
	char		**cmd; //Miriam expand
	t_red		**files; //Miriam expand
	char		**path_array; //Emilie exe
	char		*path; //Emilie exe
	int			flag; //Emilie exe
	int			pid; //Emilie exe
	int			fd_in; //Emilie exe
	int			fd_out; //Emilie exe
	t_section	*next; //Miriam expand
}				t_section;

typedef struct s_data
{
	char		*prompt;
	t_tokens	**tokens;
	t_section	**sections;
	int			tokens_qt;
	int			sections_qt;
	int			rt_value;
	t_env		*env_lst;
}				t_data;

//split
int			count_path(char *str, char c);
int			strlen_path(char *str, char c);
//void		free_array(char **array); (same in builtins)
char		**put_path(char **array, char *str, char c, int path);
char		**split_env(char *str);

//exe
void		execution(t_data *data);

//exe_utils
char		**lst_to_array(t_env *lst, t_data *data, char **array);
char		*ft_strjoin_three(char const *s1, char const *s2, char const *s3);
int			error_exe(t_data *data, char *arg, int i);

//exe_files
int			create_file(char *file, int i, t_data *data);
void		create_pipe(t_data *data);
void		check_files(t_data *data, t_section *current, t_red *red);

//path
int			search_path(t_data *data, char **array, t_section *section);
char		*check_path(t_section *section, t_data *data, char *path_lst);
char		*find_path_cmd(char **array, int j, t_data *data, char *tmp);

//exe_section-utils
t_section	*ft_initialize_section(void);
void		ft_free_section(t_section *section);
//void		ft_malloc_s(t_data *data, char **array, t_env *lst, t_section *sec);

#endif
