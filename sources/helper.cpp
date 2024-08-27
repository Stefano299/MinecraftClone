//
// Created by stefano on 8/18/24.
//

#include"../headers/helper.h"
#include<cstdlib>
#include<ctime>

#include <string>
#include <fstream>
#include <sstream>

std::string loadShader(const char* path){
    std::string shaderCode;
    std::ifstream shaderFile;
    // ensure ifstream objects can throw exceptions:
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        shaderFile.open(path);
        std::stringstream shaderStream;
        // read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        shaderCode   = shaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return shaderCode;
}

int probability(float prob){
    int probNum = prob*10;
    int num = 1+rand()%1000; //da 1 a 1000
    std::cout << num << " "  << probNum << std::endl;
    if(num <= probNum)
        return 1;
    else
        return 0;
}

int getSign(int x){
    if(x > 0)
        return 1;
    else if(x < 0)
        return -1;
    else
        return 0;
}

void showVectorInfo(const glm::vec3& vec){
    std::cout << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << std::endl;
}
