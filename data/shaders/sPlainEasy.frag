precision highp float;

varying mediump vec3 v_position;
varying mediump vec3 v_normal;
varying mediump vec2 v_texCoord;

uniform mediump float u_Phase;
uniform mediump vec4  u_CustomColor;

uniform sampler2D s_texture;

void main()
{
    vec4 texel = texture2D(s_texture, v_texCoord);
    //gl_FragColor = vec4(1, 1, 1, 1) * sin((pos.x * pos.x + pos.y * pos.y) * 40.0 + u_Phase);
    gl_FragColor = texel; // * sin((pos.x * pos.x + pos.y * pos.y + pos.z * pos.z) + u_Phase) * u_CustomColor ;
}