#shader vertex

/* ================================================================= */
/*                             VERTEX                                */
/* ================================================================= */

#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = position;
}


#shader fragment

/* ================================================================= */
/*                             FRAGMENT                              */
/* ================================================================= */

#version 330 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(255, 0, 0, 1);
}
