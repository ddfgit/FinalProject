#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "GL/glew.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

/* CLASS: Billboard */
class Billboard
{
public:
    
    /* Default constructor & Constructor */
    Billboard(const Shader& _shader,
              const Texture& _texture,
              GLfloat _size = 0.5f)
        : shader(_shader),
          texture(_texture),
          size(_size)
    { // Do initialization
        init();
    }

    /* The function to draw this billboard */
    void draw(Camera camera, GLuint texture_unit)
    {
        shader.install();
        glBindVertexArray(VAO);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        texture.bind(texture_unit);
        shader.setUniform1i("texture_sampler", texture_unit);

        // Draw this billboard
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_BLEND);
        glBindVertexArray(0);
        shader.uninstall();
    }

private:

    /* PRIVATE MEMBER
    ** Initiate all parameters in particle system */
    void init()
    {
        // The vertex coordinates and texture coordinates
        GLfloat billboard_quad[] =
        {
             size,  size, 0.0f, 1.0f, 1.0f,
             size, -size, 0.0f, 1.0f, 0.0f,
            -size, -size, 0.0f, 0.0f, 0.0f,

             size,  size, 0.0f, 1.0f, 1.0f,
            -size, -size, 0.0f, 0.0f, 0.0f,
            -size,  size, 0.0f, 0.0f, 1.0f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        // The data of VBO is shared by every particle (instancing technique!)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(billboard_quad), billboard_quad, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    /* PRIVATE MEMBER
    ** A specific shader for rendering particles */
    Shader shader;

    /* PRIVATE MEMBER
    ** The texture we use to attach to each particle */
    Texture texture;

    /* PUBLIC MEMBER
    ** The size of snowflake (Actually the edge length of cube or square) */
    GLfloat size;

    /* PRIVATE MEMBERS
    ** The VAO and VBOs of the particle system */
    GLuint VAO, VBO;
};

#endif
