<p align="end">
  <strong>🌐 Cambiar idioma:</strong><br>
  <a href="/README.es.md">
   <img src="https://github.com/Nachopuerto95/multilang/blob/main/ES.png" alt="Español" width="50">
 </a>&nbsp;&nbsp;&nbsp;
 <a href="/README.md">
   <img src="https://github.com/Nachopuerto95/multilang/blob/main/EN.png" alt="English" width="50">
 </a>
</p>

# 📚 Libft (42cursus)

<img src="https://github.com/Nachopuerto95/multilang/blob/main/42-Madrid%20-%20Edited.jpg">

## 📜 Acerca del Proyecto
> Como primer proyecto del cursus, sirve para conocer diversas funciones y como están diseñadas internamente.

```html
	🚀 Asentaremos nuestros conocimientos sobre C y la memoria, tanto el uso de punteros como el de memoria dinámica
	La parte bonus nos servirá tambien para introducirnos al uso de listas enlazadas.
```

> [!NOTE]  
> Debido a los requisitos de la norma de la Escuela 42:
> * Cada función no puede tener más de 25 líneas de código.
> * Todas las variables deben ser declaradas y alineadas en la parte superior de cada función.
> * El proyecto debe ser creado solo con las funciones permitidas.
<br>

## 📖 Descripción

Este proyecto es una __librería en C__ con funciones útiles que están permitidas para ser usadas en futuros proyectos del __cursus de la Escuela 42__. Con acceso a esta librería, el proceso de codificación en los próximos proyectos será más eficiente. El objetivo de reescribir estas funciones es entenderlas mejor y obtener una amplia gama de utilidades para los proyectos venideros.

## 📚 Índice

