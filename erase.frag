uniform sampler2D texture;
uniform vec2 mouse;
uniform float radius;

void main() {
    vec2 pos = gl_FragCoord.xy;
    float dist = distance(pos, mouse);

    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    if (dist < radius) {
        color.a = 0.0;
    }

    gl_FragColor = color;
}
