export const vertFrag = `
precision mediump float;
attribute vec2 position;
varying vec2 uv;
void main() {
  uv = 0.5 * (position + 1.0);
  gl_Position = vec4(position, 0, 1);
}`;


function hex2vec4(c: string) {
  let r = (parseInt(c.substr(1, 2), 16) / 255).toFixed(2);
  let g = (parseInt(c.substr(3, 2), 16) / 255).toFixed(2);
  let b = (parseInt(c.substr(5, 2), 16) / 255).toFixed(2);
  return `vec4(${r},${g},${b},1.0)`;
}

export const viewFrag = `precision mediump float;
uniform sampler2D buf;
uniform float width, height, mouseX, mouseY, drawSize;
varying vec2 uv;
float dx= 1./width , dy= 1./height ;
float outerSize = drawSize + 0.5;
float innerSize = drawSize - 0.5;
void main() {
  vec4 old = texture2D(buf, uv);
  int v =  int(old[0]*16.0 + 0.5);
  if (v == 5){
    gl_FragColor = ${hex2vec4('#003a8c')};
  } else if (v == 6) {
    gl_FragColor = ${hex2vec4('#096dd9')};
  } else if (v == 7) {
    gl_FragColor = ${hex2vec4('#91d5ff')};
  } else if (v == 9) {
   gl_FragColor = ${hex2vec4('#820014')};
  } else if (v == 10) {
    gl_FragColor =${hex2vec4('#cf1322')};
  } else if (v == 11) {
    gl_FragColor = ${hex2vec4('#ffa39e')};
  } else if (v == 4) {
    gl_FragColor = ${hex2vec4('#ff00ff')}; // virus
  } else if (v == 16) {
    gl_FragColor = ${hex2vec4('#ffffff')};
  } else {
    gl_FragColor = ${hex2vec4('#000000')};
  }
  if (drawSize > 0.0) {
    float dx = abs(uv.x - mouseX) * width;
    float dy = abs(uv.y - mouseY) * height;
    if ( dx <= outerSize && dy <= outerSize && (dy > innerSize || dx > innerSize)) {
      gl_FragColor = mix(gl_FragColor, ${hex2vec4('#00ff00')}, 0.5) ;
      return;
    }
  }
}
`;

