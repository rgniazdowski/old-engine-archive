#ifdef FG_GFX_ESSL_PRECISION_DEF
precision highp float;
varying highp vec3 v_position;
varying highp vec3 v_normal;
varying highp vec4 v_color;
#else
varying vec3 v_position;
varying vec3 v_normal;
varying vec4 v_color;
#endif

uniform mat4 u_mvpMatrix;

// Attributes
attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec4 a_color;

void main()
{
	// Transform the points position by MVP matrix
	gl_Position = u_mvpMatrix * a_position;

	// varying position contains original data position
	v_position = a_position.xyz;
	// Normal coordinate
	v_normal = a_normal;
	// Current color
	v_color = a_color;
}
