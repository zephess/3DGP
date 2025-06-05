#version 120
uniform mat4 uProjection;
uniform mat4 uModel;
attribute vec3 aPosition;
attribute vec2 aTexCoord;
varying vec2 vTexCoord;
void main() {
    gl_Position = uProjection * uModel * vec4(aPosition, 1.0);
    vTexCoord = aTexCoord;
}
