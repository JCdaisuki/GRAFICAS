/**
 * @author Juan Carlos González Martínez
 */

#include "GUI.h"

#include <iostream>
#include <vector>
#include <filesystem>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_stdlib.h"
#include <GLFW/glfw3.h>

#include "Camera.h"

PAG::GUI* PAG::GUI::instancia = nullptr;

namespace PAG
{
    GUI* GUI::GetInstancia ()
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

    std::string GUI::RedibujarVentanas()
    {
        //Se prepara un nuevo frame para OpenGL y GLFW
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        //Inicia un nuevo frame de ImGui que permite agregar controles en la interfaz gráfica.
        ImGui::NewFrame();

        CrearVentanaMensajes();
        CrearVentanaColores();
        CrearVentanaModelShaders();
        CrearVentanaCamera();

        if(shaderArchivo != "")
        {
            isShader = true;
            return shaderArchivo;
        }

        if(modelArchivo != "")
        {
            isShader = false;
            return modelArchivo;
        }

        return "";
    }

    void GUI::finalizaRedibujarVentanas ()
    {
        //Se renderiza en pantalla
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );
    }


    void GUI::CrearVentanaMensajes()
    {
        //Establecemos la posición y tamaño de la ventana
        ImGui::SetNextWindowPos(ImVec2(mx, my), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(600, 115), ImGuiCond_Once);

        //Comenzamos una nueva ventana flotante con el título "Mensajes"
        if (ImGui::Begin("Mensajes"))
        {
            //Escalamos el texto
            ImGui::SetWindowFontScale(1.0f);

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

    void GUI::CrearVentanaModelShaders()
    {
        ImGui::SetNextWindowPos(ImVec2(sx, sy), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(180, 250), ImGuiCond_Once);

        ImGui::Begin("Modelo y Shader");

        ImGui::Text("Cargar Modelo:");
        ImGui::InputText("##modelo", bufferModel, sizeof(bufferModel), ImGuiInputTextFlags_AutoSelectAll);

        if (ImGui::Button("Load Modelo") && bufferModel != "")
        {
            modelArchivo = bufferModel;
        }

        ImGui::Separator();

        if(nombreModelo == "")
        {
            ImGui::Text("Ningún modelo cargado");
        }
        else
        {
            ImGui::Text(("Modelo actual: " + nombreModelo).c_str());
        }

        if (ImGui::BeginCombo(".", modelosCargados.empty() ? "" : modelosCargados[modeloSeleccionado].c_str()))
        {
            for (int i = 0; i < modelosCargados.size(); i++)
            {
                bool isSelected = (modeloSeleccionado == i);

                if (ImGui::Selectable(modelosCargados[i].c_str(), isSelected))
                {
                    modeloSeleccionado = i;
                    nombreModelo = modelosCargados[i];
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if(nombreModelo != "")
        {
            ImGui::Separator();
            ImGui::Text("Modo de Visualización");

            if (ImGui::BeginMenu("Select mode"))
            {
                if (ImGui::MenuItem("Modo Plano"))
                {

                }

                if (ImGui::MenuItem("Modo Alambre"))
                {

                }

                ImGui::EndMenu();
            }
        }

        ImGui::Separator();

        ImGui::Text("Cargar Shader:");
        ImGui::InputText("##shader", bufferShader, sizeof(bufferShader), ImGuiInputTextFlags_AutoSelectAll);

        if (ImGui::Button("Load Shader") && bufferShader != "")
        {
            shaderArchivo = bufferShader;
        }

        ImGui::End();
    }

    void GUI::modeloCreadoCorrectamente()
    {
        nombreModelo = modelArchivo;
        modelosCargados.push_back(nombreModelo);
    }

    void GUI::CrearVentanaCamera()
    {
        ImGui::SetNextWindowPos(ImVec2(cax, cay), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(200, 180), ImGuiCond_Once);

        ImGui::Begin("Camera");

        ImGui::Text("Movement");

        if (ImGui::BeginMenu("Select Movement"))
        {
            if (ImGui::MenuItem("Zoom"))
            {
                menuSeleccionado = "Zoom";
                movementText = "Angle";
            }
            if (ImGui::MenuItem("Pan"))
            {
                menuSeleccionado = "Pan";
                movementText = "Direction";
            }
            if (ImGui::MenuItem("Tilt"))
            {
                menuSeleccionado = "Tilt";
                movementText = "Direction";
            }
            if (ImGui::MenuItem("Dolly"))
            {
                menuSeleccionado = "Dolly";
                movementText = "Direction";
            }
            if (ImGui::MenuItem("Crane"))
            {
                menuSeleccionado = "Crane";
                movementText = "Direction";
            }
            if (ImGui::MenuItem("Orbit"))
            {
                menuSeleccionado = "Orbit";
                movementText = "Latitude";
            }

            ImGui::EndMenu();
        }

        ImGui::Separator();
        ImGui::Text(menuSeleccionado.c_str());
        ImGui::Separator();
        ImGui::Text(movementText.c_str());

        if(menuSeleccionado == "Zoom")
        {
            ImGui::SliderInt("##Zoom", &zoom, -100, 100);
            Camera::GetInstancia()->Zoom(-zoom);
        }
        else if(menuSeleccionado == "Pan")
        {
            if (ImGui::Button("<- Left"))
            {
                Camera::GetInstancia()->Pan(-1);
            }
            ImGui::SameLine(); // Colocar el siguiente botón en la misma línea

            if (ImGui::Button("Right ->"))
            {
                Camera::GetInstancia()->Pan(1);
            }
        }
        else if(menuSeleccionado == "Tilt")
        {
            if (ImGui::Button("^ Up ^"))
            {
                Camera::GetInstancia()->Tilt(1);
            }

            ImGui::SameLine();

            if (ImGui::Button("v Down v"))
            {
                Camera::GetInstancia()->Tilt(-1);
            }
        }
        else if(menuSeleccionado == "Dolly")
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 27);
            if (ImGui::Button("^ Back ^"))
            {
                Camera::GetInstancia()->Dolly("back", 0.1);
            }

            if (ImGui::Button("<- Left"))
            {
                Camera::GetInstancia()->Dolly("left", 0.1);
            }

            ImGui::SameLine();

            if (ImGui::Button("Right ->"))
            {
                Camera::GetInstancia()->Dolly("right", 0.1);
            }

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 27);
            if (ImGui::Button("v Front v"))
            {
                Camera::GetInstancia()->Dolly("front", 0.1);
            }
        }
        else if(menuSeleccionado == "Crane")
        {
            if (ImGui::Button("^ Up ^"))
            {
                Camera::GetInstancia()->Crane(0.1);
            }

            ImGui::SameLine();

            if (ImGui::Button("v Down v"))
            {
                Camera::GetInstancia()->Crane(-0.1);
            }
        }
        else if(menuSeleccionado == "Orbit")
        {
            if (ImGui::Button("^ North ^"))
            {
                Camera::GetInstancia()->Orbit(10, 0);
            }

            ImGui::SameLine();

            if (ImGui::Button("v South v"))
            {
                Camera::GetInstancia()->Orbit(-10, 0);
            }

            ImGui::Text("Longitude");

            if (ImGui::Button("<- West"))
            {
                Camera::GetInstancia()->Orbit(0, 10);
            }

            ImGui::SameLine();

            if (ImGui::Button("East ->"))
            {
                Camera::GetInstancia()->Orbit(0, -10);
            }
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

    void GUI::LimpiarRutas()
    {
        bufferShader[0] = '\0';
        shaderArchivo = "";

        bufferModel[0] = '\0';
        modelArchivo = "";
    }

    void GUI::FinalizarImGui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext ();
    }

    void GUI::addMensaje ( std::string mensaje )
    {
        mensajes.push_back(mensaje);
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