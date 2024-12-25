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
 217;
 1.46625;-5.30505;-2.04186;,
 0.00000;-4.90220;-1.94600;,
 0.00000;-3.68315;-5.44950;,
 2.11991;-4.35480;-5.01851;,
 0.00000;1.29825;-9.17458;,
 3.55516;-3.35878;-7.14612;,
 2.72454;-5.54561;3.53934;,
 -0.00000;-4.09266;5.57550;,
 -0.00000;-5.09960;2.04400;,
 1.87092;-5.81301;1.41284;,
 4.89958;-2.59269;6.56183;,
 10.53146;0.71428;5.50805;,
 5.49024;1.23522;7.17829;,
 5.79789;1.32468;-8.89448;,
 10.71882;1.47213;-7.79852;,
 6.87970;-2.71309;-7.86628;,
 4.46292;-1.50937;-8.33301;,
 10.53272;-2.71750;-7.55331;,
 12.54162;-3.15976;-5.02656;,
 13.00582;1.26263;-4.92919;,
 13.03830;-3.56758;-1.55684;,
 13.53258;0.81336;-1.30266;,
 12.88406;0.51555;2.69948;,
 12.43624;-3.80590;2.43996;,
 10.44740;-3.88167;5.07160;,
 7.03325;-4.06003;5.72870;,
 4.89958;-2.59269;6.56183;,
 -0.00000;-4.09266;5.57550;,
 4.50912;-4.87910;5.22848;,
 2.72454;-5.54561;3.53934;,
 4.50912;-4.87910;5.22848;,
 -0.00000;-4.09266;5.57550;,
 3.55516;-3.35878;-7.14612;,
 0.00000;1.29825;-9.17458;,
 4.46292;-1.50937;-8.33301;,
 4.46292;-1.50937;-8.33301;,
 0.00014;-1.64615;6.94838;,
 0.00028;1.45799;7.48051;,
 6.21232;-3.14671;-3.92931;,
 7.43872;-2.88981;-4.35890;,
 7.31167;-2.53393;-1.10589;,
 5.27579;-3.37480;-2.95799;,
 7.31167;-2.53393;-1.10589;,
 4.84099;-3.52184;-1.71920;,
 7.31167;-2.53393;-1.10589;,
 4.78156;-3.55418;-0.12106;,
 7.31167;-2.53393;-1.10589;,
 5.30484;-3.46433;1.24901;,
 7.31167;-2.53393;-1.10589;,
 6.15034;-3.27292;2.06017;,
 7.31167;-2.53393;-1.10589;,
 7.31293;-3.03506;2.26194;,
 7.31167;-2.53393;-1.10589;,
 9.01040;-2.81592;1.71815;,
 7.31167;-2.53393;-1.10589;,
 10.01115;-2.58086;0.29722;,
 7.31167;-2.53393;-1.10589;,
 10.21048;-2.48853;-1.32818;,
 7.31167;-2.53393;-1.10589;,
 10.07440;-2.51814;-2.74921;,
 7.31167;-2.53393;-1.10589;,
 8.95545;-2.71684;-4.06641;,
 7.31167;-2.53393;-1.10589;,
 7.43872;-2.88981;-4.35890;,
 7.31167;-2.53393;-1.10589;,
 3.55516;-3.35878;-7.14612;,
 6.87970;-2.71309;-7.86628;,
 2.11991;-4.35480;-5.01851;,
 1.46625;-5.30505;-2.04186;,
 1.87092;-5.81301;1.41284;,
 2.72454;-5.54561;3.53934;,
 4.50912;-4.87910;5.22848;,
 7.03325;-4.06003;5.72870;,
 10.44740;-3.88167;5.07160;,
 12.43624;-3.80590;2.43996;,
 13.03830;-3.56758;-1.55684;,
 12.54162;-3.15976;-5.02656;,
 10.53272;-2.71750;-7.55331;,
 6.87970;-2.71309;-7.86628;,
 -2.11991;-4.35480;-5.01851;,
 -1.46625;-5.30505;-2.04186;,
 -3.55516;-3.35878;-7.14612;,
 -1.87092;-5.81301;1.41284;,
 -2.72454;-5.54561;3.53934;,
 -5.49024;1.23522;7.17829;,
 -10.53146;0.71428;5.50805;,
 -4.89958;-2.59269;6.56183;,
 -4.46292;-1.50937;-8.33301;,
 -6.87970;-2.71309;-7.86628;,
 -10.71882;1.47213;-7.79852;,
 -5.79789;1.32468;-8.89448;,
 -10.53272;-2.71750;-7.55331;,
 -13.00582;1.26263;-4.92919;,
 -12.54162;-3.15976;-5.02656;,
 -13.53258;0.81336;-1.30266;,
 -13.03830;-3.56758;-1.55684;,
 -12.43624;-3.80590;2.43996;,
 -12.88406;0.51555;2.69948;,
 -10.44740;-3.88167;5.07160;,
 -7.03325;-4.06003;5.72870;,
 -4.50912;-4.87910;5.22848;,
 -4.89958;-2.59269;6.56183;,
 -2.72454;-5.54561;3.53934;,
 -4.46292;-1.50937;-8.33301;,
 -3.55516;-3.35878;-7.14612;,
 -5.79789;1.32468;-8.89448;,
 -4.89958;-2.59269;6.56183;,
 -3.55516;-3.35878;-7.14612;,
 -0.00014;-1.64615;6.94838;,
 -0.00028;1.45799;7.48051;,
 -7.31167;-2.53393;-1.10589;,
 -7.43872;-2.88981;-4.35890;,
 -6.21232;-3.14671;-3.92931;,
 -7.31167;-2.53393;-1.10589;,
 -5.27579;-3.37480;-2.95799;,
 -7.31167;-2.53393;-1.10589;,
 -4.84099;-3.52184;-1.71920;,
 -7.31167;-2.53393;-1.10589;,
 -4.78156;-3.55418;-0.12106;,
 -7.31167;-2.53393;-1.10589;,
 -5.30484;-3.46433;1.24901;,
 -7.31167;-2.53393;-1.10589;,
 -6.15034;-3.27292;2.06017;,
 -7.31167;-2.53393;-1.10589;,
 -7.31293;-3.03506;2.26194;,
 -7.31167;-2.53393;-1.10589;,
 -9.01040;-2.81592;1.71815;,
 -7.31167;-2.53393;-1.10589;,
 -10.01115;-2.58086;0.29722;,
 -7.31167;-2.53393;-1.10589;,
 -10.21048;-2.48853;-1.32818;,
 -7.31167;-2.53393;-1.10589;,
 -10.07440;-2.51814;-2.74921;,
 -7.31167;-2.53393;-1.10589;,
 -8.95545;-2.71684;-4.06641;,
 -7.31167;-2.53393;-1.10589;,
 -7.43872;-2.88981;-4.35890;,
 -6.87970;-2.71309;-7.86628;,
 -3.55516;-3.35878;-7.14612;,
 -2.11991;-4.35480;-5.01851;,
 -1.46625;-5.30505;-2.04186;,
 -1.87092;-5.81301;1.41284;,
 -2.72454;-5.54561;3.53934;,
 -4.50912;-4.87910;5.22848;,
 -7.03325;-4.06003;5.72870;,
 -10.44740;-3.88167;5.07160;,
 -12.43624;-3.80590;2.43996;,
 -13.03830;-3.56758;-1.55684;,
 -12.54162;-3.15976;-5.02656;,
 -10.53272;-2.71750;-7.55331;,
 -6.87970;-2.71309;-7.86628;,
 10.07020;3.47196;5.16523;,
 12.47950;3.20054;2.69846;,
 13.22114;3.32577;-1.18909;,
 10.38212;3.88311;-7.69814;,
 5.68344;3.62183;-8.96882;,
 0.00000;3.44375;-9.34594;,
 12.67892;3.65568;-4.81698;,
 5.08130;4.14071;7.05386;,
 0.00000;4.40384;7.62650;,
 -12.47950;3.20054;2.69846;,
 -10.07020;3.47196;5.16523;,
 -13.22114;3.32577;-1.18909;,
 -5.68344;3.62183;-8.96882;,
 -10.38212;3.88311;-7.69814;,
 -12.67892;3.65568;-4.81698;,
 -5.08130;4.14071;7.05386;,
 0.00000;5.27404;-5.35206;,
 -2.94805;5.27404;-5.01329;,
 0.00000;6.30717;-0.90139;,
 -5.44726;5.27404;-4.04848;,
 0.00000;6.30717;-0.90139;,
 -7.11721;5.27404;-2.60459;,
 0.00000;6.30717;-0.90139;,
 -7.70360;5.27404;-0.90139;,
 0.00000;6.30717;-0.90139;,
 -7.11721;5.27404;0.80181;,
 0.00000;6.30717;-0.90139;,
 -5.44726;5.27404;2.24574;,
 0.00000;6.30717;-0.90139;,
 -2.94805;5.27404;3.21052;,
 0.00000;6.30717;-0.90139;,
 0.00000;5.27404;3.54931;,
 0.00000;6.30717;-0.90139;,
 2.94805;5.27404;3.21052;,
 0.00000;6.30717;-0.90139;,
 5.44726;5.27404;2.24574;,
 0.00000;6.30717;-0.90139;,
 7.11721;5.27404;0.80181;,
 0.00000;6.30717;-0.90139;,
 7.70360;5.27404;-0.90139;,
 0.00000;6.30717;-0.90139;,
 7.11721;5.27404;-2.60459;,
 0.00000;6.30717;-0.90139;,
 5.44726;5.27404;-4.04848;,
 0.00000;6.30717;-0.90139;,
 2.94805;5.27404;-5.01329;,
 0.00000;6.30717;-0.90139;,
 0.00000;5.27404;-5.35206;,
 0.00000;6.30717;-0.90139;,
 0.00000;3.44375;-9.34594;,
 -5.68344;3.62183;-8.96882;,
 -10.38212;3.88311;-7.69814;,
 -12.67892;3.65568;-4.81698;,
 -13.22114;3.32577;-1.18909;,
 -12.47950;3.20054;2.69846;,
 -10.07020;3.47196;5.16523;,
 -5.08130;4.14071;7.05386;,
 0.00000;4.40384;7.62650;,
 5.08130;4.14071;7.05386;,
 10.07020;3.47196;5.16523;,
 12.47950;3.20054;2.69846;,
 13.22114;3.32577;-1.18909;,
 12.67892;3.65568;-4.81698;,
 10.38212;3.88311;-7.69814;,
 5.68344;3.62183;-8.96882;,
 0.00000;3.44375;-9.34594;;
 
 142;
 4;0,1,2,3;,
 4;2,4,5,3;,
 4;6,7,8,9;,
 4;8,1,0,9;,
 3;10,11,12;,
 4;13,14,15,16;,
 3;15,14,17;,
 4;18,17,14,19;,
 4;20,18,19,21;,
 4;21,22,23,20;,
 4;24,23,22,11;,
 3;24,11,25;,
 3;11,10,25;,
 3;26,27,28;,
 3;29,30,31;,
 3;32,33,34;,
 3;26,30,25;,
 3;32,35,15;,
 3;7,10,36;,
 4;12,37,36,10;,
 3;38,39,40;,
 3;41,38,42;,
 3;43,41,44;,
 3;45,43,46;,
 3;47,45,48;,
 3;49,47,50;,
 3;51,49,52;,
 3;53,51,54;,
 3;55,53,56;,
 3;57,55,58;,
 3;59,57,60;,
 3;61,59,62;,
 3;63,61,64;,
 4;38,65,66,39;,
 4;41,67,65,38;,
 4;43,68,67,41;,
 4;45,69,68,43;,
 4;47,70,69,45;,
 4;49,71,70,47;,
 4;51,72,71,49;,
 4;53,73,72,51;,
 4;55,74,73,53;,
 4;57,75,74,55;,
 4;59,76,75,57;,
 4;61,77,76,59;,
 4;63,78,77,61;,
 4;79,2,1,80;,
 4;79,81,4,2;,
 4;82,8,7,83;,
 4;82,80,1,8;,
 3;84,85,86;,
 4;87,88,89,90;,
 3;91,89,88;,
 4;92,89,91,93;,
 4;94,92,93,95;,
 4;95,96,97,94;,
 4;85,97,96,98;,
 3;99,85,98;,
 3;99,86,85;,
 3;100,27,101;,
 3;27,100,102;,
 3;103,33,104;,
 3;33,103,105;,
 3;99,100,106;,
 3;88,103,107;,
 3;108,86,7;,
 4;86,108,109,84;,
 3;110,111,112;,
 3;113,112,114;,
 3;115,114,116;,
 3;117,116,118;,
 3;119,118,120;,
 3;121,120,122;,
 3;123,122,124;,
 3;125,124,126;,
 3;127,126,128;,
 3;129,128,130;,
 3;131,130,132;,
 3;133,132,134;,
 3;135,134,136;,
 4;111,137,138,112;,
 4;112,138,139,114;,
 4;114,139,140,116;,
 4;116,140,141,118;,
 4;118,141,142,120;,
 4;120,142,143,122;,
 4;122,143,144,124;,
 4;124,144,145,126;,
 4;126,145,146,128;,
 4;128,146,147,130;,
 4;130,147,148,132;,
 4;132,148,149,134;,
 4;134,149,150,136;,
 4;151,11,22,152;,
 4;22,21,153,152;,
 4;154,14,13,155;,
 4;13,4,156,155;,
 4;153,21,19,157;,
 4;19,14,154,157;,
 4;12,11,151,158;,
 4;159,37,12,158;,
 4;160,97,85,161;,
 4;160,162,94,97;,
 4;163,90,89,164;,
 4;163,156,4,90;,
 4;165,92,94,162;,
 4;165,164,89,92;,
 4;166,161,85,84;,
 4;166,84,109,159;,
 3;167,168,169;,
 3;168,170,171;,
 3;170,172,173;,
 3;172,174,175;,
 3;174,176,177;,
 3;176,178,179;,
 3;178,180,181;,
 3;180,182,183;,
 3;182,184,185;,
 3;184,186,187;,
 3;186,188,189;,
 3;188,190,191;,
 3;190,192,193;,
 3;192,194,195;,
 3;194,196,197;,
 3;196,198,199;,
 4;200,201,168,167;,
 4;201,202,170,168;,
 4;202,203,172,170;,
 4;203,204,174,172;,
 4;204,205,176,174;,
 4;205,206,178,176;,
 4;206,207,180,178;,
 4;207,208,182,180;,
 4;208,209,184,182;,
 4;209,210,186,184;,
 4;210,211,188,186;,
 4;211,212,190,188;,
 4;212,213,192,190;,
 4;213,214,194,192;,
 4;214,215,196,194;,
 4;215,216,198,196;,
 3;13,16,33;;
 
 MeshMaterialList {
  2;
  142;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  0,
  0,
  0,
  1;;
  Material {
   0.401600;0.081600;0.019200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.122400;0.238400;0.583200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  146;
  0.048073;-0.945768;-0.321267;,
  0.127009;-0.991743;-0.017744;,
  -0.050286;-0.648975;0.759146;,
  -0.008651;-0.360225;-0.932826;,
  0.908248;0.020235;0.417943;,
  0.124098;-0.113759;-0.985727;,
  0.093763;-0.342772;0.934728;,
  0.917606;0.025677;-0.396662;,
  0.088977;-0.982938;-0.160985;,
  0.049522;-0.265174;-0.962928;,
  0.175092;-0.979550;0.099123;,
  -0.003891;-0.818108;-0.575052;,
  0.194605;-0.058913;0.979111;,
  0.436828;-0.038193;-0.898734;,
  0.457785;-0.043861;0.887980;,
  0.999872;0.012181;0.010403;,
  0.889299;0.149875;0.432070;,
  0.149313;-0.014301;-0.988687;,
  0.912690;0.139200;-0.384215;,
  0.216476;0.066427;0.974026;,
  0.558720;0.149385;0.815792;,
  0.539327;0.085254;-0.837770;,
  0.990750;0.133429;0.024725;,
  0.000000;-0.857156;-0.515058;,
  0.000000;-0.995991;0.089458;,
  -0.000000;-0.751456;0.659783;,
  0.000000;-0.390486;-0.920609;,
  0.000000;-0.976312;-0.216367;,
  0.065144;-0.083547;0.994372;,
  0.000000;-0.054778;-0.998499;,
  0.000000;0.000767;1.000000;,
  0.516923;-0.102654;0.849855;,
  0.911434;-0.109506;0.396607;,
  0.994016;-0.109157;-0.004063;,
  0.910541;-0.088102;-0.403923;,
  0.468097;-0.071349;-0.880792;,
  0.154426;-0.256514;0.954124;,
  0.010560;-0.333332;0.942750;,
  0.194739;-0.980714;-0.016642;,
  0.141623;-0.989233;0.036889;,
  0.254751;-0.967007;0.000167;,
  0.339454;-0.940232;-0.027092;,
  0.410418;-0.910904;-0.042557;,
  0.448287;-0.890518;-0.077559;,
  0.425099;-0.894887;-0.135899;,
  0.326768;-0.926577;-0.186221;,
  0.152164;-0.964512;-0.215783;,
  -0.020274;-0.977874;-0.208209;,
  -0.133219;-0.981536;-0.137261;,
  -0.170076;-0.984720;-0.037431;,
  -0.089804;-0.994920;0.045488;,
  0.026245;-0.997226;0.069657;,
  -0.048073;-0.945768;-0.321267;,
  -0.127009;-0.991743;-0.017744;,
  0.050286;-0.648975;0.759146;,
  0.008651;-0.360225;-0.932826;,
  -0.908248;0.020235;0.417943;,
  -0.124098;-0.113759;-0.985727;,
  -0.093763;-0.342772;0.934728;,
  -0.917606;0.025677;-0.396662;,
  -0.088977;-0.982938;-0.160985;,
  -0.049522;-0.265174;-0.962928;,
  -0.175092;-0.979550;0.099123;,
  0.003891;-0.818108;-0.575052;,
  -0.194605;-0.058913;0.979111;,
  -0.436828;-0.038193;-0.898734;,
  -0.457785;-0.043861;0.887980;,
  -0.999872;0.012181;0.010403;,
  -0.889299;0.149875;0.432070;,
  -0.149313;-0.014301;-0.988687;,
  -0.912690;0.139200;-0.384215;,
  -0.216476;0.066427;0.974026;,
  -0.558720;0.149385;0.815792;,
  -0.539327;0.085254;-0.837770;,
  -0.990750;0.133429;0.024725;,
  -0.065144;-0.083547;0.994372;,
  -0.516923;-0.102654;0.849855;,
  -0.911434;-0.109506;0.396607;,
  -0.994016;-0.109157;-0.004063;,
  -0.910541;-0.088102;-0.403923;,
  -0.468097;-0.071349;-0.880792;,
  -0.154426;-0.256514;0.954124;,
  -0.010560;-0.333332;0.942750;,
  -0.194739;-0.980714;-0.016642;,
  -0.141623;-0.989233;0.036889;,
  -0.254751;-0.967007;0.000167;,
  -0.339454;-0.940232;-0.027092;,
  -0.410418;-0.910904;-0.042557;,
  -0.448287;-0.890518;-0.077559;,
  -0.425099;-0.894887;-0.135899;,
  -0.326768;-0.926577;-0.186221;,
  -0.152164;-0.964512;-0.215783;,
  0.020274;-0.977874;-0.208209;,
  0.133219;-0.981536;-0.137261;,
  0.170076;-0.984720;-0.037431;,
  0.089804;-0.994920;0.045488;,
  -0.026245;-0.997226;0.069657;,
  -0.000000;1.000000;-0.000000;,
  0.000000;0.948952;-0.315419;,
  -0.049993;0.957290;-0.284775;,
  -0.114267;0.974070;-0.195273;,
  -0.182882;0.979384;-0.085797;,
  -0.223094;0.974599;0.019649;,
  -0.208706;0.970026;0.124464;,
  -0.149431;0.969401;0.194762;,
  -0.076468;0.972321;0.220783;,
  0.000000;0.974130;0.225988;,
  0.076468;0.972321;0.220783;,
  0.149431;0.969401;0.194762;,
  0.208706;0.970026;0.124464;,
  0.223094;0.974599;0.019649;,
  0.182882;0.979384;-0.085797;,
  0.114267;0.974070;-0.195273;,
  0.049993;0.957290;-0.284775;,
  0.115156;-0.992537;-0.040115;,
  0.382499;-0.890404;-0.246730;,
  0.151908;-0.946273;-0.285468;,
  -0.105881;-0.955163;-0.276501;,
  -0.293881;-0.939014;-0.178567;,
  -0.348655;-0.935606;-0.055504;,
  -0.219017;-0.975187;0.032287;,
  -0.024939;-0.999082;0.034826;,
  -0.115156;-0.992537;-0.040115;,
  -0.382499;-0.890404;-0.246730;,
  -0.151908;-0.946273;-0.285468;,
  0.105881;-0.955163;-0.276501;,
  0.293881;-0.939014;-0.178567;,
  0.348655;-0.935606;-0.055504;,
  0.219017;-0.975187;0.032287;,
  0.024939;-0.999082;0.034826;,
  0.000000;0.915640;-0.401999;,
  -0.049507;0.932211;-0.358513;,
  -0.135206;0.963938;-0.229222;,
  -0.242690;0.966499;-0.083554;,
  -0.311414;0.949468;0.039148;,
  -0.293111;0.942574;0.160127;,
  -0.204999;0.951951;0.227518;,
  -0.102720;0.967276;0.232004;,
  0.000000;0.974160;0.225861;,
  0.102720;0.967276;0.232004;,
  0.204999;0.951951;0.227518;,
  0.293111;0.942574;0.160127;,
  0.311414;0.949468;0.039148;,
  0.242690;0.966499;-0.083554;,
  0.135206;0.963938;-0.229222;,
  0.049507;0.932211;-0.358513;;
  142;
  4;8,27,23,0;,
  4;23,26,11,0;,
  4;10,25,24,1;,
  4;24,27,8,1;,
  3;6,14,12;,
  4;5,13,9,3;,
  3;9,13,35;,
  4;34,35,13,7;,
  4;33,34,7,15;,
  4;15,4,32,33;,
  4;31,32,4,14;,
  3;31,14,36;,
  3;14,6,36;,
  3;6,25,2;,
  3;10,2,25;,
  3;11,26,3;,
  3;6,2,36;,
  3;11,3,9;,
  3;25,6,37;,
  4;12,28,37,6;,
  3;40,39,38;,
  3;41,40,38;,
  3;42,41,38;,
  3;43,42,38;,
  3;44,43,38;,
  3;45,44,38;,
  3;46,45,38;,
  3;47,46,38;,
  3;48,47,38;,
  3;49,48,38;,
  3;50,49,38;,
  3;51,50,38;,
  3;39,51,38;,
  4;40,11,114,39;,
  4;41,0,11,40;,
  4;42,8,0,41;,
  4;43,1,8,42;,
  4;44,10,1,43;,
  4;45,115,10,44;,
  4;46,116,115,45;,
  4;47,117,116,46;,
  4;48,118,117,47;,
  4;49,119,118,48;,
  4;50,120,119,49;,
  4;51,121,120,50;,
  4;39,114,121,51;,
  4;52,23,27,60;,
  4;52,63,26,23;,
  4;53,24,25,62;,
  4;53,60,27,24;,
  3;64,66,58;,
  4;55,61,65,57;,
  3;80,65,61;,
  4;59,65,80,79;,
  4;67,59,79,78;,
  4;78,77,56,67;,
  4;66,56,77,76;,
  3;81,66,76;,
  3;81,58,66;,
  3;54,25,58;,
  3;25,54,62;,
  3;55,26,63;,
  3;26,55,57;,
  3;81,54,58;,
  3;61,55,63;,
  3;82,58,25;,
  4;58,82,75,64;,
  3;83,84,85;,
  3;83,85,86;,
  3;83,86,87;,
  3;83,87,88;,
  3;83,88,89;,
  3;83,89,90;,
  3;83,90,91;,
  3;83,91,92;,
  3;83,92,93;,
  3;83,93,94;,
  3;83,94,95;,
  3;83,95,96;,
  3;83,96,84;,
  4;84,122,63,85;,
  4;85,63,52,86;,
  4;86,52,60,87;,
  4;87,60,53,88;,
  4;88,53,62,89;,
  4;89,62,123,90;,
  4;90,123,124,91;,
  4;91,124,125,92;,
  4;92,125,126,93;,
  4;93,126,127,94;,
  4;94,127,128,95;,
  4;95,128,129,96;,
  4;96,129,122,84;,
  4;20,14,4,16;,
  4;4,15,22,16;,
  4;21,13,5,17;,
  4;5,26,29,17;,
  4;22,15,7,18;,
  4;7,13,21,18;,
  4;12,14,20,19;,
  4;30,28,12,19;,
  4;68,56,66,72;,
  4;68,74,67,56;,
  4;69,57,65,73;,
  4;69,29,26,57;,
  4;70,59,67,74;,
  4;70,73,65,59;,
  4;71,72,66,64;,
  4;71,64,75,30;,
  3;98,99,97;,
  3;99,100,97;,
  3;100,101,97;,
  3;101,102,97;,
  3;102,103,97;,
  3;103,104,97;,
  3;104,105,97;,
  3;105,106,97;,
  3;106,107,97;,
  3;107,108,97;,
  3;108,109,97;,
  3;109,110,97;,
  3;110,111,97;,
  3;111,112,97;,
  3;112,113,97;,
  3;113,98,97;,
  4;130,131,99,98;,
  4;131,132,100,99;,
  4;132,133,101,100;,
  4;133,134,102,101;,
  4;134,135,103,102;,
  4;135,136,104,103;,
  4;136,137,105,104;,
  4;137,138,106,105;,
  4;138,139,107,106;,
  4;139,140,108,107;,
  4;140,141,109,108;,
  4;141,142,110,109;,
  4;142,143,111,110;,
  4;143,144,112,111;,
  4;144,145,113,112;,
  4;145,130,98,113;,
  3;5,3,26;;
 }
 MeshTextureCoords {
  217;
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  2.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  2.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  2.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.076920;0.125000;,
  0.000000;0.125000;,
  0.038460;0.000000;,
  0.153850;0.125000;,
  0.115380;0.000000;,
  0.230770;0.125000;,
  0.192310;0.000000;,
  0.307690;0.125000;,
  0.269230;0.000000;,
  0.384620;0.125000;,
  0.346150;0.000000;,
  0.461540;0.125000;,
  0.423080;0.000000;,
  0.538460;0.125000;,
  0.500000;0.000000;,
  0.615380;0.125000;,
  0.576920;0.000000;,
  0.692310;0.125000;,
  0.653850;0.000000;,
  0.769230;0.125000;,
  0.730770;0.000000;,
  0.846150;0.125000;,
  0.807690;0.000000;,
  0.923080;0.125000;,
  0.884620;0.000000;,
  1.000000;0.125000;,
  0.961540;0.000000;,
  0.076920;0.250000;,
  0.000000;0.250000;,
  0.153850;0.250000;,
  0.230770;0.250000;,
  0.307690;0.250000;,
  0.384620;0.250000;,
  0.461540;0.250000;,
  0.538460;0.250000;,
  0.615380;0.250000;,
  0.692310;0.250000;,
  0.769230;0.250000;,
  0.846150;0.250000;,
  0.923080;0.250000;,
  1.000000;0.250000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  2.000000;0.000000;,
  2.000000;0.000000;,
  0.000000;0.000000;,
  2.000000;0.000000;,
  2.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.038460;0.000000;,
  0.000000;0.125000;,
  0.076920;0.125000;,
  0.115380;0.000000;,
  0.153850;0.125000;,
  0.192310;0.000000;,
  0.230770;0.125000;,
  0.269230;0.000000;,
  0.307690;0.125000;,
  0.346150;0.000000;,
  0.384620;0.125000;,
  0.423080;0.000000;,
  0.461540;0.125000;,
  0.500000;0.000000;,
  0.538460;0.125000;,
  0.576920;0.000000;,
  0.615380;0.125000;,
  0.653850;0.000000;,
  0.692310;0.125000;,
  0.730770;0.000000;,
  0.769230;0.125000;,
  0.807690;0.000000;,
  0.846150;0.125000;,
  0.884620;0.000000;,
  0.923080;0.125000;,
  0.961540;0.000000;,
  1.000000;0.125000;,
  0.000000;0.250000;,
  0.076920;0.250000;,
  0.153850;0.250000;,
  0.230770;0.250000;,
  0.307690;0.250000;,
  0.384620;0.250000;,
  0.461540;0.250000;,
  0.538460;0.250000;,
  0.615380;0.250000;,
  0.692310;0.250000;,
  0.769230;0.250000;,
  0.846150;0.250000;,
  0.923080;0.250000;,
  1.000000;0.250000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.250000;,
  0.062500;0.250000;,
  0.031250;0.000000;,
  0.125000;0.250000;,
  0.093750;0.000000;,
  0.187500;0.250000;,
  0.156250;0.000000;,
  0.250000;0.250000;,
  0.218750;0.000000;,
  0.312500;0.250000;,
  0.281250;0.000000;,
  0.375000;0.250000;,
  0.343750;0.000000;,
  0.437500;0.250000;,
  0.406250;0.000000;,
  0.500000;0.250000;,
  0.468750;0.000000;,
  0.562500;0.250000;,
  0.531250;0.000000;,
  0.625000;0.250000;,
  0.593750;0.000000;,
  0.687500;0.250000;,
  0.656250;0.000000;,
  0.750000;0.250000;,
  0.718750;0.000000;,
  0.812500;0.250000;,
  0.781250;0.000000;,
  0.875000;0.250000;,
  0.843750;0.000000;,
  0.937500;0.250000;,
  0.906250;0.000000;,
  1.000000;0.250000;,
  0.968750;0.000000;,
  0.000000;0.500000;,
  0.062500;0.500000;,
  0.125000;0.500000;,
  0.187500;0.500000;,
  0.250000;0.500000;,
  0.312500;0.500000;,
  0.375000;0.500000;,
  0.437500;0.500000;,
  0.500000;0.500000;,
  0.562500;0.500000;,
  0.625000;0.500000;,
  0.687500;0.500000;,
  0.750000;0.500000;,
  0.812500;0.500000;,
  0.875000;0.500000;,
  0.937500;0.500000;,
  1.000000;0.500000;;
 }
}
