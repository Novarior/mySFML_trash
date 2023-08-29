/* Signed distance drawing methods */
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform vec2 u_coord;
uniform float u_time;



#define PI_TWO 1.570796326794897
#define PI 3.141592653589793
#define TWO_PI 6.283185307179586

#define rx 1./min(u_resolution.x,u_resolution.y)
#define uv gl_FragColor.xy/u_resolution.xy
#define st coord(FragCoord.xy*u_resolution.xy)
#define mx coord(u_mouse)

const vec4 WHITE=vec4(1.);
const vec4 BLACK=vec4(0.);
const vec4 RED=vec4(1.,0.,0.,1.);
const vec4 AZUR=vec4(0.,1.,1.,1.);
const vec4 ORANGE=vec4(1.,.5,0.,1.);
const vec4 GREEN=vec4(0.,1.,0.,1.);


vec2 vvv=vec2(0.5,0.5);

float sdCircle(vec2 p,vec2 c,float r){
    return length(p-c)-r;
}



float fill(in float d) {
    return 1.0 - smoothstep(0.0, rx * 2.0, d);
}
float stroke(in float d, in float t) {
    return 1.0 - smoothstep(t - rx * 1.5, t + rx * 1.5, abs(d));
}
vec3 draw(in sampler2D t, in vec2 pos, in vec2 w)
{
    vec2 s = w / 1.0; s.x *= -1.0;
    return texture2D(t, pos / s + 0.5).rgb;
}
/* Field Adapted from https://www.shadertoy.com/view/XsyGRW */
vec4 field(float d){
    const vec4 c1=mix(WHITE,RED,.1);
    const vec4 c4=BLACK;
    float f=clamp(d*sin(PI_TWO),.01,1.);
    vec4 gradient=mix(c4,c1,f);
    gradient=mix(gradient,c4,1.-clamp(1.25-d*.001,1.,1.2));
    
    return gradient;
}
vec4 mainImage(vec4 fragCoord,vec2 iResolution)
{
    
    vec2 p=gl_FragCoord.xy/iResolution/.4-.7;
    float d=sdCircle(p,vvv,.01);
    vec4 color=field(d);
    return vec4(color.xyz,1.);
}

void main(){
    
    gl_FragColor=mainImage(gl_FragCoord,u_resolution);
}

