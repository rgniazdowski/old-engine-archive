#ifdef FG_GFX_ESSL_PRECISION_DEF
precision highp float;
varying highp vec3 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texCoord;
varying highp vec4 v_color;

varying highp vec3 v_eye;
#else
//#version 120
varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texCoord;
varying vec4 v_color;
varying vec3 v_eye;
#endif

// Matrices
uniform mat4 u_mvMatrix;
uniform mat4 u_mvpMatrix;

// Attributes
attribute vec4 a_position; 
attribute vec3 a_normal;
attribute vec2 a_texCoord;
attribute vec4 a_color;
attribute vec3 a_tangent;
attribute vec3 a_bitangent;

void main() {
    
    // Define normal in model coordinates    
    vec3 mcNormal = a_normal;
    
    // Calculate and normalize eye space normal
    vec3 ecNormal = vec3(u_mvMatrix * vec4(mcNormal, 0.0));
    ecNormal = normalize(ecNormal);
    v_normal = ecNormal;
    // eye view space
    v_eye = -(u_mvMatrix * a_position);
    
    // Texture coordinate
	v_texCoord = a_texCoord;	
	// Current color
	v_color = a_color;
    
    gl_Position = u_mvpMatrix * a_position;    
}


