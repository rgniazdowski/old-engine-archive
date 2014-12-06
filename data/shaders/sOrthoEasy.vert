#ifdef FG_GFX_ESSL_PRECISION_DEF
precision highp float;
varying highp vec3 v_position;
varying highp vec2 v_texCoord;
varying highp vec4 v_color;
#else

varying vec3 v_position;
varying vec2 v_texCoord;
varying vec4 v_color;
#endif

uniform mat4 u_mvpMatrix;

attribute vec4 a_position; 
attribute vec2 a_texCoord;
attribute vec4 a_color;

void main()
{
    gl_Position = u_mvpMatrix * a_position;
	
	v_position = a_position.xyz;
	v_texCoord = a_texCoord;
	v_color = a_color;
}
