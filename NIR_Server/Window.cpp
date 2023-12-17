#include "Window.hpp"

Window::Window(int weight, int height, const char* title)
    : m_window(nullptr)
    , m_width(weight)
    , m_height(height)
    , m_title(title)
    , m_show_demo(true)
    , m_glsl_version("#version 130")
{
    m_userInterface = std::make_unique<UserInterface>(this);
}

void Window::onInit()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    if (m_window == nullptr)
        return;

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    m_userInterface->onInit();
}

void Window::onRender()
{
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while (!glfwWindowShouldClose(m_window))
    {
        m_frameStart = std::chrono::high_resolution_clock::now();
        glfwPollEvents();

        // ImGui
        m_userInterface->onRender();

        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);

        m_frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> frameDuration = m_frameEnd - m_frameStart;
        m_fps = 1000.0 / frameDuration.count();
    }

    onDestroy();
}

void Window::onDestroy()
{
    // Cleanup
    m_userInterface->onDestroy();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}