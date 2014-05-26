// vertex shader
var vertexShader =
"attribute vec3 aPosition;" +
"attribute vec2 aTexCoord;" +
"uniform mat4 uMvpMatrix;" +
"uniform bool enableTexture;" +
"varying vec2 vTexCoord;" +
"void main() {" +
"  if (enableTexture) {" +
"    vTexCoord = aTexCoord;" +
"  }" +
"  gl_Position = uMvpMatrix * vec4(aPosition, 1.0);" +
"  gl_PointSize = 1.0;" +
"}";

// fragment shader
var fragmentShader =
"precision mediump float;" +
"uniform sampler2D uSampler;" +
"uniform bool enableTexture;" +
"uniform vec3 uColor;" +
"varying vec2 vTexCoord;" +
"void main() {" +
"  if (enableTexture) {" +
"    gl_FragColor = texture2D(uSampler, vTexCoord);" +
"  } else {" +
"    gl_FragColor = vec4(uColor, 1);" +
"  }" +
"}";

// init
var canvas = document.getElementById("canvas");
var gl = canvas.getContext("experimental-webgl");
var fps = 30;
var paranoimiaRotation = 0;
gl.clearColor(0, 0, 0, 1);
gl.enable(gl.DEPTH_TEST);
gl.enable(gl.BLEND);
gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);

// music
var music = new Audio("paranoimia.mp3");
music.addEventListener('ended', function() {
  this.currentTime = 0;
  this.play();
}, false);
music.play();

// shader
var program = createProgram(vertexShader, fragmentShader);
gl.useProgram(program);

// matrices
var mvMatrix = new J3DIMatrix4();
var mvpMatrix = new J3DIMatrix4();
var perspectiveMatrix = new J3DIMatrix4();
perspectiveMatrix.perspective(60, canvas.width / canvas.height, 0.1, 1000);

// uniforms
var mvpMatrixLocation = gl.getUniformLocation(program, "uMvpMatrix");
var colorLocation = gl.getUniformLocation(program, "uColor");
var samplerLocation = gl.getUniformLocation(program, "uSampler");
var enableTextureLocation = gl.getUniformLocation(program, "enableTexture");

// attributes
var attribs = {
  "POSITION": gl.getAttribLocation(program, "aPosition"),
  "TEXCOORD": gl.getAttribLocation(program, "aTexCoord")
};
gl.enableVertexAttribArray(attribs.POSITION);
gl.enableVertexAttribArray(attribs.TEXCOORD);

// colors
var paranoimiaColor = [1, 1, 1];
var starfieldColor = [1, 1, 1];
var barsColor = [0, 0, 1];

// images
var textTexture = gl.createTexture();
var textImage = new Image();
textImage.src = "font.png";
textImage.onload = function () {
  gl.activeTexture(gl.TEXTURE0);
  gl.bindTexture(gl.TEXTURE_2D, textTexture);
  gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, textImage);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
  animate();
}

// Paranoimia vertices
var paranoimiaVertices = [
  0, 0, 0, 0, 10, 0, 4, 10, 0, 4, 5, 0, 0, 5, 0,                // P
  5, 0, 0, 7, 10, 0, 9, 0, 0,                                   // A
  10, 0, 0, 10, 10, 0, 14, 10, 0, 14, 5, 0, 10, 5, 0, 14, 0, 0, // R
  15, 0, 0, 17, 10, 0, 19, 0, 0,                                // A
  20, 0, 0, 20, 10, 0, 24, 0, 0, 24, 10, 0,                     // N
  25, 0, 0, 25, 10, 0, 29, 10, 0, 29, 0, 0,                     // O
  30, 0, 0, 30, 10, 0,                                          // I
  31, 0, 0, 31, 10, 0, 34, 5, 0, 37, 10, 0, 37, 0, 0,           // M
  38, 0, 0, 38, 10, 0,                                          // I
  39, 0, 0, 41, 10, 0, 43, 0, 0                                 // A
];
var paranoimiaVertexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, paranoimiaVertexBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(paranoimiaVertices), gl.STATIC_DRAW);

