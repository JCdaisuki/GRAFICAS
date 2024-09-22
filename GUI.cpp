#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_opengl3_loader.h"

#include "GUI.h"

/**
 * @author Juan Carlos González Martínez
 */

PAG::GUI* PAG::GUI::instancia = nullptr;

namespace PAG
{
    PAG::GUI* PAG::GUI::GetInstancia ()
    {
        if ( !instancia )
        {
            instancia = new GUI();
        }

        return instancia;
    }
    void GUI::InicializarImGui(GLFWwindow* window)
    {
        //Inicialización de Dear ImGui,
        IMGUI_CHECKVERSION();
        ImGui::CreateContext ();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        //Completar la inicialización de GLFW y OpenGL
        ImGui_ImplGlfw_InitForOpenGL ( window, true );
        ImGui_ImplOpenGL3_Init ();
    }

    void GUI::RedibujarVentanas(std::string mensaje)
    {
        //Se prepara un nuevo frame para OpenGL y GLFW
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        //Inicia un nuevo frame de ImGui que permite agregar controles en la interfaz gráfica.
        ImGui::NewFrame();

        CrearVentanaMensajes(mensaje);

        //Se renderiza en pantalla
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );
    }

    void GUI::CrearVentanaMensajes(std::string mensaje)
    {
        //Establecemos la posición de la ventana
        ImGui::SetNextWindowPos(ImVec2(mx, my), ImGuiCond_Once);

        //Comenzamos una nueva ventana flotante con el título "Mensajes"
        if (ImGui::Begin("Mensajes"))
        {
            //Escalamos el texto
            ImGui::SetWindowFontScale(1.0f);

            if(mensaje != "") //Emplearemos un string vacio para indicar que se quiere mostrar el último mensaje
            {
                //Agregar texto a la ventana
                ImGui::Text(mensaje.c_str());
                lastMensaje = mensaje;
            }
            else
            {
                ImGui::Text(lastMensaje.c_str());
            }
        }

        ImGui::End();
    }

}