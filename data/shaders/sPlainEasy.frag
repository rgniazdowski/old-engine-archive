precision highp float;

varying highp vec3 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texCoord;

uniform mediump float u_Phase;
uniform mediump vec4  u_CustomColor;

uniform sampler2D s_texture;

void main()
{
    vec4 texel = texture2D(s_texture, v_texCoord);
    gl_FragColor = texel; 
}
