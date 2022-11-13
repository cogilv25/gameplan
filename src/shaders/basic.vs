#version 400 core

in vec3 pPosition;
in vec4 pColour;
out vec4 vColour;

void main()
{
    gl_Position = vec4(pPosition.xy, 0.0, 1.0);

    vColour = pColour;
}