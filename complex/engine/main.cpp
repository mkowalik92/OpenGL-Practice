#include <stdio.h>
#include <glad/glad.h> // Need to include BEFORE GLFW
#include <GLFW/glfw3.h>

#include "shader.h"

// Window Settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

/* PROTOTYPES */
GLFWwindow* InitEngine();
// Callback functions prototypes
void WindowResizeCallback(GLFWwindow* window, int width, int height);
void WindowCloseCallback(GLFWwindow* window);

int main ()
{
  // Holds the main window
  GLFWwindow* mainWindow;

  // Initialize engine
  if (!(mainWindow = InitEngine()))
  {
    printf("Engine failed to start!\n");
    return -1;
  }

  Shader newShader = Shader("shaders/basic.vs", "shaders/basic.fs");
  float vertices[] =
  {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
  };

  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Start render loop
  while (!glfwWindowShouldClose(mainWindow))
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    newShader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(mainWindow);
    glfwPollEvents(); // Check for user input
  }

  return 0;
}

GLFWwindow* InitEngine ()
{
  // Initialize GLFW
  glfwInit();
  // Configure GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Create Window object
  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Engine v0.01", NULL, NULL);
  if (window == NULL)
  {
    printf("Failed to create GLFW window!\n");
    glfwTerminate();
    return window;
  }
  glfwMakeContextCurrent(window);

  // Set window close/resize callback functions
  glfwSetWindowCloseCallback(window, WindowCloseCallback);
  glfwSetFramebufferSizeCallback(window, WindowResizeCallback);

  // Initialize GLAD before calling any OpenGL functions
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to Initialize GLAD\n");
    return window;
  }

  return window;
}

// Window callback function definitions
void WindowCloseCallback (GLFWwindow* window)
{
  glfwSetWindowShouldClose(window, true);
}
void WindowResizeCallback (GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
