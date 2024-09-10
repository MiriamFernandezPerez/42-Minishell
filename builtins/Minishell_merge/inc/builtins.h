/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/09/10 20:56:00 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*typedef	struct s_exe
{
	char	**cmd;
	->array or lst de infile (with heredoc)
	array or lst de outfile (ou une pour les deux)
	->redirection lst avec les files ou a part?
	char 	**path_array;	
	char	*path
	int		*fd;
	int		flag;
	int		*pid
	struct t_exe	*prev;
	struct t_exe	*next;
}				t_exe;*/


/*typedef struct s_cmd
{
	char			**arg;
	char			***infile;
	char			***outfile;
	int				ar;
	int				in;
	int				out;
	int				lexer_indx;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;*/

//builtins
int		make_builtins(char **str, t_data *data);
int		exit_number(char **str, t_data *data);
int		make_exit(char **str, t_data *data);
void	make_echo(char **str);
int		make_pwd(t_data *data);

//builtins_env
t_env	*adjust_env(t_data *data, t_env *to_del);
void	make_unset(char **str, t_data *data);
int		make_env(t_data *data, char **str);

//builtins_export_utils
char	*check_value(t_data *data, int j, char *name);
int		first_check(char *str);
int		check_name(char *str, int i, t_env *current, t_data *data);
int		check_args(char *str);

//builtins_export
void	p_exp_loop(t_env *to_print, t_env *old, t_env *cur, t_env *env_lst);
void	print_export(t_env *env_lst);
void	export_malloc(char **str, int i, t_env *current, t_data *data);
int		make_export(char **str, t_data *data);

//builtins_cd
int		change_pwd(t_data *data, char *str);
int		cd_home(char **str, t_data *data);
int		make_cd(char **str, t_data *data);
//maths
int		modulo_negativ(int a);
int		check_minmax(char *str);
int		strncmp_long(const char *s1, const char *s2);

//env
t_env	*create_flag(t_env *new_node);
t_env	*env_new(char *str, t_env *new_node);
t_env	*create_env(char **env, t_data *data);
int		exp_new(char *str, t_env *new_node);
int		create_value(t_env *new_node, int i, int j, char *str);

//env_array
char	**copy_env(t_data *data, char **array, t_env *env);
char	**env_array(t_data *data, char **array);
t_env	*search_str(char *str, t_data *data);

//utils
int		ft_strcmp(char *s1, char *s2);
int		print_errors(char **str, t_data *data, int i);
void	ft_malloc(t_data *data, char **array, t_env *lst);
void	free_array(char **arr);
void	erase_lst(t_env *lst);

#endif
