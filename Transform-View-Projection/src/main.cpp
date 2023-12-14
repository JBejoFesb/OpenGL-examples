#include <iostream>
#include <string>

#include "Window.h"
#include "Renderer.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

int main()
{
    Window window("Vjezba3", SCR_WIDTH, SCR_HEIGHT);
  
    Model model("res/models/dragon.obj");
    Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");
    Texture tex("res/textures/container.jpg");

    Renderer render;
    while (!window.isClosed())
    {
        window.ProcessInput();
        render.Clear();

        glm::mat4 modelM = glm::mat4(1.0f);
        modelM = glm::rotate(modelM, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        const float radius = 2.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 viewM;
        viewM = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 0.0));

        glm::mat4 projectionM;
        projectionM = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shader.GetID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM));

        int viewLoc = glGetUniformLocation(shader.GetID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewM));

        int projLoc = glGetUniformLocation(shader.GetID(), "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionM));

        model.Draw(shader, tex);

        window.SwapAndPoll();
    }

    window.CloseWindow();

    return 0;
}