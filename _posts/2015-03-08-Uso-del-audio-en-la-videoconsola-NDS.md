---
layout: post
title: Práctica 4 - Uso del audio en la videoconsola NDS
date: 2015-03-08 15:07:00
---

##Simple Sound Playback Library

###Síntesis por generación de tonos

Empezamos revisando un ejemplo que vimos en la práctica 2, *timercallback* donde se utiliza el generador de sonidos. A continuación tenemos el prototipo de la función soundPlayPSG:

{% highlight cpp %}
int soundPlayPSG( DutyCycle cycle, u16 freq, u8 volume, u8 pan )
{% endhighlight %}

Podemos jugar con diferentes características del sonido que se va a generar:

* **DutyCycle:** Es el porcentaje del periodo cuando la señal está activa.

* **freq:** La frecuencia en Hz.

* **volume:** Volumen del canal, toma valores entre 0 y 127. 

* **pan:** El paneo en stereo, toma valores entre 0 y 127 siendo 64 el sonido centrado.

La función devuelve un id que corresponde al canal de audio que se está utilizando para este sonido generado y se utiliza luego para controlar la reproducción de este sonido.

####Iterar sobre tonos

Hemos realizado un programa que permite escuchar los tonos entre 20Hz y 20KHz en intervalos de 100Hz. Para ello hemos modificado el programa de ejemplo *timercallback*, creamos un variable para guardar la frecuencia actual y cada vez que se llama a `timerCallBack()` incrementamos esta variable en 100. Por último actualizamos la frecuencia del tono con la llamada `soundSetFreq(channel, freq);` dentro del callback.

####soundPlayNoise

Ampliando el programa anterior hemos añadido la opción de realizar llamadas a la función `soundPlayNoise(u16 freq, u8 volume, u8 pan)` variando sus parámetros. Los valores válidos para estos parámetros se pueden encontrar al principio de esta entrada.

Para realizar esto nos hemos basado en el programa de la práctica 2, *menus*, para ofrecer la posibilidad de reproducir PSG o Noise y permitir al usuario variar los 3 parámetros (frecuencia, volumen y pan) en ambos casos.

> ![Captura del programa tonos2](../../../../p4Media/tonos2.png)
>
> Captura del programa tonos2

###Micrófono

Veamos el ejemplo que nos proporciona devkitpro en *audio/micrecord*, donde podemos observar varias funciones relativas al sonido:

{% highlight cpp %}

soundMicRecord(void buffer, u32 bufferLength, MicFormat format, int freq, MicCallback callback)

soundMicOff()

soundEnable()

soundPlaySample(const void *data, SoundFormat format, u32 dataSize, u16 freq, u8 volume, u8 pan, bool loop, u16 loopPoint)

{% endhighlight %}

También podemos observar un cálculo que realiza al principio del ejemplo para el tamaño del buffer de sonido, con un sample rate de 8000 bits/s lo multiplica por 2 para audio de 16bits y después esto por 5 para tener sitio para 5 segundos de audio en 16 bits.

Ahora para realizar la función de exportar el audio grabado a disco debemos revisar el ejemplo de *filesystem/libfat* y comparar su makefile con el actual para *micrecord*. Observamos que además de la librería para el **arm9** también utiliza la librería de **fat**
`LIBS	:= 	-lfat -lnds9`

Una vez guardada una locución, podemos abrirla en Audacity.

> ![Captura de audacity con el fichero raw grabado con micrecord](../../../../p4Media/micrecord.png)
>
> Captura de audacity con el fichero raw grabado con micrecord

##Maxmod

**Maxmod** se utiliza para la reproducción de ficheros de sonido modulares y ahora forma parte de *libnds*.

###Reproducción de audio

Para utilizar la librería de **Maxmod** debemos incluir la cabecera `maxmod9.h` y compilar con la librería `-lmm9`. También incluimos en el makefile la carpeta de maxmod_data que contendrá los ficheros de audio y añadimos el `.bin` del banco de sonidos a la lista de ficheros binarios `BINFILES`. Por último, incluimos una regla para crear el banco de sonidos con *mmutil* procurando pasar el parámetro `-d` para dar compatibilidad a la **NDS**.

Observamos con el ejemplo `/audio/maxmod/basic_sound` algunos de los métodos propios de **Maxmod**.

Al principio inicializa **Maxmod** con los ajustes por defecto y con los ficheros de audio(ya convertidos a un banco de sonidos mediante *mmutil*) mediante `mmInitDefaultMem(mm_addr soundbank)`.

Luego mediante llamadas a `mmLoadEffect( indice_fichero_sonido )` carga los diferentes ficheros de audio.

Para los ficheros que no están en formato modular (efectos) debe hacer una estructura añadiendo información de *rate*, *handle*, *volumen* y *paneo* para cada fichero.

Ahora podemos reproducir los efectos mediante `mmEffectEx(direccion_struct_fichero)` y `mmEffectCancel(mm_sfxhand devuelto por mmEffectEx)` para detener la reproducción.

Para los ficheros ya en formato modular basta con usar el método `mmStart(indice_fichero, opción_de_reproducción)` para reproducirlo.


###Reproducción de ficheros modulares

Aquí vemos un ejemplo de reproducción de diferentes bandas sonoras, */audio/maxmod/audio_modes*, mediante un menú que permite seleccionar diferente ficheros y modos de reproducción.

Para este proyecto han llamado a la carpeta que contiene los ficheros de audio como *audio*, por tanto hay que hacer una pequeña modificación en el *MakeFile* para reflejar esta diferencia.

###Sincronización de eventos

Para poder sincronizar eventos con instantes de una banda sonora lo primero que necesitamos es crear un `callback` que recibe los códigos de efecto cuando se producen en la reproducción de la banda sonora. Estos *eventos* los podemos introducir con un editor de midi añadiendo a la pista de efectos en los momentos oportunos para lanzar un evento con código x(1,2,3...).

En el primer ejemplo utiliza un solo efecto, SF1 en el canal 4 de la banda sonora y cuando llegan eventos con parámetro igual a 1 cambia la velocidad del sprite para hacerlo botar.

En el segundo ejemplo mediante una simple serie de sentencias `if` consigue diferenciar entre 5 parámetros de efecto diferentes y hacer que sprites diferentes se muevan dependiendo del efecto recibido en cada instante.

##Trabajo autónomo

Aquí hemos ampliado el ejemplo de **Bouncing Ball* añadiendo música de fondo y un efecto para cuando el balón bote. Una dificultad que encontramos fue que los sonidos no se reproducían y resultó ser debido al método de habilitar las interrupciones para el `VBlank`. Este método ya no es necesario y sólo ha sido necesario comentar la llamada para que empezase a funcionar el audio. Por otra parte tuvimos que bajar el volumen de la banda sonora considerablemente para que se escuchase el efecto de bote del balón.

> [Demo](https://www.youtube.com/watch?v=9JY2NaQNHFY).



