//
// Created by stefano on 7/25/24.
//

#ifndef OPENGL_HELPER_H
#define OPENGL_HELPER_H

#include<iostream>
#include <string>
#include <fstream>
#include <sstream>

std::string loadShader(const char* path);
int probability(float prob); //Ritorna 1 con una probabilità = prob (massimo una cifra decimale)

#endif //OPENGL_HELPER_H
