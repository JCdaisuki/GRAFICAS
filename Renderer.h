/**
 * @author Juan Carlos González Martínez
 */

#ifndef Renderer_h
#define Renderer_h

#include <vector>

#include "Material.h"
#include "ShaderProgram.h"
#include "Model.h"

namespace PAG
{
    class Renderer
    {
    private:
        // Puntero al único objeto
        static Renderer* instancia;

        std::vector<Model*> models;
        std::vector<ShaderProgram*> shaderPrograms;
        std::vector<Material*> materials;

        GLuint idVS = 0; // Identificador del vertex shader
        GLuint idFS = 0; // Identificador del fragment shader

    public:
        // - Getter de instancia
        static Renderer* GetInstancia ();

        // - Esta función nicializa las opciones de OpenGL
        void InicializarOpenGL();

        // - Esta función informa de las propiedades del contexto 3D construido.
        std::string MostrarPropiedades();

        // - Esta función será llamada de manera auxiiar cada vez que el área de dibujo OpenGL deba ser redibujada.
        void Refrescar();

        // - Esta función será llamada auxiliarmente cada vez que el área de dibujo OpenGL deba ser redibujada.
        void RefrescarVentana ();

        // - Esta función callback será llamada cada vez que se cambie el tamaño del área de dibujo OpenGL.
        void ModificarTamaño (int width, int height);

        // - Esta función callback será llamada cada vez que se pulse una tecla dirigida al área de dibujo OpenGL.
        void TeclaPulsada (int key, int scancode, int action, int mods );

        // - Esta función callback será llamada cada vez que se pulse algún botón del ratón sobre el área de dibujo OpenGL.
        void AccionRaton (int button, int action, int mods );

        // - Esta función callback será llamada cada vez que se mueva la rueda del ratón sobre el área de dibujo OpenGL.
        static void CambiarColorFondo (float* color);

        void CreaShaderProgram ( std::string ruta );
        void CreaModelo(std::string rutaModelo, std::string nombreModelo);

        Model* GetModelo(std::string nombreModelo);

        ~Renderer();
    };
}

#endif