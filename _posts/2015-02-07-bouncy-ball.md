---
layout: post
title: How to Make a Bouncing Ball Game
date: 2015-02-07 09:40:00
---

> Esta entrada relata la experiencia de [Lluís](http://llu.is) siguiendo el primer tutorial propuesto en clase.

La finalidad del [tutorial](http://ekid.nintendev.com/bouncy/) es hacer un pequeño juego para la Nintendo DS donde una pelota verde rebota contra el suelo.

Mediante las flechas podemos movernos en el eje horizontal, desplazándose también la pelota (que se ve afectada por el rozamiento con el aire). También podemos hacer que la pelota rebote más alto o más bajo mediante las flechas verticales, pero la pelota nunca dejará de rebotar.

A continuación detallo mis progresos e impresiones a lo largo del tutorial, sección a sección. El código completo está disponible en [Github](https://github.com/Sumolari/BouncyBall), donde hay una Release (Tag) por cada capítulo donde el código se modificó lo suficiente como para mostrar cambios significativos de cara al jugador.

## Progreso

### Preparación

Teniendo preparado el entorno de trabajo de antemano en este paso lo único que tuve que hacer fue descargar el archivo comprimido con los recursos. Curiosamente en un primer momento descargué las imágenes directamente de la tabla pero éstas no tienen las mismas dimensiones que las que contiene el paquete comprimido.

### Preparando tu proyecto

Es una lectura interesante y se obtiene el primer ejecutable. El estado del proyecto se corresponde con el commit [4b7cb2](https://github.com/Sumolari/BouncyBall/tree/4b7cb265b175ac21b3f46b5b9bae8da958545c6f).

![STEP 1](https://raw.githubusercontent.com/Sumolari/BouncyBall/master/porfolio/Step_1.png)

### Diseñando

En este capítulo se hace una pequeña declaración de intenciones y una breve introducción de los diferentes modos de vídeo para los fondos que admite la consola. No se escribe código.

### Flujo del programa

Otro capítulo teórico en el que no se añade código aunque se nos introduce la utilidad del método `swiWaitForVBlank();`.

### Bancos VRAM

Este es un capítulo que me confundió bastante y que hasta que no pruebe en profundidad más funciones que ofrece la consola seguirá siendo un tanto misterioso para mí. De todos los bancos de memoria que introduce usamos tan sólo dos y no hacemos uso ni mucho menos de todos los usos que admiten los bancos.

No se introdujo código que afectase a la percepción del jugador en este capítulo.

### Conversión de gráficos

Se explica la necesidad de usar Grit y cómo convertir los gráficos a un formado legible por la consola. La mayoría de los cambios los acabara el fichero `Makefile` si bien se modifican algunos ficheros de configuración de Grit de las imágenes.

En el commit [a820a0](https://github.com/Sumolari/BouncyBall/tree/a820a0b0ccf3776f70b24b80290ae86eeb0adc67) ya están todos los cambios de este apartado.

### Cargando gráficos

Tras explicar cómo cargar los fondos por fin tenemos a nuestra disposición un ejecutable que muestra algo más que una pantalla en blanco.

El commit [4cb97a](https://github.com/Sumolari/BouncyBall/commit/4cb97a2aafdda34f6da594df4b9a019a068a22c1) incluye los cambios de esta sección.

![STEP 2](https://raw.githubusercontent.com/Sumolari/BouncyBall/master/porfolio/Step_2.png)

### El fondo

Se introduce por primera vez la estructura de un registro de la Nintendo DS, se explican sus diferentes bits y cómo añadir un degradado y un muro de ladrillos.

Algunas cosas de este capítulo no terminaron de gustarme demasiado (no soy ningún fan de trabajar de trabajar "a pelo" a tan bajo nivel) y ya comenzó a rondarme la idea de componer un pequeño framework que se encargase de trabajar con los bits a bajo nivel, aunque todavía era sólo una idea.

Lo que sí añadí fue una utilidad para poder imprimir mensajes por la consola. La Nintendo DS no tiene consola de debug, o al menos depende del emulador que se use. En DeSmuME no he encontrado consola de debug sin embargo rebuscando en el código fuente del toolkit vi que había un método de debug bastante sospechoso, `nocashMessage(char *)` que permitía escribir cadenas de texto en la consola de debug de No$Gba, versión debug, así que preparé un método con el mismo perfil que `printf` de C de tal manera que pudiese imprimir mensajes por consola a voluntad de forma cómoda.

Todo esto se encuentra en el commit [6399e4](https://github.com/Sumolari/BouncyBall/commit/6399e46f2c26a6bda2885ec88a6f91522abfe1e3).

![STEP 3](https://raw.githubusercontent.com/Sumolari/BouncyBall/master/porfolio/Step_3.png)

### Transparencias

Más registros. Al principio no entendí del todo cómo funcionaba la cosa pero según avanzaban los capítulos regresé a este punto y creo que entendí mejor la estructura de los registros y las limitaciones de la consola.

Finalmente se añade transparencia al degradado superior del fondo, como puede verse en el commit [41089f](https://github.com/Sumolari/BouncyBall/commit/41089f9abcda324f5bcf0d9245dcaaa95ae50300).

![STEP 4](https://raw.githubusercontent.com/Sumolari/BouncyBall/master/porfolio/Step_4.png)

### Cargar gráficos para sprites

La idea del framework tomaba fuerza según avanzaban los capítulos. Algunas de las novedades que se introducen en este capítulo las introduzco directamente en el framework mientras que otras se quedan fuera.

No hay cambios visibles para el usuario pero el commit asociado es [9c870f](https://github.com/Sumolari/BouncyBall/commit/9c870fba4f83b2095bddae0d5bcd8639382a45a1).

### Mostrando sprites

Hasta aquí llegó mi paciencia. No solamente hay que usar registros para trabajar con los sprites sino que además hay que usar 3 registros diferentes manipulando bits en posiciones incómodas, de modo que decido embarcarme en la aventura de programar un framework que me abstraiga de todas esas operaciones de bajo nivel.

Iluso de mí, no sabía lo que me esperaba: el tutorial que hasta entonces parecía muy claro empezaba a no parecérmelo tanto: muchos valores que aparecen como constantes no están claros cómo se obtienen (sobre todo en los capítulos posteriores) o cómo deducir qué valor debería usar en una situación diferente.

Pese a todo en el commmit [c198be](https://github.com/Sumolari/BouncyBall/commit/c198beaa8205cbee2bfd6729066636e122b95aae) hay una versión funcional de lo explicado a lo largo del tutorial hasta este punto, aunque fuertemente basada en el framework en desarrollo.

![STEP 5](https://raw.githubusercontent.com/Sumolari/BouncyBall/master/porfolio/Step_5.png)

### Aritmética de coma entera

"¿Pero qué demonios?" fue lo primero que me vino a la cabeza tras acabar de leer este capítulo. La motivación era legítima pero tener que operar así me parecía un jaleo tremendo, sobre todo al ver en el capítulo siguiente que el autor decide no implementar ningún tipo de método auxiliar, macro o similar para hacer más legibles los cálculos en coma entera.

Inicialmente quise incorporar todas estas operaciones al framework y de hecho hay diversos commits que incluyen una clase para trabajar con coma entera sin embargo la implementación original de las operaciones tenía errores y al final acabé reescribiendo bastantes funciones. En vista de que ni corrigiendo esas funciones conseguía hacer funcionar el código decidí dejar de lado este componente del framework para añadirlo en un futuro.

### El balón hinchable

Se introduce una estructura para trabajar con la pelota, sin embargo yo estaba usando C++ así que decidí trabajar desde el primer momento con clases.

El resultado de este capítulo puede verse en el commit [4a89a3](https://github.com/Sumolari/BouncyBall/commit/4a89a3ed475c9ef5c4fea1d8f7e181bf777643c7).

![STEP 6](https://raw.githubusercontent.com/Sumolari/BouncyBall/master/porfolio/Step_6.png)

![STEP 6](https://raw.githubusercontent.com/Sumolari/BouncyBall/master/porfolio/Step_6.gif)

### Aplastando cosas

El tema de transformaciones no me pilla por sorpresa: el cuatrimestre pasado cursé sistemas gráficos interactivos y me imaginaba cómo funcionaría la cosa en la Nintendo DS.

Añadí más funciones al framework para manejar las transformaciones, y el resultado puede verse en el [último commit del repositorio](https://github.com/Sumolari/BouncyBall/tree/3f6233c8f5481f976132b110dcb4f19f0cf0b898).

![STEP 7](https://raw.githubusercontent.com/Sumolari/BouncyBall/master/porfolio/Step_7.png)

![STEP 7](https://raw.githubusercontent.com/Sumolari/BouncyBall/master/porfolio/Step_7.gif)

### Sonido

Este capítulo brilla por su ausencia. La página no existe hoy en día ni tampoco existía en 2009 (hasta donde pude buscar con [Wayback Machine](http://archive.org/web/)), así que no he podido hacer nada de sonido.

## Problemas

Ha sido bastante frustrante hacer el tutorial mientras desarrollaba el framework. En muchas ocasiones no estaba seguro de cómo generalizar partes del programa porque el autor no dejaba claro por qué usaba un valor concreto. Intuyo que más adelante encontraré más cosas que añadir a esta lista de puntos no claros.

## Framework

El framework me ha parecido el producto más interesante del tutorial, además de romper un poco de mano con la consola, y tengo muchas ganas de que trabajar en grupo en su desarrollo. Creo que nos vendrá muy bien para abstraernos del bajo nivel que ofrece el toolkit y nos permitirá avanzar más rápido en el desarrollo del videojuego y enfrentándonos a menos bugs.

El framework está documentado con Doxygen y se puede generar la docuemntación mediante `make doc`.



