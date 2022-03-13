#ifndef CLIONGL_PLAYER_H
#define CLIONGL_PLAYER_H

#include "GLBuffer.h"
#include "GLVertexArray.h"
#include "GLShaderProgram.h"
#include <glad.h>
#include <glm.hpp>
#include <iostream>

/**
 * For asteroids, need to handle the player wrapping around the screen.
 * Perhaps a screen space offset could be implemented and draw the ship 4 times?
 */
class Player {
public:
    Player();
    void Draw();
    void HandleInput(int x, int y);
    void Update();
private:
    glm::vec2 forwardVector();
    GLVertexArray mVertexArray;
    GLBuffer mVertexBuffer;
    GLBuffer mIndexBuffer;
    GLShaderProgram mShaderProgram;
    float scale;
    float rotationRads;
    glm::vec2 location;
};


#endif //CLIONGL_PLAYER_H