// Paranoimia indices
var paranoimiaIndices = [
  0, 1, 1, 2, 2, 3, 3, 4,              // P
  5, 6, 6, 7,                          // A
  8, 9, 9, 10, 10, 11, 11, 12, 12, 13, // R
  14, 15, 15, 16,                      // A
  17, 18, 18, 19, 19, 20,              // N
  21, 22, 22, 23, 23, 24, 24, 21,      // O
  25, 26,                              // I
  27, 28, 28, 29, 29, 30, 30, 31,      // M
  32, 33,                              // I
  34, 35, 35, 36                       // A
];
var paranoimiaIndexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, paranoimiaIndexBuffer);
gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(paranoimiaIndices), gl.STATIC_DRAW);

// starfield vertices
var starfieldNum = 50;
var starfieldVertices = [];
for (var i = 0; i < starfieldNum; i++) {
  var x = 20 * Math.random() - 10;
  var y = 20 * Math.random() - 10;
  var z = - 100 * Math.random();
  starfieldVertices.push(x, y, z);
}
var starfieldVertexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, starfieldVertexBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(starfieldVertices), gl.DYNAMIC_DRAW);

// bars vertices
var barsVertices = [-1, 0, 0, 1, 0, 0, -1, 0.13, 0, -1, 0.13, 0, 1, 0, 0, 1, 0.13, 0];
var barsVertexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, barsVertexBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(barsVertices), gl.STATIC_DRAW);

// text
var text = "JA, VI ELSKER DETTE LANDET, SOM DET STIGER FREM, FURET, VARBITT OVER VANNET, MED DE TUSEN HJEM, ELSKER, ELSKER DET OG TENKER PA VAR FAR OG MOR OG DEN SAGANATT SOM SENKER DROMMER PA VAR JORD. OG DEN SAGANATT SOM SENKER, SENKER DROMMER PA VAR JORD.";
var textAnimPos = 2;
var charSize = 8 / 512;
var charWidth = 0.05;
var textVertices = [];
for (var i in text) {
  var x = i * 0.05;
  var w = charWidth;
  var h = 0.08;
  var c = text[i];
  var charIndex;
  if (c == " ") charIndex = 26;
  else if (c == ".") charIndex = 27;
  else if (c == ",") charIndex = 28;
  else if (c == "!") charIndex = 30;
  else if (c == "?") charIndex = 31;
  else if (!isNaN(c)) charIndex = parseInt(c) + 35;
  else charIndex = c.charCodeAt(0) - 65;
  var charAt = charIndex * 8 / 512;
  var charVertices = [
    x, 0, 0, charAt, 1,
    x + w, 0, 0, charAt + charSize, 1,
    x, h, 0, charAt, 0,
    x, h, 0, charAt, 0,
    x + w, 0, 0, charAt + charSize, 1,
    x + w, h, 0, charAt + charSize, 0];
  textVertices = textVertices.concat(charVertices);
}

var textVertexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, textVertexBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textVertices), gl.STATIC_DRAW);

