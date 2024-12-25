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
 121;
 -4.09549;-26.15742;-1.97330;,
 -3.94940;-26.19708;0.05460;,
 -5.13513;-24.97670;0.00644;,
 -5.35941;-24.67507;-2.59147;,
 -5.49647;-17.19256;-0.52304;,
 -6.62246;-5.76958;-0.87020;,
 -6.06553;-4.33555;-3.85171;,
 -5.56252;-16.33334;-2.82429;,
 3.40686;-24.37172;6.33434;,
 2.86206;-26.47053;5.03773;,
 4.54125;-26.47729;3.54756;,
 5.59030;-24.13726;4.30976;,
 -6.27435;-5.56318;3.00202;,
 -5.10139;-17.28093;2.10070;,
 -3.89701;-16.66837;4.65924;,
 -5.28020;-4.87907;5.61106;,
 5.64189;-26.53241;0.29981;,
 6.96167;-23.93594;0.38115;,
 3.78381;-23.62762;-6.09556;,
 3.07384;-26.38503;-4.62255;,
 -0.19698;-26.29347;-5.16386;,
 -0.40400;-23.93580;-6.63698;,
 -3.04839;-26.19729;-3.95640;,
 -4.08625;-24.33966;-5.06555;,
 0.28297;-26.26176;5.28640;,
 0.19708;-24.67531;6.84208;,
 5.06576;-26.49031;-2.58580;,
 6.26069;-23.70676;-3.44883;,
 -4.04442;-14.87836;-5.37894;,
 -4.21313;-0.91917;-6.57993;,
 -0.35914;-0.13009;-7.74053;,
 -0.31027;-12.25448;-6.88163;,
 -3.63451;-26.22000;1.73785;,
 -4.73921;-25.13133;2.17017;,
 -2.49567;-26.26379;3.38583;,
 -3.30418;-25.07131;4.32278;,
 3.77114;-10.71581;-7.05313;,
 6.01072;-10.21058;-4.11705;,
 6.61538;-10.25175;-0.01872;,
 3.53633;-12.06471;7.17311;,
 -0.18788;-14.46462;7.50011;,
 5.84636;-10.72305;4.17599;,
 3.74206;-0.02996;-7.36519;,
 6.05518;-0.18217;-4.41651;,
 6.81062;-0.36697;-0.36642;,
 5.90894;-0.38713;4.27465;,
 3.62169;-0.28787;7.31815;,
 -1.76530;-24.85980;5.77703;,
 -1.31813;-26.24923;4.53075;,
 -2.22691;-15.56915;6.42943;,
 -3.20761;-3.62831;7.68684;,
 -0.43844;-2.29645;8.25909;,
 -0.21466;1.75427;-5.27523;,
 -2.81344;1.22073;-4.50114;,
 0.74424;3.40392;-0.05089;,
 -3.80474;1.09249;-2.95764;,
 0.74424;3.40392;-0.05089;,
 -4.32443;1.14726;-0.83352;,
 0.74424;3.40392;-0.05089;,
 -4.16959;1.56867;1.91499;,
 0.74424;3.40392;-0.05089;,
 -3.42759;1.81409;3.49962;,
 0.74424;3.40392;-0.05089;,
 -1.80922;1.95947;5.17849;,
 0.74424;3.40392;-0.05089;,
 -0.15659;1.92420;5.47617;,
 0.74424;3.40392;-0.05089;,
 2.46351;1.64434;4.91999;,
 0.74424;3.40392;-0.05089;,
 4.00764;1.58575;2.84350;,
 0.74424;3.40392;-0.05089;,
 4.45473;1.75871;-0.29193;,
 0.74424;3.40392;-0.05089;,
 4.08037;1.73296;-2.98893;,
 0.74424;3.40392;-0.05089;,
 2.54860;1.82203;-4.99695;,
 0.74424;3.40392;-0.05089;,
 -0.21466;1.75427;-5.27523;,
 0.74424;3.40392;-0.05089;,
 -5.71627;-1.12150;-4.27444;,
 3.62169;-0.28787;7.31815;,
 -0.31388;0.22032;8.04832;,
 -6.48357;-0.80640;-1.17778;,
 -6.25765;-0.42725;2.90321;,
 -5.14283;-0.04939;5.28122;,
 -2.76909;0.16831;7.70735;,
 -0.43844;-2.29645;8.25909;,
 -0.18788;-14.46462;7.50011;,
 3.53633;-12.06471;7.17311;,
 3.62169;-0.28787;7.31815;,
 -4.21313;-0.91917;-6.57993;,
 -4.04442;-14.87836;-5.37894;,
 -5.56252;-16.33334;-2.82429;,
 -6.06553;-4.33555;-3.85171;,
 0.80636;-25.44356;-0.27660;,
 -3.04839;-26.19729;-3.95640;,
 -0.19698;-26.29347;-5.16386;,
 0.80636;-25.44356;-0.27660;,
 -4.09549;-26.15742;-1.97330;,
 0.80636;-25.44356;-0.27660;,
 -3.94940;-26.19708;0.05460;,
 0.80636;-25.44356;-0.27660;,
 -3.63451;-26.22000;1.73785;,
 0.80636;-25.44356;-0.27660;,
 -2.49567;-26.26379;3.38583;,
 0.80636;-25.44356;-0.27660;,
 -1.31813;-26.24923;4.53075;,
 0.80636;-25.44356;-0.27660;,
 0.28297;-26.26176;5.28640;,
 0.80636;-25.44356;-0.27660;,
 2.86206;-26.47053;5.03773;,
 0.80636;-25.44356;-0.27660;,
 4.54125;-26.47729;3.54756;,
 0.80636;-25.44356;-0.27660;,
 5.64189;-26.53241;0.29981;,
 0.80636;-25.44356;-0.27660;,
 5.06576;-26.49031;-2.58580;,
 0.80636;-25.44356;-0.27660;,
 3.07384;-26.38503;-4.62255;,
 0.80636;-25.44356;-0.27660;,
 -0.19698;-26.29347;-5.16386;;
 
 85;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,5,4,13;,
 4;14,15,12,13;,
 4;10,16,17,11;,
 4;18,19,20,21;,
 4;20,22,23,21;,
 4;24,9,8,25;,
 4;17,16,26,27;,
 4;28,29,30,31;,
 4;26,19,18,27;,
 4;2,1,32,33;,
 4;32,34,35,33;,
 4;23,22,0,3;,
 4;28,23,3,7;,
 4;33,35,14,13;,
 4;4,2,33,13;,
 4;27,18,36,37;,
 4;38,17,27,37;,
 4;25,8,39,40;,
 4;21,23,28,31;,
 4;36,18,21,31;,
 4;11,17,38,41;,
 4;39,8,11,41;,
 4;3,2,4,7;,
 4;42,36,31,30;,
 4;43,37,36,42;,
 4;44,38,37,43;,
 4;45,41,38,44;,
 4;46,39,41,45;,
 4;47,35,34,48;,
 4;24,25,47,48;,
 4;49,14,35,47;,
 4;25,40,49,47;,
 4;50,15,14,49;,
 4;40,51,50,49;,
 3;52,53,54;,
 3;53,55,56;,
 3;55,57,58;,
 3;57,59,60;,
 3;59,61,62;,
 3;61,63,64;,
 3;63,65,66;,
 3;65,67,68;,
 3;67,69,70;,
 3;69,71,72;,
 3;71,73,74;,
 3;73,75,76;,
 3;75,77,78;,
 3;29,6,79;,
 3;80,81,51;,
 4;82,79,6,5;,
 4;12,83,82,5;,
 4;15,84,83,12;,
 4;50,85,84,15;,
 4;51,81,85,50;,
 4;52,30,29,53;,
 4;67,46,45,69;,
 4;69,45,44,71;,
 4;71,44,43,73;,
 4;73,43,42,75;,
 4;75,42,30,77;,
 4;79,55,53,29;,
 4;80,67,65,81;,
 4;82,57,55,79;,
 4;83,59,57,82;,
 4;84,61,59,83;,
 4;85,63,61,84;,
 4;81,65,63,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 3;94,95,96;,
 3;97,98,95;,
 3;99,100,98;,
 3;101,102,100;,
 3;103,104,102;,
 3;105,106,104;,
 3;107,108,106;,
 3;109,110,108;,
 3;111,112,110;,
 3;113,114,112;,
 3;115,116,114;,
 3;117,118,116;,
 3;119,120,118;;
 
 MeshMaterialList {
  1;
  85;
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
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  80;
  -0.954641;-0.053844;-0.292849;,
  -0.949109;-0.083082;0.303790;,
  0.912198;-0.013761;-0.409518;,
  -0.108347;-0.071999;0.991502;,
  -0.147299;-0.050407;-0.987807;,
  0.897081;-0.012199;0.441698;,
  -0.966657;-0.045534;0.251993;,
  -0.024732;-0.001828;0.999692;,
  -0.928448;-0.022314;-0.370792;,
  -0.996438;-0.063042;0.056016;,
  -0.624212;-0.051777;-0.779537;,
  0.999572;-0.001093;0.029228;,
  -0.792739;-0.102508;0.600880;,
  0.452399;-0.040883;-0.890878;,
  0.497496;-0.038615;0.866606;,
  -0.999034;-0.029115;-0.032925;,
  -0.821735;-0.041023;0.568391;,
  0.778091;-0.471598;-0.414934;,
  -0.279084;-0.955617;0.094385;,
  0.396313;-0.509616;-0.763693;,
  -0.320145;-0.943193;-0.088850;,
  0.737842;-0.488436;0.465854;,
  -0.085951;-0.546881;-0.832787;,
  -0.317778;-0.948097;0.011372;,
  -0.325128;-0.851308;-0.411784;,
  0.887228;-0.458566;0.050433;,
  -0.699370;-0.418236;0.579621;,
  0.434084;-0.290837;-0.852634;,
  0.432624;-0.335959;0.836641;,
  0.834041;-0.259473;0.486877;,
  -0.129400;-0.302605;-0.944291;,
  -0.140954;-0.398271;0.906373;,
  0.868352;-0.248021;-0.429477;,
  -0.852611;-0.417503;0.314238;,
  -0.897803;-0.381335;-0.220303;,
  -0.916342;-0.390763;0.087303;,
  -0.611327;-0.349519;-0.710011;,
  0.971976;-0.229499;0.050916;,
  0.359746;-0.586857;0.725384;,
  -0.070768;-0.942281;0.327260;,
  -0.225438;-0.953491;0.200081;,
  -0.169143;-0.947889;0.269993;,
  -0.512758;-0.411555;0.753460;,
  -0.534779;-0.100134;0.839038;,
  -0.483856;-0.027354;0.874720;,
  -0.034105;0.999313;-0.014478;,
  -0.156829;0.411056;-0.898019;,
  0.418992;0.460088;-0.782793;,
  0.836422;0.423609;-0.347784;,
  0.915154;0.402762;0.016584;,
  0.833776;0.416463;0.362458;,
  -0.400336;0.853788;-0.332832;,
  -0.139884;0.885921;-0.442240;,
  -0.512013;0.833616;-0.207188;,
  -0.538118;0.833479;-0.125468;,
  -0.524972;0.851093;0.006702;,
  -0.431626;0.882644;0.186117;,
  -0.211192;0.914907;0.344011;,
  0.064474;0.906686;0.416851;,
  0.309219;0.880065;0.360374;,
  0.488140;0.847259;0.209457;,
  0.543681;0.839023;0.021258;,
  0.477124;0.860426;-0.178942;,
  0.221848;0.899364;-0.376733;,
  -0.839383;0.413006;-0.353358;,
  -0.661828;0.310620;-0.682275;,
  0.037665;0.499602;0.865436;,
  0.442916;0.374800;0.814463;,
  -0.904010;0.413554;-0.108343;,
  -0.892626;0.420953;0.161296;,
  -0.762712;0.459568;0.455047;,
  -0.419498;0.507067;0.752931;,
  -0.010142;-0.999819;-0.016094;,
  0.036197;-0.985796;0.164001;,
  -0.010756;-0.984782;0.173464;,
  -0.111374;-0.982868;-0.146853;,
  -0.170958;-0.980388;-0.098045;,
  -0.218221;-0.975817;-0.012674;,
  -0.199183;-0.977050;0.075490;,
  -0.116515;-0.981514;0.151835;;
  85;
  4;20,23,35,34;,
  4;9,15,8,0;,
  4;28,38,21,29;,
  4;6,15,9,1;,
  4;12,16,6,1;,
  4;21,25,37,29;,
  4;27,19,22,30;,
  4;22,24,36,30;,
  4;39,38,28,31;,
  4;37,25,17,32;,
  4;10,65,46,4;,
  4;17,19,27,32;,
  4;35,23,18,33;,
  4;18,40,26,33;,
  4;36,24,20,34;,
  4;10,36,34,0;,
  4;33,26,12,1;,
  4;9,35,33,1;,
  4;32,27,13,2;,
  4;11,37,32,2;,
  4;31,28,14,3;,
  4;30,36,10,4;,
  4;13,27,30,4;,
  4;29,37,11,5;,
  4;14,28,29,5;,
  4;34,35,9,0;,
  4;47,13,4,46;,
  4;48,2,13,47;,
  4;49,11,2,48;,
  4;50,5,11,49;,
  4;67,14,5,50;,
  4;42,26,40,41;,
  4;39,31,42,41;,
  4;43,12,26,42;,
  4;31,3,43,42;,
  4;44,16,12,43;,
  4;3,7,44,43;,
  3;52,51,45;,
  3;51,53,45;,
  3;53,54,45;,
  3;54,55,45;,
  3;55,56,45;,
  3;56,57,45;,
  3;57,58,45;,
  3;58,59,45;,
  3;59,60,45;,
  3;60,61,45;,
  3;61,62,45;,
  3;62,63,45;,
  3;63,52,45;,
  3;65,8,64;,
  3;67,66,7;,
  4;68,64,8,15;,
  4;6,69,68,15;,
  4;16,70,69,6;,
  4;44,71,70,16;,
  4;7,66,71,44;,
  4;52,46,65,51;,
  4;59,67,50,60;,
  4;60,50,49,61;,
  4;61,49,48,62;,
  4;62,48,47,63;,
  4;63,47,46,52;,
  4;64,53,51,65;,
  4;67,59,58,66;,
  4;68,54,53,64;,
  4;69,55,54,68;,
  4;70,56,55,69;,
  4;71,57,56,70;,
  4;66,58,57,71;,
  4;7,3,14,67;,
  4;65,10,0,8;,
  3;72,73,74;,
  3;72,20,24;,
  3;72,23,20;,
  3;72,18,23;,
  3;72,40,18;,
  3;72,41,40;,
  3;72,39,41;,
  3;72,75,39;,
  3;72,76,75;,
  3;72,77,76;,
  3;72,78,77;,
  3;72,79,78;,
  3;72,74,79;;
 }
 MeshTextureCoords {
  121;
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
  0.000000;0.125000;,
  0.076920;0.125000;,
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
  0.153850;0.125000;,
  0.615380;0.125000;,
  0.538460;0.125000;,
  0.230770;0.125000;,
  0.307690;0.125000;,
  0.384620;0.125000;,
  0.461540;0.125000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  2.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  2.000000;0.000000;,
  0.038460;1.000000;,
  0.076920;0.500000;,
  0.000000;0.500000;,
  0.115380;1.000000;,
  0.153850;0.500000;,
  0.192310;1.000000;,
  0.230770;0.500000;,
  0.269230;1.000000;,
  0.307690;0.500000;,
  0.346150;1.000000;,
  0.384620;0.500000;,
  0.423080;1.000000;,
  0.461540;0.500000;,
  0.500000;1.000000;,
  0.538460;0.500000;,
  0.576920;1.000000;,
  0.615380;0.500000;,
  0.653850;1.000000;,
  0.692310;0.500000;,
  0.730770;1.000000;,
  0.769230;0.500000;,
  0.807690;1.000000;,
  0.846150;0.500000;,
  0.884620;1.000000;,
  0.923080;0.500000;,
  0.961540;1.000000;,
  1.000000;0.500000;;
 }
}
