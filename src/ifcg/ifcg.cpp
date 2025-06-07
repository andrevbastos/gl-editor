#include "ifcg/ifcg.hpp"

namespace ifcg
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	IFCG* IFCG::instance = nullptr;
    GLFWwindow* IFCG::window = nullptr;
    Camera* IFCG::camera = nullptr;
    std::vector<Mesh*> IFCG::renderQueue;
    Shader IFCG::shader;
	GLuint IFCG::width;
	GLuint IFCG::height;

    IFCG::IFCG()
    {
        glfwInit();
    };

    void IFCG::init()
    {
        if (instance == nullptr)
        {
            instance = new IFCG();
            window = NULL;
        }
    };

    void IFCG::terminate()
    {
        if (instance != nullptr)
        {
            terminate_();
        }
    }

    void IFCG::createWindow(GLuint w, GLuint h)
    {
        width = w;
        height = h;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        if (window == nullptr)
        {
            window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);

            if (window == nullptr)
            {
                std::cerr << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
            }
        }

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);
    
        int posX = (vidMode->width - width) / 2;
        int posY = (vidMode->height - height) / 2;
    
        glfwSetWindowPos(window, posX, posY);
        
        glfwFocusWindow(window);

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    };

    void IFCG::destroyWindow()
    {
        if (window)
        {
            glfwDestroyWindow(window);
        } else {
            std::cerr << "Failed to destroy GLFW window" << std::endl;
        }
    };
    
    bool IFCG::shouldClose()
    {
        return glfwWindowShouldClose(IFCG::window);
    };

    void IFCG::clearBuffer(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    };

    void IFCG::readInputs()
    {
        glfwPollEvents();
        processInput();
    };

    void IFCG::processInput() 
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (camera != nullptr) {
            camera->inputs(window);
        }
    };

    void IFCG::swapBuffer()
    {
        glfwSwapBuffers(window);
    };

    void IFCG::setup2D() {
        if (shader.id != 0) {
            shader.terminate();
        }
        if (renderQueue.size() > 0) {
            for (Mesh* mesh : renderQueue) {
                delete mesh;
            }
            renderQueue.clear();
        }
        if (camera != nullptr) {
            delete camera; 
            camera = nullptr; 
        }
        
        shader = Shader("../resources/shaders/default2D_vert.glsl", "../resources/shaders/default2D_frag.glsl");
        camera = new Camera2D(width, height);
        camera->setPos(glm::vec3(0.0f, 0.0f, -0.5f));

        if (glIsEnabled(GL_DEPTH_TEST)) {
            glDisable(GL_DEPTH_TEST);
        }
    };

	void IFCG::setup3D() {
        if (shader.id != 0) {
            shader.terminate(); 
        }
        if (renderQueue.size() > 0) {
            for (Mesh* mesh : renderQueue) {
                delete mesh;
            }
            renderQueue.clear();
        }
        if (camera != nullptr) {
            delete camera; 
            camera = nullptr; 
        }

        shader = Shader("../resources/shaders/default3D_vert.glsl", "../resources/shaders/default3D_frag.glsl");
        camera = new Camera3D(width, height);

        if (!glIsEnabled(GL_DEPTH_TEST)) {
            glEnable(GL_DEPTH_TEST);
        }
    };

    void IFCG::addMesh(Mesh* mesh)
    {
        renderQueue.push_back(mesh);
    };

    void IFCG::removeMesh(Mesh* mesh)
    {
        if (renderQueue.empty()) {
            std::cerr << "No meshes to remove." << std::endl;
            return;
        }
        auto it = std::remove(renderQueue.begin(), renderQueue.end(), mesh);
        if (it != renderQueue.end()) {
            renderQueue.erase(it);
        } else {
            std::cerr << "Mesh not found in the list." << std::endl;
        }
    };

    void IFCG::render()
    {
        shader.activate();
        camera->update(90.0f, 0.1f, 100.0f, shader.id);

        if (renderQueue.empty()) {
            return;
        }
        for (Mesh* mesh : renderQueue)
        {
            mesh->draw();
        }
    };

    void IFCG::terminate_() 
    {
        glfwTerminate();
    };
    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }    
}