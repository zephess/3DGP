#version 120
uniform sampler2D inTexture;
varying vec2 vTexCoord;
void main() {
    vec4 tex = texture2D(inTexture, vTexCoord);
    gl_FragColor = tex;
}
