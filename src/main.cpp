#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.hpp"
#include "Shader.hpp"
#include "DanceFloor.hpp"

int main()
{
    if (!initialiseGLFW())
        return -1;

    WindowProperties winProp;
    winProp.width = 1920;
    winProp.height = 1080;
    Window win(winProp);

    if (!gladLoadGLLoader(win.getProcAddress()))
    {
        std::cerr << "Error initializing GLAD";
        exit(-1);
    }

    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL(glEnable(GL_BLEND));
    GL(glEnable(GL_DEPTH_TEST));


    GL(glEnable(GL_CULL_FACE));

    Shader shady("src/shaders/basic.vs", "src/shaders/basic.fs");
    GL(glUseProgram(shady.ID));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(win.getGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 400");

    bool show_demo_window = true;

    DanceFloor danceFloor(16,9,std::chrono::milliseconds(1000));
    auto proj = glm::mat4(1.0f);

    while (!win.shouldClose())
    {
        win.swapBuffers();
        win.pollEvents();

        GL(glClearColor(0.0f, 1.0f, 1.0f, 1.0f));
        GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        danceFloor.draw();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Press Escape to close the window
        if (win.getKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            win.setShouldClose(true);
        }

            danceFloor.update();
    }


    terminateGLFW();
}