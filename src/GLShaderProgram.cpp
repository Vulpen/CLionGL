#include "GLShaderProgram.h"
#include <sstream>
#include <iostream>
#include <fstream>

float GLShaderProgram::ScreenWidth;
float GLShaderProgram::ScreenHeight;
glm::mat4x4 GLShaderProgram::ViewMatrix;
glm::mat4x4 GLShaderProgram::ProjectionMatrix;

GLShaderProgram::GLShaderProgram() : mShaderID(0) {
    ScreenWidth = INIT_SCREEN_WIDTH;
    ScreenHeight = INIT_SCREEN_HEIGHT;
}

GLShaderProgram::~GLShaderProgram() {
    glDeleteProgram(mShaderID);
    mShaderID = 0;
}

void GLShaderProgram::use() {
    if (mShaderID > 0) {
        glUseProgram(mShaderID);
    }
}

bool GLShaderProgram::loadAndCompileShaders(const char *vsFilename, const char *fsFilename) {
    string vsString = fileToString(vsFilename);
    string fsString = fileToString(fsFilename);
    const GLchar *vsSourcePtr = vsString.c_str();
    const GLchar *fsSourcePtr = fsString.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vsSourcePtr, NULL);
    glShaderSource(fs, 1, &fsSourcePtr, NULL);

    glCompileShader(vs);
    checkCompileErrors(vs, VERTEX);
    glCompileShader(fs);
    checkCompileErrors(fs, FRAGMENT);


    mShaderID = glCreateProgram(); //Shader program is a collection of shaders
    glAttachShader(mShaderID, vs);
    glAttachShader(mShaderID, fs);
    glLinkProgram(mShaderID);

    checkCompileErrors(mShaderID, PROGRAM);


    glDeleteShader(vs); //Delete shaders because they're linked to the program
    glDeleteShader(fs);
    //End Shaders-----------

    mUniformMap.clear();
    return true;
}

void GLShaderProgram::setUniform(const GLchar *name, const GLfloat value) {
    GLint location = getUniformLocation(name);
    glUniform1f(location, value);
}

void GLShaderProgram::setUniform(const GLchar *name, const glm::mat4 &m) {
    GLint location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m));
}

GLint GLShaderProgram::getUniformLocation(const GLchar *name) {
    std::map<string, GLint>::iterator it = mUniformMap.find(name);

    if (it == mUniformMap.end()) {
        mUniformMap[name] = glGetUniformLocation(mShaderID, name);
    }
    return mUniformMap[name];
}

void GLShaderProgram::checkCompileErrors(GLuint shader, ShaderType type) {
    int status = 0;

    if (type == PROGRAM) {
        glGetProgramiv(mShaderID, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length = 0;
            glGetProgramiv(mShaderID, GL_INFO_LOG_LENGTH, &length);

            string errorLog(length, ' ');
            glGetProgramInfoLog(mShaderID, length, &length, &errorLog[0]);
            std::cerr << "Error! Shader program failed on link." << errorLog << std::endl;
        }
    } else {
        //Vertex or Fragment
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            string errorLog(length, ' ');
            glGetShaderInfoLog(shader, length, &length, &errorLog[0]);
            std::cerr << "Error! Shader program failed to compile." << errorLog << std::endl;
        }
    }
}

string GLShaderProgram::fileToString(const string &filename) {
    std::stringstream ss;
    std::ifstream file;

    try {
        file.open(filename, std::ios::in);
        if (!file.fail()) {
            ss << file.rdbuf();
        } else {
            throw std::exception();
        }

        file.close();
    }
    catch (std::exception e) {
        std::cerr << "Could not open shader file" << std::endl;
    }

    return ss.str();
}

glm::vec3 GLShaderProgram::WorldToClip(const glm::vec3 &point) {
    glm::vec4 temp = (GLShaderProgram::ProjectionMatrix * GLShaderProgram::ViewMatrix) * glm::vec4(point, 1);
    return glm::vec3(temp.x, temp.y, temp.z) / temp.z;
}