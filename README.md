# GRAFICAS
 Prácticas de Programación de aplicaciones gráficas (13313011)

## Practica 1
<p style="text-align: justify;">
Crearemos el namespace *PAG* que incluirá la clase *Renderer*. <br>
La clase *Renderer* contiene métodos que realizan las funciones de los callbacks. <br>
Sin embargo, GLFW no puede registrar funciones de clases, esto se debe a que está escrito en C y, por tanto, no tiene soporte para las clases ni los métodos de C++. <br>
La solución es emplear funciones estáticas, que, a diferencia de las no estáticas, no pasa el puntero *this* implícitamente y, por tanto, no están asociadas a ninguna instancia particular de una clase, lo que permite que sean manejables por GLFW. <br>

A continuación se muestra un UML que representa el namespace *PAG* con la clase que incluye *Renderer*: <br>
</p>
<img src="https://i.imgur.com/ELmKFPj.png">


## Practica 2
<p style="text-align: justify;">
Empleando la biblioteca ImGui he creado 2 sub-ventanas que se crearan dentro de la ventana principal:
    
- **Mensajes**: Permite mostrar mensajes en lugar de emplear *std::cout*.
- **Fondo**: Permite seleccionar un nuevo color para el fondo de la ventana principal.

El funcionamiento de la ventana Mensajes es simple, al recibir una cadena de caracteres se actualiza el mensaje mostrado. 
Dado que su funcionamiento se encuentra dentro de la función que crea las ventanas, es posible que simplemente querramos actualizar el frame y no cambiar el mensaje, en cuyo caso se pasará una cadena de caracteres vacía que se interpretará como mantener el mensaje ya mostrado.

El funcionamiento de la ventana Fondo es algo más complejo.
Dado que para seleccionar un nuevo color debemos pulsar con el ratón, emplearemos esto a nuestro favor: Cuando se ejecute el callback de haber pulsado el ratón, se comprobará si ha cambiado el color seleccionado, es decir,
si se ha pulsado sobre un nuevo color, en caso positivo, se actualizara el fondo.
</p>