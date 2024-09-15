# GRAFICAS
 Prácticas de Programación de aplicaciones gráficas (13313011)

## Practica 1
Crearemos el namespace *PAG* que incluirá la clase *Renderer*. <br>
La clase *Renderer* contiene métodos que realizan las funciones de los callbacks. <br>
Sin embargo, GLFW no puede registrar funciones de clases, esto se debe a que está escrito en C y, por tanto, no tiene soporte para las clases ni los métodos de C++. <br>
La solución es emplear funciones estáticas, que, a diferencia de las no estáticas, no pasa el puntero *this* implícitamente y, por tanto, no están asociadas a ninguna instancia particular de una clase, lo que permite que sean manejables por GLFW. <br>

A continuación se muestra un UML que representa el namespace *PAG* con la clase que incluye *Renderer*: <br>

<img src="https://i.imgur.com/ELmKFPj.png">