#include <iostream>
#include <filesystem>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_opengl3_loader.h"
#include "imgui/imgui_stdlib.h"

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

    float* GUI::GetColorFondo()
    {
        return colorFondo;
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
        CrearVentanaColores();
        CrearVentanaShaders();

        //Se renderiza en pantalla
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );

        if(shaderArchivo != "")
        {
            throw shaderArchivo;
        }
    }

    void GUI::CrearVentanaMensajes(std::string mensaje)
    {
        //Establecemos la posición y tamaño de la ventana
        ImGui::SetNextWindowPos(ImVec2(mx, my), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(600, 115), ImGuiCond_Once);

        //Comenzamos una nueva ventana flotante con el título "Mensajes"
        if (ImGui::Begin("Mensajes"))
        {
            //Escalamos el texto
            ImGui::SetWindowFontScale(1.0f);

            if(mensaje != "") //Emplearemos un string vacio para indicar no hay ningún mensaje nuevo
            {
                mensajes.push_back(mensaje);
            }

            for(int i = 0; i < mensajes.size(); i++)
            {
                ImGui::TextUnformatted(mensajes[i].c_str());
            }
        }

        ImGui::End();
    }

    void GUI::CrearVentanaColores()
    {
        //Establecemos la posición y tamaño de la ventana
        ImGui::SetNextWindowPos(ImVec2(cx, cy), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(200, 220), ImGuiCond_Once);

        if (ImGui::Begin("Fondo"))
        {
            // Color picker completo (RGBA) de ImGui
            ImGui::ColorPicker4("Color:", colorSeleccionado, ImGuiColorEditFlags_PickerHueWheel);
        }

        ImGui::End();
    }

    void GUI::CrearVentanaShaders()
    {
        ImGui::SetNextWindowPos(ImVec2(sx, sy), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(140, 80), ImGuiCond_Once);

        ImGui::Begin("Cargar Shader");

        ImGui::InputText("##shader", buffer, sizeof(buffer), ImGuiInputTextFlags_AutoSelectAll);

        if (ImGui::Button("Load") && buffer != "")
        {
            shaderArchivo = buffer;
        }

        ImGui::End();
    }

    bool GUI::CambioColor()
    {
        for(int i = 0; i < 4; i++)
        {
            //Comprobamos si se ha cambiado de color en ColorPicker
            if(colorFondo[i] != colorSeleccionado[i])
            {
                //Almacenamos el nuevo color seleccionado
                for(int j = i; j < 4; j++)
                {
                    colorFondo[j] = colorSeleccionado[j];
                }

                return true;
            }
        }
        return false;
    }

    void GUI::FinalizarImGui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext ();
    }

    GUI::~GUI()
    {
        // Llamamos a FinalizarImGui para liberar los recursos relacionados con ImGui
        FinalizarImGui();

        if (instancia)
        {
            delete instancia;
            instancia = nullptr;
        }
    }
}