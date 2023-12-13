uniform sampler2D texture;
uniform float height;

void main() {
    vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);
    float gradient = gl_FragCoord.y / height;
    gl_FragColor = vec4(texColor.rgb * gradient, texColor.a);
}
