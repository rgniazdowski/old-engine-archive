#ifdef FG_GFX_ESSL_PRECISION_DEF
precision highp float;

varying highp vec3 v_position;
varying highp vec3 v_normal;
varying highp vec4 v_color;
uniform mediump vec4  u_CustomColor;
#else

varying vec3 v_position;
varying vec3 v_normal;
varying vec4 v_color;
uniform vec4  u_CustomColor;
#endif

uniform samplerCube s_skybox;

void main()
{
  gl_FragColor = textureCube(s_skybox, v_position);
}
