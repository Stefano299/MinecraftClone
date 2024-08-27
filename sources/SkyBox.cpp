//
// Created by stefano on 8/24/24.
//

#include "../headers/stb_image.h"
#include "../headers/SkyBox.h"

float vertexPos[] {
// positions
-1.0f,  1.0f, -1.0f,
-1.0f, -1.0f, -1.0f,
1.0f, -1.0f, -1.0f,
1.0f, -1.0f, -1.0f,
1.0f,  1.0f, -1.0f,
-1.0f,  1.0f, -1.0f,

-1.0f, -1.0f,  1.0f,
-1.0f, -1.0f, -1.0f,
-1.0f,  1.0f, -1.0f,
-1.0f,  1.0f, -1.0f,
-1.0f,  1.0f,  1.0f,
-1.0f, -1.0f,  1.0f,

1.0f, -1.0f, -1.0f,
1.0f, -1.0f,  1.0f,
1.0f,  1.0f,  1.0f,
1.0f,  1.0f,  1.0f,
1.0f,  1.0f, -1.0f,
1.0f, -1.0f, -1.0f,

-1.0f, -1.0f,  1.0f,
-1.0f,  1.0f,  1.0f,
1.0f,  1.0f,  1.0f,
1.0f,  1.0f,  1.0f,
1.0f, -1.0f,  1.0f,
-1.0f, -1.0f,  1.0f,

-1.0f,  1.0f, -1.0f,
1.0f,  1.0f, -1.0f,
1.0f,  1.0f,  1.0f,
1.0f,  1.0f,  1.0f,
-1.0f,  1.0f,  1.0f,
-1.0f,  1.0f, -1.0f,

-1.0f, -1.0f, -1.0f,
-1.0f, -1.0f,  1.0f,
1.0f, -1.0f, -1.0f,
1.0f, -1.0f, -1.0f,
-1.0f, -1.0f,  1.0f,
1.0f, -1.0f,  1.0f
};

SkyBox::SkyBox() {
    setPaths();
    setVertices();
    initBuffers();
    initTextures();
    loadShader();
}

void SkyBox::setPaths() {
    paths[0] = "../img/right.jpg";
    paths[1] = "../img/left.jpg";
    paths[2] = "../img/top.jpg";
    paths[3] = "../img/bottom.jpg";
    paths[4] = "../img/front.jpg";
    paths[5] = "../img/back.jpg";
}

void SkyBox::setVertices() {
    for(int i = 0; i < 108; i++){
        vertices[i] = vertexPos[i];
    }
}

void SkyBox::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    glEnableVertexAttribArray(0);
}

void SkyBox::initTextures() {
    glGenTextures(1, &cubeMapText);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapText);
    unsigned char* data;
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(false);
    for(int i = 0; i < 6; i++){
        data = stbi_load(paths[i].c_str(), &width, &height, &nChannels, 0);
        if(data){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else{
            std::cerr << "errore nel caricamento della texture della cubemap" << std::endl;
        }
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void SkyBox::loadShader() {
    shader.loadVertex("../shaders/vSkyBox.glsl");
    shader.loadFragment("../shaders/fSkyBox.glsl");
    shader.createProgram();
    shader.useProgram();
    shader.changeUniform1i("cubeTexture", 0);
}

void SkyBox::draw(const glm::mat4 &projection, const glm::mat4 &view) const {
    //glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    shader.useProgram();
    shader.changeUniform4M("view", view);
    shader.changeUniform4M("projection", projection);
    glBindVertexArray(VAO);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapText);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
    //glDepthMask(GL_TRUE);
}
