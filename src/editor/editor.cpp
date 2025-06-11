#include "editor/editor.hpp"

Editor::Editor() 
    : currentMesh(nullptr), meshes(&IFCG::renderQueue), selectState(this), editorState(this), currentState(&selectState) {}

bool Editor::isKeyJustPressed(GLFWwindow* window, int key) {
    int currentState = glfwGetKey(window, key);
    bool justPressed = false;

    if (currentState == GLFW_PRESS && keyStates[key] == GLFW_RELEASE) {
        justPressed = true;
    }

    keyStates[key] = currentState;
    return justPressed;
};

void Editor::changeState()
{
    if (currentState == &selectState) {
        currentState = &editorState;
    } else {
        currentState = &selectState;
    }
};

void Editor::input(GLFWwindow* window) {
    currentState->input(window);

    if (isKeyJustPressed(window, GLFW_KEY_C))
    {
        IFCG::addMesh(new Cube3D(IFCG::shader.id));
    }
    if (isKeyJustPressed(window, GLFW_KEY_T))
    {
        castRay();
    }
};

void Editor::castRay()
{
    double mouseX;
    double mouseY;
    glfwGetCursorPos(IFCG::window, &mouseX, &mouseY);

    double normalizedX = (mouseX / IFCG::width) * 2.0 - 1.0;
    double normalizedY = 1.0 - (mouseY / IFCG::height) * 2.0;

    glm::vec4 ray_clip = glm::vec4(normalizedX, normalizedY, -1.0f, 1.0f);

    glm::mat4 invProjection = glm::inverse(IFCG::camera->getProjectionMatrix());
    glm::vec4 ray_eye = invProjection * ray_clip;

    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

    glm::mat4 invView = glm::inverse(IFCG::camera->getViewMatrix());
    glm::vec4 ray_world = invView * ray_eye;

    glm::vec3 ray_direction = glm::normalize(glm::vec3(ray_world));
    glm::vec3 ray_origin = glm::vec3(invView[3]);

    float line_length = 100.0f;
    glm::vec3 ray_end_point = ray_origin + ray_direction * line_length;

    currentVertex = checkRayCol(ray_origin, ray_end_point, IFCG::camera->getViewMatrix(), IFCG::camera->getProjectionMatrix());
    if (currentVertex != nullptr)
        std::cout << "Current Vertex Pos: (" << currentVertex->x << ", " << currentVertex->y << ", " << currentVertex->z << ")" << std::endl;
    makeLine(ray_origin, ray_end_point);
}

Vertex* Editor::checkRayCol(glm::vec3 ray_origin, glm::vec3 ray_end, glm::mat4 view, glm::mat4 projection)
{
    if (meshes == nullptr) {
        return nullptr;
    }

    glm::vec3 ray_direction = glm::normalize(ray_end - ray_origin);

    Mesh* closestHitMesh = nullptr;
    Vertex* closestHitVertexPtr = nullptr;
    float minDistanceAlongRay = std::numeric_limits<float>::max();

    const float VERTEX_HIT_RADIUS = 0.1f;

    for (Mesh* currentMeshPtr : *meshes) {
        if (currentMeshPtr == nullptr) {
            continue;
        }

        for (size_t i = 0; i < currentMeshPtr->vertices.size(); ++i) {
            Vertex& currentVertex = currentMeshPtr->vertices[i];
            
            glm::vec4 localVertexPosHom = glm::vec4(currentVertex.x, currentVertex.y, currentVertex.z, 1.0f);
            
            glm::vec4 worldVertexPosHom = currentMeshPtr->model * localVertexPosHom; 
            
            glm::vec3 worldVertexPos = glm::vec3(worldVertexPosHom);
            
            glm::vec3 originToVertex = worldVertexPos - ray_origin;
            float t = glm::dot(originToVertex, ray_direction);

            if (t < 0.0f) {
                continue;
            }

            glm::vec3 closestPointOnRay = ray_origin + ray_direction * t;
            float distanceSq = glm::distance2(worldVertexPos, closestPointOnRay);

            if (distanceSq <= (VERTEX_HIT_RADIUS * VERTEX_HIT_RADIUS)) {
                if (t < minDistanceAlongRay) {
                    minDistanceAlongRay = t;
                    closestHitMesh = currentMeshPtr;
                    closestHitVertexPtr = &currentVertex;
                }
            }
        }
    }

    return closestHitVertexPtr;
}

void Editor::makeLine(glm::vec3 origin, glm::vec3 end)
{
    float d = 0.01f;
    IFCG::addMesh(new Mesh3D({
            Vertex(origin.x + d, origin.y + d, origin.z, 1.0f, 0.0f, 0.0f, 1.0f),
            Vertex(origin.x + d, origin.y - d, origin.z, 1.0f, 0.0f, 0.0f, 1.0f),
            Vertex(origin.x - d, origin.y + d, origin.z, 1.0f, 0.0f, 0.0f, 1.0f),
            Vertex(origin.x - d, origin.y - d, origin.z, 1.0f, 0.0f, 0.0f, 1.0f),
            Vertex(end.x + d, end.y + d, end.z, 1.0f, 0.0f, 0.0f, 1.0f), 
            Vertex(end.x + d, end.y - d, end.z, 1.0f, 0.0f, 0.0f, 1.0f), 
            Vertex(end.x - d, end.y + d, end.z, 1.0f, 0.0f, 0.0f, 1.0f), 
            Vertex(end.x - d, end.y - d, end.z, 1.0f, 0.0f, 0.0f, 1.0f)},
        {
            0, 1, 2,
            2, 1, 3,
            4, 6, 5,
            6, 7, 5,
            0, 2, 4,
            4, 2, 6,
            1, 3, 5,
            5, 3, 7,
            0, 4, 1,
            1, 4, 5,
            2, 3, 6,
            6, 3, 7
        }, 
        IFCG::shader.id
    ));
}