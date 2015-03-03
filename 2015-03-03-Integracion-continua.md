---
layout: post
title: Integración continua
date: 2015-03-03 9:40:00
---

Más de una vez nos hemos despistado, hemos añadido una nueva imagen, la hemos usado temporalmente en el proyecto y finalmente la hemos eliminado del disco pero no hemos eliminado todas las referencias. Si no se limpia con frecuencia el directorio de archivos intermedios el código compilado de estas imágenes permanece en el sistema de ficheros y el compilador puede enlazarlas al código y el desarrollador puede dejar referencias a ellas sin detectar ningún problema.

Esto puede no parecer importante pero cuando abres una pull-request y llueven los comentarios diciendo que el código no compila ya toma más prioridad que la que tenía inicialmente. Para asegurarnos de que no tenemos más problemas de este tipo hemos configurado un servidor de integración continua.

Como nuestro repositorio es privado hemos optado por [MagnumCI](https://magnum-ci.com/). La configuración realmente es sencilla:

1. El proyecto será de tipo `generic` ya que ninguna de las opciones casa muy bien con lo que estamos haciendo (todas son orientadas a desarrollo de servicios web mientras que este proyecto no usa Ruby ni NodeJS sino C y C++).
1. Habrá que declarar dos variables de entorno: {% highlight bash %}
DEVKITPRO=~/devkitPro
DEVKITARM=${DEVKITPRO}/devkitARM
{% endhighlight %}
1. La instalación de dependencias es algo más compleja, usaremos el siguiente script que elaboramos [para preparar nuestro entorno de desarrollo](http://sumolari.github.io/TacticsDS/2015/02/05/p1-instalacion-entorno/). {% highlight bash %}
cd ~/
wget -O ~/devkitARMupdate.pl http://goo.gl/rjbq5P
chmod a+x ~/devkitARMupdate.pl
~/devkitARMupdate.pl
{% endhighlight %}
1. Como `before test execution` nos situaremos en la carpeta con el código fuente del proyecto (ya que en la instalación de dependencias nos hemos cambiado de directorio): {% highlight bash %}
cd ~/TacticsDS
{% endhighlight %}
1. Como comando para ejecutar los tests usaremos únicamente `make` (en realidad nosotros tenemos algunos tests unitarios que se pueden ejecutar con `make test` pero son pequeños tests para verificar el correcto funcionamiento del componente de aritmética en coma fija y realmente no cubre demasiada parte del proyecto, de modo que con confirmar que el proyecto se compila nos es suficiente, de momento).

Con esto podemos comprobar el estado del proyecto cada vez que hacemos `push` al repositorio y corregir rápidamente estos despistes. 

![Estado de la rama master](https://magnum-ci.com/status/ec748ea24dd8096d90e6b94241cf6151.png)