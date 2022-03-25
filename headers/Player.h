#ifndef CLIONGL_PLAYER_H
#define CLIONGL_PLAYER_H

#include "GLBuffer.h"
#include "GLVertexArray.h"
#include "GLShaderProgram.h"
#include "Transform2D.h"
#include <ext.hpp>
#include <glad.h>
#include <glm.hpp>
#include <iostream>

static const float GHOST_DISPLAY_DISTANCE = 0.97;
static const float GHOST_REPLACE_DISTANCE = 1.09;

/**
 * For asteroids, need to handle the player wrapping around the screen.
 * Perhaps a screen space offset could be implemented and draw the ship 4 times?
 */
class Player {
public:
    Player(void (*bulletSpawnFunc)(glm::vec2, glm::vec2));
    void Draw();
    void HandleInput(int x, int y, bool fire);
    void Update();
private:
    GLVertexArray mVertexArray;
    GLBuffer mVertexBuffer;
    GLBuffer mIndexBuffer;
    GLShaderProgram mShaderProgram;
    Transform2D mTransform;
    Transform2D mGhostTransform;
    glm::vec2 getBulletSpawnPoint();
    void (*spawnBulletCallback)(glm::vec2, glm::vec2);
    bool isWithinScreen(glm::vec2 location);
};


#endif //CLIONGL_PLAYER_H
