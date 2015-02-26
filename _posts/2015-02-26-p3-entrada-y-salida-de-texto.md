---
layout: post
title: Práctica 3: Entrada y salida de datos utilizando el texto
date: 2015-02-26 09:40:00
---

##Introducción

Comprobado que tenemos en local tanto la documentación como los ejemplos de DEVKITPRO.

##Gestión de los controles

Hemos realizado un programa que imprima por pantalla el estado de los 13 botones mediante el enum `KEYPAD_BITS` y la función `keysHeld()`. El color del texto cambia dependiendo de si está pulsado o no ese botón.

![](../../../../P3Media/keysHeld.png)

##Uso avanzado del texto en pantalla

###custom_font

En este ejemplo han creado un fichero `.bmp` que contiene por filas en una columna 95 caracteres. El programa utiliza el fichero `font.h` creado por grit y este `.bmp` para definir un variable de tipo ConsoleFont y luego lo utiliza con un \texttt{console} definido al principio del programa. Al final del programa con un simple `printf` nos muestra en el emulador la fuente custom.

![](../../../../P3Media/print_both_screens.png)

###rotation

Este programa juega con una imagen puesta como fondo en la pantalla principal, mediante las teclas permite hacer varias transformaciones de la imagen con el uso de funciones de libnds. Podemos ajustar donde está centrada la imagen, el tamaño en ambas ejes y el ángulo en ambas direcciones. Por alguna razón, en el código del ejemplo, utiliza la tecla `START` para cambiar el centro de la imagen en el eje x, pero también utiliza esta tecla para salir del programa. Comentando la linea que hace `break` al pulsar la tecla `START` ya podemos cambiar el centro de la imagen en el eje x.

![](../../../../P3Media/rotation.png)

###rotscale_text

Este ejemplo es muy similar al anterior, lo único que cambia es que al principio carga una fuente custom como en el ejemplo que hemos visto anteriormente y muestra la salida en la pantalla inferior. Hace las mismas operaciones sobre el fondo como en el ejemplo anterior y consigue la referencia al fondo directamente de la consola. 

![](../../../../P3Media/rotscale_text.png)

###console_windows

Con el último ejemplo observamos que tenemos dos cajas en pantalla y dependiendo en que lado de la pantalla tocamos la pantalla, va escribiendo las coordinadas del toque en la caja correspondiente a esa mitad en vertical de la pantalla. Consigue esto con la función de `consoleSetWindow` variando el valor del eje x para cada una de las cajas y así imprimiendo dentro de ellas.

![](../../../../P3Media/console_windows.png)

##Sistemas de archivos en NDS

###libfat

`fat.h`
####funciones
* `fatInitDefault()`
* `opendir()`
* `closedir()`
* `readdir`

####DeSmuMe

![](../../../../P3Media/fat.png)

####NO$GBA

![](../../../../P3Media/fat_nogba.png)

####Nintendo DSlite

![](../../../../P3Media/fat_nds.jpg)

###nitrofs

`filesystem.h`
####funciones
* `nitroFSInit()`
* `dirlist()`
* `fseek`
* `ftell`
* `fread`

####DeSmuMe

![](../../../../P3Media/nitrofs.png)

####NO$GBA

![](../../../../P3Media/nitrofs_nogba.png)

####Nintendo DSlite

En una consola real, el ejemplo de *nitrofs* muestra una pantalla en negro.