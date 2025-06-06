# 🐚 Proyecto Minishell

## 📚 Descripción General

**Minishell** es una implementación simplificada de una shell Unix, desarrollada como parte del currículo de la Escuela 42. El objetivo principal es recrear funcionalidades básicas de una shell, incluyendo el análisis y ejecución de comandos, manejo de memoria y diseño modular, todo construido desde cero utilizando una biblioteca de utilidades personalizada (`libft`).

### 🎯 Objetivos Educativos

- Comprender la gestión de procesos y llamadas al sistema en Unix.
- Implementar análisis léxico y sintáctico de comandos.
- Gestionar la memoria de manera eficiente y prevenir fugas.
- Diseñar una arquitectura de software modular y escalable.

---

## 🧱 Estructura del Proyecto y Dependencias

El proyecto sigue una arquitectura modular basada en una biblioteca de utilidades personalizada. Los componentes principales incluyen:

- **`libft`**: Biblioteca personalizada que proporciona funciones fundamentales para manipulación de cadenas, gestión de memoria y estructuras de datos.
- **GNU Readline**: Permite la entrada interactiva con soporte de historial y edición de línea.
- **Librerías del sistema**: Encabezados estándar para E/S, asignación de memoria y llamadas al sistema.

---

## 🧩 Arquitectura de Datos Principal

Minishell utiliza dos estructuras de datos primarias para gestionar el estado de la shell y el procesamiento de comandos:

- **`t_data`**: Contexto principal de la shell que contiene el prompt del usuario y referencias al analizador.
- **`t_parser`**: Contenedor de procesamiento de comandos que mantiene la entrada tokenizada como un arreglo de cadenas.

### 🔄 Flujo de Procesamiento

1. `ft_initialize()` configura la estructura de datos principal.
2. `ft_read_prompt()` captura la entrada del usuario utilizando readline.
3. `ft_tokenize()` divide los comandos en tokens procesables.
4. `ft_free_data()` maneja la limpieza de memoria después del procesamiento.

---

## 🚧 Estado de Desarrollo y Arquitectura

La implementación actual representa la fase fundamental del proyecto Minishell, con manejo básico de entrada y tokenización completados. La arquitectura demuestra una clara separación de responsabilidades con componentes modulares.

### ✅ Capacidades Actuales

- Visualización interactiva del prompt con historial.
- Análisis y tokenización de la entrada de comandos.
- Prevención de fugas de memoria mediante limpieza estructurada.
- Salida de depuración para desarrollo (`print_tokens()`).

### 🔜 Funcionalidades Planeadas

- Ejecución de comandos.
- Implementación de comandos integrados (built-ins).
- Operaciones con tuberías (pipes).

---

## 🛠️ Compilación y Ejecución

Para compilar y ejecutar el proyecto:

```bash
make
./minishell
```

# 📎 Recursos Útiles

Aquí tienes una recopilación de recursos importantes para el proyecto:

- 📘 [Guía completa del proyecto (DeepWiki)](https://deepwiki.com/MiriamFernandezPerez/42_Minishell)  
- 📗 [Documentación oficial de GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)  
- 📙 [Normas de codificación de la Escuela 42](https://github.com/42School/norminette)

---

# 📝 Créditos

- 💻 **Proyecto:** Minishell – Escuela 42  
- ✍️ **Autoras originales:** Miriam Fernández Pérez y Emilie Sellier

---

