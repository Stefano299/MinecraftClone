//
// Created by stefano on 8/18/24.
//

#include "Shader.h"
#include"helper.h"

void Shader::loadVertex(const char *path) {
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    std::string code = loadShader(path);
    const char* source = code.c_str();
    glShaderSource(vertexID, 1, &source, nullptr);
    glCompileShader(vertexID);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexID, 512, nullptr, infoLog);
        std::cerr << "Errore nella vertex shader " << infoLog << std::endl;
    }
}

void Shader::loadFragment(const char *path) {
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string code = loadShader(path);
    const char* source = code.c_str();
    glShaderSource(fragmentID, 1, &source, nullptr);
    glCompileShader(fragmentID);
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentID, 512, nullptr, infoLog);
        std::cerr << "Errore nella fragment shader " << infoLog << std::endl;
    }
}

void Shader::createProgram() {
    programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

void Shader::useProgram() const{
    glUseProgram(programID);
}

void Shader::changeUniform4M(const std::string& name, const glm::mat4& matrix) const{
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::Shader() {
    vertexID = 0;
    fragmentID = 0;
    programID = 0;
}

void Shader::changeUniformVec3(const std::string &name, float v1, float v2, float v3) const {
    glUniform3f(glGetUniformLocation(programID, name.c_str()), v1, v2, v3);
}

void Shader::changeUniform1i(const std::string &name, int parameter) const{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), parameter);
}
