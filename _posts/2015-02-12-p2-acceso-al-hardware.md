---
layout: post
title: Práctica 2 - Acceso al Hardware
date: 2015-02-12 09:40:00
---

## PersonalData

Hemos imprimido todos los valores que nos ofrece el struct de {\tt PersonalData}. Se puede observar en la imagen que hemos escogido el color verde para los nombres y el gris para los valores. Hemos observado que en el emulador No$GBA, no están definidos algunos de los valores como el *nombre* y el *mensaje personal* pero en el emulador DeSmuMe sí que existen valores para todos.


> ![Captura del programa PersonalData.](../../../../P2Media/personaldata.png)
>
> Captura del programa PersonalData.

## Paso del tiempo

### stopwatch

A continuación están las respuestas de los ejercicios planteados en el boletin.

1. **¿Cual es la definición (prototipo) de esta función?** {% highlight c %}
  void timerStart( int timer, ClockDivider divider, u16 ticks, VoidFn callback )
  {% endhighlight %}


2. **Busque también la definición de los argumentos segundo y tercero.**
   `ClockDivider_1024` equivale a dividir el reloj por 1024 (~ 32.7284 kHz) y el 0 como parámetro para el número de ticks antes de desbordar hace que cada tick de nuestro timer equivalga a un tick de reloj.

### timercallback

1. **¿Qué significa la función que se le pasa como tercer parámetro?**
   Calcula el valor correcto para el desbordamiento de ticks para una frecuencia dada.


2. **¿Cual es la definición (prototpipo) de la función, el cuarto parámetro, que puede ser llamada por el timer?** {% highlight c %}
  void timerCallBack()
  {% endhighlight %}

3. **¿Cómo se le pasa/recoge información a/desde esa función?**
   Con la variable global `play`.

### RealTimeClock

1. **¿Qué dos funciones se utilizan para averiguar la hora y la fecha?** Primero llama a `time` para que devuelve un struct con el Unix Time, después utiliza `gmtime` para tratar este `time_t` struct y devolver otro struct con el tiempo en un formato más manejable. Sus prototipos son los siguientes: {% highlight c %}
time_t time(time_t *t)
struct tm *gmtime(const time_t *timer)
  {% endhighlight %}

2. **¿Cómo inicializa este ejemplo el uso de las dos pantallas de la consola?** Con las líneas \#103 y \#106: {% highlight c %}
         lcdMainOnTop(); // Del fichero system.h
videoSetMode(MODE_0_3D); // Del fichero video.h
  {% endhighlight %}

## Gestión de entrada

### keyboard/keyboard\_async

Proporciona un teclado con una consola donde aparece lo que se teclea.

> ![Captura del programa keyboard\_async.](../../../../P2Media/keyboard_async.png)
>
> Captura del programa keyboard\_async.

### keyboard/keyboard\_stdin

Lee del teclado como entrada estándar con un tipico programa de hola `$(inserta_nombre)`.

> ![Captura del programa keyboard\_stdin.](../../../../P2Media/keyboard_stdin.png)
>
> Captura del programa keyboard\_stdin.

### Touch\_Pad/touch\_area/

Indica en pantalla qué punto de los ejes x/y de la pantalla está tocando el usuario y con qué cantidad de fuerza.

> ![Captura del programa touch\_area.](../../../../P2Media/touch_area.png)
>
> Captura del programa touch\_area.

### Touch\_Pad/touch\_look/

Proporciona en la pantalla de arriba un mundo 3D donde podemos "mirar" utilizando la pantalla de abajo deslizando el dedo.

> ![Captura del programa touch\_look.](../../../../P2Media/touch_look.png)
>
> Captura del programa touch\_look.

### Touch\_Pad/touch\_test/

Parecido al `test_area` pero proporcionando más información como que botones están siendo pulsados.

> ![Captura del programa touch\_test.](../../../../P2Media/touch_test.png)
>
> Captura del programa touch\_test.

## Trabajo autónomo

Mediante los ejemplos indicados no hubo gran problema para realizar el ejercicio, lo único que ha requerido refrescar un poco ha sido para mostrar contenido en la pantalla de arriba manteniendo el menú en la de abajo.

A continuación dejamos capturas del programa mostrando el valor de `name` y lo mismo tras darle a la función de `lcdSwap`.

> ![Programa con menú.](../../../../P2Media/prog.png)
>
> Programa con menú.
