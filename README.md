# GRAFICAS
 Prácticas de Programación de aplicaciones gráficas (13313011)

## Practica 1
Crearemos el namespace *PAG* que incluirá la clase *Renderer*. <br>
La clase *Renderer* contiene métodos que realizan las funciones de los callbacks. <br>
Sin embargo, GLFW no puede registrar funciones de clases, esto se debe a que está escrito en C y, por tanto, no tiene soporte para las clases ni los métodos de C++. <br>
La solución es emplear funciones estáticas, que, a diferencia de las no estáticas, no pasa el puntero *this* implícitamente y, por tanto, no están asociadas a ninguna instancia particular de una clase, lo que permite que sean manejables por GLFW. <br>

A continuación se muestra un UML que representa el namespace *PAG* con la clase que incluye *Renderer*: <br>

<img src="https://i.imgur.com/ELmKFPj.png">


## Practica 2
Empleando la biblioteca ImGui he creado 2 sub-ventanas que se crearan dentro de la ventana principal:
    
- **Mensajes**: Permite mostrar mensajes en lugar de emplear *std::cout*.
- **Fondo**: Permite seleccionar un nuevo color para el fondo de la ventana principal.

El funcionamiento de la ventana Mensajes es simple, al recibir una cadena de caracteres se actualiza el mensaje mostrado. 
Dado que su funcionamiento se encuentra dentro de la función que crea las ventanas, es posible que simplemente querramos actualizar el frame y no cambiar el mensaje, en cuyo caso se pasará una cadena de caracteres vacía que se interpretará como mantener el mensaje ya mostrado.

El funcionamiento de la ventana Fondo es algo más complejo.
Dado que para seleccionar un nuevo color debemos pulsar con el ratón, emplearemos esto a nuestro favor: Cuando se ejecute el callback de haber pulsado el ratón, se comprobará si ha cambiado el color seleccionado, es decir,
si se ha pulsado sobre un nuevo color, en caso positivo, se actualizara el fondo.


## Practica 3
Para el desarrollo de esta practica emplearemos las siguientes funciones en la clase Renderer:
 - **LoadShader()**: Recibiendo la ruta de un archivo que contiene un tipo de Shader, se encargará de leer las propiedades del shader a partir del archivo y crearlo, almacendo su id como una propiedad de Renderer.
 - **CreaShaderProgram()**: Empleando los ids de los shaders cargados, crea y configura un programa de Shaders en OpenGL.
 - **CreaModelo()**: Crea y configura los datos de geometría de un modelo empleando VAOs y VBOs (Con 2 versiones que veremos a continuación).

### Ejercicio VBO Opcional
Primeramente deberemos modificar los archivos *pag03-vs.glsl* y *pag03-fs.glsl* :
 - **pag03-vs**: Añadiremos un segundo atributo de los vértices, el color, localizado en el buffer de colores (1); 
así como una variable de salida que contenga el color y que se mandará al siguiente shader en la cadena, el fragment shader.
Dentro del main asignaremos el color del vértice a la variable de salida.
 - **pag03-fs**: Originalmente asignaba un color fijo a cada fragmento, ahora recibe el color de cada fragmento desde el vertex shader.

 
#### VBOs no entrelazados
Comenzaremos almacenando dos vectores distintos, uno para vértices y otro para colores (No entrelazados).
Por separado generaremos y vincularemos dos VBOs, para posiciones y colores, a partir de los vectores anteriores

#### VBO entrelazado
Esta vez almacenaremos un único vector que contendrá la información de los vectores y sus respectivos colores.
Generaremos y vincularemos el VBO, pero para que OpenGL sepa interpretarlo deberemos indicar las posiciones y colores por separado, es decir,
indicarle que los 3 primeros valores son las posiciones x,y,z seguidos de otros 3 valores que indican los colores r,g,b.

Ambas versiones compartiran la forma en que se utiliza un IBO para referenciar los vértices al dibujar, por lo que no realizaremos cambios en ese aspecto.


### Pregunta
**Si redimensionas la ventana de la aplicación, verás que el triángulo no permanece igual, sino que se deforma al mismo tiempo que la ventana. ¿A qué crees que se
debe este comportamiento?**

Los puntos dentro de la ventana se basan en un sistema de coordenadas, donde (0,0) indica el centro de la ventana, al redimensionarse este centro "cambia" de posición.
Sin embargo, las coordenadas de los vértices del triangulo permanecen constantes, por lo que aunque se redimensione la ventana, el triángulo tratará de mantener sus coordenadas, dandonos el efecto de que varía aunque no sea así.


## Practica 4
<img src="https://i.imgur.com/h38xcu4.png">


## Practica 5