### Funciones de la librería `<ctype.h>`
* [`ft_isascii`](https://github.com/Nachopuerto95/libft/blob/main/ft_isascii.c) - Verifica si un carácter es un carácter ASCII de 7 bits.
* [`ft_isalpha`](https://github.com/Nachopuerto95/libft/blob/main/ft_isalpha.c) - Verifica si un carácter es alfabético.
* [`ft_isdigit`](https://github.com/Nachopuerto95/libft/blob/main/ft_isdigit.c) - Verifica si un carácter es un dígito decimal.
* [`ft_isalnum`](https://github.com/Nachopuerto95/libft/blob/main/ft_isalnum.c) - Verifica si un carácter es alfanumérico.
* [`ft_isprint`](https://github.com/Nachopuerto95/libft/blob/main/ft_isprint.c) - Verifica si un carácter es imprimible (incluido el espacio).
* [`ft_tolower`](https://github.com/Nachopuerto95/libft/blob/main/ft_tolower.c) - Convierte un carácter a minúscula.
* [`ft_toupper`](https://github.com/Nachopuerto95/libft/blob/main/ft_toupper.c) - Convierte un carácter a mayúscula.

### Funciones de la librería `<stdlib.h>`
* [`ft_atoi`](https://github.com/Nachopuerto95/libft/blob/main/ft_atoi.c) - Convierte una cadena ASCII a un entero.
* [`ft_calloc`](https://github.com/Nachopuerto95/libft/blob/main/ft_calloc.c) - Reserva espacio para un arreglo e inicializa su contenido en 0.

### Funciones de la librería `<strings.h>`
* [`ft_bzero`](https://github.com/Nachopuerto95/libft/blob/main/ft_bzero.c) - Establece a cero los primeros bytes de un bloque de memoria.
* [`ft_memset`](https://github.com/Nachopuerto95/libft/blob/main/ft_memset.c) - Establece un valor específico en un bloque de memoria.
* [`ft_memchr`](https://github.com/Nachopuerto95/libft/blob/main/ft_memchr.c) - Busca la primera aparición de un carácter en un bloque de memoria.
* [`ft_memcmp`](https://github.com/Nachopuerto95/libft/blob/main/ft_memcmp.c) - Compara dos bloques de memoria byte a byte.
* [`ft_memmove`](https://github.com/Nachopuerto95/libft/blob/main/ft_memmove.c) - Copia datos entre bloques de memoria, incluso si se solapan.
* [`ft_memcpy`](https://github.com/Nachopuerto95/libft/blob/main/ft_memcpy.c) - Copia datos entre bloques de memoria (sin solapamiento).

### Funciones de la librería `<string.h>`
* [`ft_strlen`](https://github.com/Nachopuerto95/libft/blob/main/ft_strlen.c) - Obtiene la longitud de una cadena.
* [`ft_strchr`](https://github.com/Nachopuerto95/libft/blob/main/ft_strchr.c) - Busca la primera aparición de un carácter en una cadena.
* [`ft_strrchr`](https://github.com/Nachopuerto95/libft/blob/main/ft_strrchr.c) - Busca la última aparición de un carácter en una cadena.
* [`ft_strnstr`](https://github.com/Nachopuerto95/libft/blob/main/ft_strnstr.c) - Localiza una subcadena dentro de otra cadena.
* [`ft_strncmp`](https://github.com/Nachopuerto95/libft/blob/main/ft_strncmp.c) - Compara dos cadenas hasta un número determinado de caracteres.
* [`ft_strdup`](https://github.com/Nachopuerto95/libft/blob/main/ft_strdup.c) - Duplica una cadena de texto usando `malloc`.
* [`ft_strlcpy`](https://github.com/Nachopuerto95/libft/blob/main/ft_strlcpy.c) - Copia una cadena con límite de tamaño.
* [`ft_strlcat`](https://github.com/Nachopuerto95/libft/blob/main/ft_strlcat.c) - Concatena cadenas con límite de tamaño.

### Funciones no estándar
* [`ft_itoa`](https://github.com/Nachopuerto95/libft/blob/main/ft_itoa.c) - Convierte un entero en una cadena ASCII.
* [`ft_substr`](https://github.com/Nachopuerto95/libft/blob/main/ft_substr.c) - Extrae una subcadena de una cadena.
* [`ft_strtrim`](https://github.com/Nachopuerto95/libft/blob/main/ft_strtrim.c) - Elimina caracteres específicos del principio y fin de una cadena.
* [`ft_strjoin`](https://github.com/Nachopuerto95/libft/blob/main/ft_strjoin.c) - Une dos cadenas en una nueva usando `calloc`.
* [`ft_split`](https://github.com/Nachopuerto95/libft/blob/main/ft_split.c) - Divide una cadena usando un delimitador y la convierte en un arreglo de cadenas.
* [`ft_strmapi`](https://github.com/Nachopuerto95/libft/blob/main/ft_strmapi.c) - Crea una nueva cadena aplicando una función a cada carácter de otra cadena.
* [`ft_striteri`](https://github.com/Nachopuerto95/libft/blob/main/ft_striteri.c) - Aplica una función a cada carácter de una cadena.
* [`ft_putchar_fd`](https://github.com/Nachopuerto95/libft/blob/main/ft_putchar_fd.c) - Escribe un carácter en un descriptor de archivo.
* [`ft_putstr_fd`](https://github.com/Nachopuerto95/libft/blob/main/ft_putstr_fd.c) - Escribe una cadena en un descriptor de archivo.
* [`ft_putendl_fd`](https://github.com/Nachopuerto95/libft/blob/main/ft_putendl_fd.c) - Escribe una cadena seguida de salto de línea.
* [`ft_putnbr_fd`](https://github.com/Nachopuerto95/libft/blob/main/ft_putnbr_fd.c) - Escribe un número entero en un descriptor de archivo.

### Funciones de listas enlazadas *(bonus)*
* [`ft_lstnew`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstnew_bonus.c) - Crea un nuevo nodo de lista.
* [`ft_lstsize`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstsize_bonus.c) - Cuenta los nodos de una lista.
* [`ft_lstlast`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstlast_bonus.c) - Devuelve el último nodo de la lista.
* [`ft_lstadd_back`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstadd_back_bonus.c) - Añade un nodo al final de la lista.
* [`ft_lstadd_front`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstadd_front_bonus.c) - Añade un nodo al principio de la lista.
* [`ft_lstdelone`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstdelone_bonus.c) - Elimina un nodo de la lista.
* [`ft_lstclear`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstclear_bonus.c) - Elimina todos los nodos desde un punto dado.
* [`ft_lstiter`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstiter_bonus.c) - Aplica una función a todos los nodos de la lista.
* [`ft_lstmap`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstmap_bonus.c) - Aplica una función a cada nodo de una lista, creando una nueva.

## ⚙️ Requisitos

La librería está escrita en __lenguaje C__ y necesita el compilador `gcc`, junto con las librerías estándar `<stdlib.h>` y `<unistd.h>` para su ejecución.

## 🛠️ Instrucciones

### Compilar la librería

Para compilar la librería, ve al directorio correspondiente y ejecuta:

Para las funciones __básicas__:

```shell
$ make
```

Para las funciones __bonus__ :

```shell
$ make bonus
```

Limpiar binarios (.o) y ejecutable files (.a)

```shell
$ make fclean
```

### 3. Utilizar en tu código

Para utilizarla simplemente incluyela en el Makefile, Ejemplo:

```Makefile
$(NAME): $(OBJ)
	cd libft && $(MAKE)
	$(CC) $(CFLAGS) $(OBJ)  -L ./libft -lft -o $(NAME)
```
después impórtala en tu código:

```c
#include "libft.h"
```
