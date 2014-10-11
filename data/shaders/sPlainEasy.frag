#ifdef FG_GFX_ESSL_PRECISION_DEF
precision highp float;

varying highp vec3 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texCoord;

uniform mediump float u_Phase;
uniform mediump vec4  u_CustomColor;
#else
varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texCoord;

uniform float u_Phase;
uniform vec4  u_CustomColor;
#endif

uniform sampler2D s_texture;

void main()
{
    vec4 texel = texture2D(s_texture, v_texCoord);
    gl_FragColor = texel; 
}