// animate
function animate() {
  setInterval(function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // defaults
    gl.uniform1i(enableTextureLocation, false);
    gl.disableVertexAttribArray(attribs.TEXCOORD);

    // move starfield
    for (var i = 0; i < starfieldNum; i++) {
      starfieldVertices[3 * i + 2] += 0.4;
      var z = starfieldVertices[3 * i + 2];
      if (z > 0) {
        starfieldVertices[3 * i] = 20 * Math.random() - 10;
        starfieldVertices[3 * i + 1] = 20 * Math.random() - 10;
        starfieldVertices[3 * i + 2] = - 100 * Math.random();
      }
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, starfieldVertexBuffer);
    gl.bufferSubData(gl.ARRAY_BUFFER, 0, new Float32Array(starfieldVertices));

    // starfield pvm matrix
    mvpMatrix.makeIdentity();
    mvpMatrix.load(perspectiveMatrix);
    mvpMatrix.setUniform(gl, mvpMatrixLocation, false);

    // draw starfield
    gl.bindBuffer(gl.ARRAY_BUFFER, starfieldVertexBuffer);
    gl.vertexAttribPointer(attribs.POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.uniform3fv(colorLocation, new Float32Array(starfieldColor));
    gl.drawArrays(gl.POINTS, 0, starfieldVertices.length / 3);

    // rotate Paranoimia
    mvMatrix.makeIdentity();
    mvMatrix.translate(-20, -5, -60);
    mvMatrix.translate(20, 5, 0);
    mvMatrix.rotate(paranoimiaRotation, 1, 0, 0);
    mvMatrix.rotate(0.4 * paranoimiaRotation, 0, 1, 0);
    mvMatrix.translate(-20, -5, 0);
    paranoimiaRotation += 5;

    // Paranoimia pvm matrix
    mvpMatrix.makeIdentity();
    mvpMatrix.load(perspectiveMatrix);
    mvpMatrix.multiply(mvMatrix);
    mvpMatrix.setUniform(gl, mvpMatrixLocation, false);

    // draw Paranoimia
    gl.bindBuffer(gl.ARRAY_BUFFER, paranoimiaVertexBuffer);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, paranoimiaIndexBuffer);
    gl.vertexAttribPointer(attribs.POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.uniform3fv(colorLocation, new Float32Array(paranoimiaColor));
    gl.drawElements(gl.LINES, paranoimiaIndices.length, gl.UNSIGNED_SHORT, 0);

    // bar top pvm matrix
    mvpMatrix.makeIdentity();
    mvpMatrix.translate(0, 0.78, 0);
    mvpMatrix.setUniform(gl, mvpMatrixLocation, false);

    // draw bar top
    gl.bindBuffer(gl.ARRAY_BUFFER, barsVertexBuffer);
    gl.vertexAttribPointer(attribs.POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.uniform3fv(colorLocation, new Float32Array(barsColor));
    gl.drawArrays(gl.TRIANGLES, 0, barsVertices.length / 3);

    // bar bottom pvm matrix
    mvpMatrix.makeIdentity();
    mvpMatrix.translate(0, -0.82, 0);
    mvpMatrix.setUniform(gl, mvpMatrixLocation, false);

    // draw bar bottom
    gl.drawArrays(gl.TRIANGLES, 0, barsVertices.length / 3);

    // text top pvm matrix
    mvpMatrix.makeIdentity();
    mvpMatrix.translate(-0.9 + textAnimPos, 0.8, -1);
    mvpMatrix.setUniform(gl, mvpMatrixLocation, false);

    // draw top text
    gl.enableVertexAttribArray(attribs.TEXCOORD);
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, textTexture);
    gl.bindBuffer(gl.ARRAY_BUFFER, textVertexBuffer);
    gl.vertexAttribPointer(attribs.POSITION, 3, gl.FLOAT, false, 5 * Float32Array.BYTES_PER_ELEMENT, 0);
    gl.vertexAttribPointer(attribs.TEXCOORD, 2, gl.FLOAT, false, 5 * Float32Array.BYTES_PER_ELEMENT, 3 * Float32Array.BYTES_PER_ELEMENT);
    gl.uniform1i(samplerLocation, 0); // TEXTURE0
    gl.uniform1i(enableTextureLocation, true);
    gl.drawArrays(gl.TRIANGLES, 0, textVertices.length / 5);

    // text bottom pvm matrix
    mvpMatrix.makeIdentity();
    mvpMatrix.translate(-0.9 + textAnimPos, -0.8, -1);
    mvpMatrix.setUniform(gl, mvpMatrixLocation, false);

    // draw bottom text
    gl.drawArrays(gl.TRIANGLES, 0, textVertices.length / 5);

    // move text
    textAnimPos -= 0.01;
    if (textAnimPos < - charWidth * text.length)
      textAnimPos = 2;
  }, 1000 / fps);
}
