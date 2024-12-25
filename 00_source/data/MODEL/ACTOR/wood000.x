xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 55;
 -7.02383;45.52138;4.13915;,
 -6.13719;45.52138;-5.06891;,
 -8.10839;0.00000;-7.17392;,
 -9.32842;0.00000;5.49667;,
 2.89419;45.52138;-7.07113;,
 4.31907;0.00000;-9.92902;,
 7.58926;45.52138;0.89951;,
 10.77962;0.00000;1.03882;,
 1.45957;45.52138;7.82784;,
 2.34500;0.00000;10.57242;,
 -7.02383;45.52138;4.13915;,
 -9.32842;0.00000;5.49667;,
 -0.24360;45.52138;0.14529;,
 -0.24360;45.52138;0.14529;,
 -0.24360;45.52138;0.14529;,
 -0.24360;45.52138;0.14529;,
 -0.24360;45.52138;0.14529;,
 0.00138;0.00000;0.00099;,
 0.00138;0.00000;0.00099;,
 0.00138;0.00000;0.00099;,
 0.00138;0.00000;0.00099;,
 0.00138;0.00000;0.00099;,
 -12.09356;26.10147;52.03123;,
 -52.36666;24.73746;-15.57562;,
 16.56368;24.73746;-56.17869;,
 57.16679;24.73746;12.75167;,
 2.40008;104.73746;-1.41195;,
 -12.09356;26.10147;52.03123;,
 -52.36666;24.73746;-15.57562;,
 -12.09356;26.10147;52.03123;,
 -52.36666;24.73746;-15.57562;,
 57.16679;24.73746;12.75167;,
 16.56368;24.73746;-56.17869;,
 -8.97275;51.11384;42.56340;,
 -41.57540;51.11384;-12.78480;,
 13.77289;51.11384;-45.38741;,
 46.37539;51.11384;9.96081;,
 2.40008;115.35050;-1.41195;,
 -8.97275;51.11384;42.56340;,
 -41.57540;51.11384;-12.78480;,
 -8.97275;51.11384;42.56340;,
 -41.57540;51.11384;-12.78480;,
 46.37539;51.11384;9.96081;,
 13.77289;51.11384;-45.38741;,
 -4.89598;82.16196;26.79979;,
 -25.81170;82.16196;-8.70800;,
 9.69613;82.16196;-29.62370;,
 30.61175;82.16196;5.88408;,
 2.40008;123.37190;-1.41195;,
 -4.89598;82.16196;26.79979;,
 -25.81170;82.16196;-8.70800;,
 -4.89598;82.16196;26.79979;,
 -25.81170;82.16196;-8.70800;,
 30.61175;82.16196;5.88408;,
 9.69613;82.16196;-29.62370;;
 
 30;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 3;12,1,0;,
 3;13,4,1;,
 3;14,6,4;,
 3;15,8,6;,
 3;16,10,8;,
 3;17,3,2;,
 3;18,2,5;,
 3;19,5,7;,
 3;20,7,9;,
 3;21,9,11;,
 4;22,23,24,25;,
 3;26,27,25;,
 3;26,28,29;,
 3;26,24,30;,
 3;26,31,32;,
 4;33,34,35,36;,
 3;37,38,36;,
 3;37,39,40;,
 3;37,35,41;,
 3;37,42,43;,
 4;44,45,46,47;,
 3;48,49,47;,
 3;48,50,51;,
 3;48,46,52;,
 3;48,53,54;;
 
 MeshMaterialList {
  2;
  30;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.592941;0.244706;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.200784;0.718431;0.207059;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  20;
  0.000000;1.000000;0.000000;,
  -0.994274;0.047482;-0.095737;,
  -0.216119;0.054438;-0.974848;,
  0.860142;0.058733;-0.506662;,
  0.747845;0.054438;0.661638;,
  0.000000;-1.000000;-0.000000;,
  0.448543;0.444359;0.775471;,
  -0.002982;-0.999926;0.011814;,
  0.453957;0.447213;0.770665;,
  0.453957;0.447214;0.770664;,
  -0.398300;0.047482;0.916026;,
  -0.771791;0.448561;0.450702;,
  -0.453956;0.447214;-0.770664;,
  0.770664;0.447214;-0.453956;,
  -0.770664;0.447214;0.453957;,
  -0.453956;0.447215;-0.770664;,
  0.770665;0.447214;-0.453955;,
  -0.770664;0.447215;0.453956;,
  -0.453956;0.447215;-0.770664;,
  0.770665;0.447214;-0.453955;;
  30;
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;10,10,10,10;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  4;7,7,7,7;,
  3;6,6,6;,
  3;11,11,11;,
  3;12,12,12;,
  3;13,13,13;,
  4;5,5,5,5;,
  3;8,8,8;,
  3;14,14,14;,
  3;15,15,15;,
  3;16,16,16;,
  4;5,5,5,5;,
  3;9,9,9;,
  3;17,17,17;,
  3;18,18,18;,
  3;19,19,19;;
 }
 MeshTextureCoords {
  55;
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.100000;0.000000;,
  0.300000;0.000000;,
  0.500000;0.000000;,
  0.700000;0.000000;,
  0.900000;0.000000;,
  0.100000;1.000000;,
  0.300000;1.000000;,
  0.500000;1.000000;,
  0.700000;1.000000;,
  0.900000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}