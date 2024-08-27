//
// Created by stefano on 8/18/24.
//

#ifndef LIGHTING_SHADER_H
#define LIGHTING_SHADER_H

#include <iostream>
#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
private:
    unsigned int vertexID;
    unsigned int fragmentID;
    unsigned int programID;
public:
    Shader();
    void loadVertex(const char* path);
    void loadFragment(const char* path);
    void createProgram();
    void changeUniform4M(const std::string& name, const glm::mat4& matrix) const;
    void changeUniformVec3(const std::string& name, float v1, float v2, float v3) const;
    void changeUniform1i(const std::string& name, int parameter) const;
    void useProgram() const;
};


#endif //LIGHTING_SHADER_H
