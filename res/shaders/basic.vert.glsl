#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in mat4 instanceModel;

out vec3 vPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    vPos = (u_model * vec4(aPos, 1.0)).xyz;
    gl_Position = u_projection * u_view * u_model * vec4(aPos, 1.0f);

    //gl_Position = u_projection * u_view * instanceModel * vec4(aPos, 1.0f);
}
