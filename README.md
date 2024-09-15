# GRAFICAS
 Prácticas de Programación de aplicaciones gráficas (13313011)

## Practica 1
Crear el namespace PAG que incluya la clase Renderer. <br>
La clase Renderer incluira funciones "en español" que realizaran el comportamiento de los callbacks. <br>
GLFW requiere que los callbacks sean static al no poder registrar funciones de clases, dado que las funciones static no emplean puntero this  puede ser llamada directamente por GLFW sin la necesidad de pasar un objeto de clase.