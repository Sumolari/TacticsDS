---
layout: post
title: Práctica 3 - Entrada y salida de datos utilizando el texto
date: 2015-02-26 12:26:00
---


##Introducción

Comprobado que tenemos en local tanto la documentación como los ejemplos de DEVKITPRO.

##Gestión de los controles

Hemos realizado un programa que imprima por pantalla el estado de los 13 botones mediante el enum `KEYPAD_BITS` y la función `keysHeld()`. El color del texto cambia dependiendo de si está pulsado o no ese botón.

> ![Captura del programa keysHeld.](../../../../p3media/keysHeld.png)
>
> Captura del programa keysHeld.

##Uso avanzado del texto en pantalla

###custom_font

En este ejemplo han creado un fichero `.bmp` que contiene por filas en una columna 95 caracteres. El programa utiliza el fichero `font.h` creado por grit y este `.bmp` para definir un variable de tipo ConsoleFont y luego lo utiliza con un \texttt{console} definido al principio del programa. Al final del programa con un simple `printf` nos muestra en el emulador la fuente custom.

> ![Captura del programa print_both_screens.](../../../../p3media/print_both_screens.png)
>
> Captura del programa print_both_screens.

###rotation

Este programa juega con una imagen puesta como fondo en la pantalla principal, mediante las teclas permite hacer varias transformaciones de la imagen con el uso de funciones de libnds. Podemos ajustar donde está centrada la imagen, el tamaño en ambas ejes y el ángulo en ambas direcciones. Por alguna razón, en el código del ejemplo, utiliza la tecla `START` para cambiar el centro de la imagen en el eje x, pero también utiliza esta tecla para salir del programa. Comentando la linea que hace `break` al pulsar la tecla `START` ya podemos cambiar el centro de la imagen en el eje x.

> ![Captura del programa rotation.](../../../../p3media/rotation.png)
>
> Captura del programa rotation.

###rotscale_text

Este ejemplo es muy similar al anterior, lo único que cambia es que al principio carga una fuente custom como en el ejemplo que hemos visto anteriormente y muestra la salida en la pantalla inferior. Hace las mismas operaciones sobre el fondo como en el ejemplo anterior y consigue la referencia al fondo directamente de la consola. 

> ![Captura del programa rotscale_text.](../../../../p3media/rotscale_text.png)
>
> Captura del programa rotscale_text.

###console_windows

Con el último ejemplo observamos que tenemos dos cajas en pantalla y dependiendo en que lado de la pantalla tocamos la pantalla, va escribiendo las coordinadas del toque en la caja correspondiente a esa mitad en vertical de la pantalla. Consigue esto con la función de `consoleSetWindow` variando el valor del eje x para cada una de las cajas y así imprimiendo dentro de ellas.

> ![Captura del programa console_windows.](../../../../p3media/console_windows.png)
> 
> Captura del programa console_windows.

##Sistemas de archivos en NDS

###libfat

`fat.h`
####funciones
* `fatInitDefault()`
* `opendir()`
* `closedir()`
* `readdir`

####DeSmuMe

> ![Captura del programa libfat en el emulador DeSmuMe.
](../../../../p3media/fat.png)
>
> Captura del programa libfat en el emulador DeSmuMe.

Con la version por defecto de **DeSmuMe** nos sale un error, esto es debido a que no inicializa un sistema de ficheros por defecto. Pero, tenemos a nuestra disposición la version `desmume-glade` que efectivamente si que carga bien el programa de ejemplo.

> ![Captura del programa libfat en el emulador DeSmuMe-glade.
](../p3media/fat_glade.png)
>
> Captura del programa libfat en el emulador DeSmuMe-glade.

####NO$GBA

> ![Captura del programa libfat en el emulador NO$GBA.](../../../../p3media/fat_nogba.png)
>
> Captura del programa libfat en el emulador NO$GBA.


####Nintendo DSlite

> ![Captura del programa libfat en una consola NDSLite.
](../../../../p3media/fat_nds.jpg)
> 
> Captura del programa libfat en una consola NDSLite.


###nitrofs

`filesystem.h`
####funciones
* `nitroFSInit()`
* `dirlist()`
* `fseek`
* `ftell`
* `fread`

####DeSmuMe

En este ejemplo además de listar los ficheros existentes, crea algunos archivos para que el ejemplo tenga salida.

> ![Captura del programa nitrofs en el emulador DeSmuMe.
](../p3media/nitrofs.png)
> 
> Captura del programa nitrofs en el emulador DeSmuMe.


####NO$GBA

> ![](../../../../p3media/nitrofs_nogba.png)
>
> Captura del programa nitrofs en el emulador NO$GBA.


####Nintendo DSlite

En una consola real, el ejemplo de *nitrofs* muestra una pantalla en negro.