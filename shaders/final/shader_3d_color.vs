#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aColor;
layout(location = 4) in vec3 aTangent;
layout(location = 5) in vec3 aBitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;

void main() {
  gl_Position = projection * view * model * vec4(aPos, 1.0f);
  FragPos = vec3(model * vec4(aPos, 1.0f));
  Normal = mat3(transpose(inverse(model))) * aNormal;
}