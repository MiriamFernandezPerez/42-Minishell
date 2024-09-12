/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by esellier          #+#    #+#             */
/*   Updated: 2024/09/12 19:05:43 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_red // Miriam expand
{
	char		*file;
	int			redirection; //HEREDOC/APPEND/INPUT/OUTPUT
	//int		fd; //Emilie exe
	t_red		*next;
}				t_red;

typedef	struct s_section
{
	char		**cmd; //Miriam expand
	t_red		*files; //Miriam expand
	char		**path_array; //Emilie exe
	char		*path; //Emilie exe
	int			flag; //Emilie exe
	int			pid; //Emilie exe
	int			fd; //Emilie exe
	t_section	*next;  //Miriam expand
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

/*typedef struct s_exe
{
	char	**cmd;
	char	**array;
	char	*path;
	int		fd[2];
	int		flag;
	int		pid1;
	int		pid2;
}			t_exe;
*/

//split
int		count_path(char *str, char c);
int		strlen_path(char *str, char c);
//void	free_array(char **array); (same in builtins)
char	**put_path(char **array, char *str, char c, int path);
char	**split_env(char *str);

//exe

//exe_utils
char	**lst_to_array(t_env *lst);

//path


#endif
