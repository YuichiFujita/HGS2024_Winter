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
 250;
 -0.02681;2.88864;3.09875;,
 -0.02681;0.98594;3.46189;,
 1.61032;1.15878;3.34729;,
 1.49733;3.06419;3.00187;,
 1.59948;5.12238;2.14945;,
 -0.02681;4.95498;2.23176;,
 3.86087;3.46277;2.09179;,
 3.79098;5.60172;1.75474;,
 3.90180;1.28527;2.57586;,
 2.70849;9.47866;-0.40976;,
 3.89145;8.98297;-0.63040;,
 3.42593;8.61232;-1.37012;,
 1.85237;9.05364;-1.38088;,
 1.65660;8.13932;-2.06276;,
 -0.02681;8.17384;-2.26141;,
 -0.02681;8.91788;-1.77478;,
 2.97497;7.90334;-1.87471;,
 3.88549;3.16525;-2.06670;,
 4.13318;0.79574;-2.38089;,
 2.29122;0.78060;-3.44984;,
 2.13629;3.00978;-3.24116;,
 2.08110;5.28079;-2.78699;,
 3.50799;5.60145;-1.90883;,
 -0.02681;2.99342;-3.37616;,
 -0.02681;5.18575;-2.96890;,
 -0.02681;0.73889;-3.57958;,
 2.04339;9.20936;1.03186;,
 3.86161;8.83234;0.61680;,
 3.95549;9.02202;0.04485;,
 2.48936;9.49770;0.41558;,
 4.79490;0.98994;1.05441;,
 4.47438;-0.36402;2.65288;,
 5.45354;-0.67304;1.32619;,
 5.76767;-0.77519;-0.03559;,
 5.16171;0.65473;-0.15665;,
 4.71975;-0.61600;-2.47823;,
 1.98706;-0.84036;-3.87061;,
 -0.02681;-1.00884;-3.99526;,
 4.94985;0.67947;-1.37881;,
 5.56206;-0.64786;-1.38508;,
 4.78800;8.24037;-0.73249;,
 4.81343;8.34529;0.09455;,
 2.76389;6.93644;-2.07191;,
 3.74774;7.43313;-1.83127;,
 3.38524;7.05102;-1.90712;,
 4.77952;3.11647;0.02601;,
 4.55809;3.36000;1.04844;,
 4.18317;5.14784;1.03617;,
 4.18914;5.03606;0.08333;,
 4.54414;3.12404;-1.08233;,
 3.91811;5.05593;-0.81217;,
 4.30791;7.86322;-1.41644;,
 0.03603;0.08494;3.75703;,
 2.48200;0.09424;3.62346;,
 1.80246;8.02487;1.89019;,
 3.44596;7.97446;1.60590;,
 3.69857;8.56390;1.12585;,
 1.31943;8.95823;1.52988;,
 -0.02681;8.71761;1.76566;,
 -0.02681;7.96562;2.05788;,
 -0.02681;6.94439;-2.48118;,
 1.59011;6.92191;-2.32960;,
 3.13832;6.97652;1.88363;,
 1.69968;6.82242;2.07752;,
 -0.02681;6.69107;2.19312;,
 -0.02681;-1.48311;4.77278;,
 -0.02681;-1.53908;3.27159;,
 1.86124;-1.63045;3.11865;,
 2.82182;-1.60330;4.16725;,
 4.81857;-2.06694;2.39511;,
 4.95160;-2.02929;2.62035;,
 5.79335;-1.83338;-1.42907;,
 4.93512;-1.73769;-2.53283;,
 5.08500;-1.79306;-2.85339;,
 6.02940;-1.87016;-1.63392;,
 6.25160;-2.04683;-0.10633;,
 5.99598;-2.01498;-0.03922;,
 2.09688;-1.84763;-3.01963;,
 -0.02681;-1.92256;-3.16411;,
 -0.02681;-1.95937;-4.43955;,
 2.06658;-1.89780;-4.31345;,
 5.71883;-2.11494;1.45010;,
 5.94501;-2.11949;1.53026;,
 4.68187;8.23994;0.68946;,
 4.55651;8.12179;1.05287;,
 4.33432;7.79879;1.43145;,
 3.93169;7.08423;1.69173;,
 3.74687;6.11604;1.41193;,
 3.45379;6.17898;-1.35965;,
 3.83980;5.83703;0.26258;,
 3.81557;5.83716;-0.09290;,
 3.67415;6.45957;-1.11431;,
 3.92796;6.45400;1.09249;,
 4.02991;6.63822;-0.26915;,
 4.07838;6.63800;0.44182;,
 4.39831;7.43897;0.56564;,
 4.42716;7.43929;-0.50081;,
 4.02898;7.16139;-1.26538;,
 4.26090;7.28789;1.07268;,
 3.13832;6.97652;1.88363;,
 3.93169;7.08423;1.69173;,
 3.44596;7.97446;1.60590;,
 4.33432;7.79879;1.43145;,
 3.44596;7.97446;1.60590;,
 3.93169;7.08423;1.69173;,
 3.74774;7.43313;-1.83127;,
 3.38524;7.05102;-1.90712;,
 2.97497;7.90334;-1.87471;,
 2.76389;6.93644;-2.07191;,
 2.97497;7.90334;-1.87471;,
 3.38524;7.05102;-1.90712;,
 -1.55095;3.06419;3.00187;,
 -1.66394;1.15878;3.34729;,
 -1.65310;5.12238;2.14945;,
 -3.84460;5.60172;1.75474;,
 -3.91449;3.46277;2.09179;,
 -3.95542;1.28527;2.57586;,
 -1.90599;9.05364;-1.38088;,
 -3.47955;8.61232;-1.37012;,
 -3.94507;8.98297;-0.63040;,
 -2.76211;9.47866;-0.40976;,
 -1.71022;8.13932;-2.06276;,
 -3.02859;7.90334;-1.87471;,
 -2.18991;3.00978;-3.24116;,
 -2.34484;0.78060;-3.44984;,
 -4.18680;0.79574;-2.38089;,
 -3.93911;3.16525;-2.06670;,
 -3.56161;5.60145;-1.90883;,
 -2.13472;5.28079;-2.78699;,
 -2.54298;9.49770;0.41558;,
 -4.00911;9.02202;0.04485;,
 -3.91523;8.83234;0.61680;,
 -2.09701;9.20936;1.03186;,
 -5.50716;-0.67304;1.32619;,
 -4.52800;-0.36402;2.65288;,
 -4.84852;0.98994;1.05441;,
 -5.21533;0.65473;-0.15665;,
 -5.82129;-0.77519;-0.03559;,
 -2.04068;-0.84036;-3.87061;,
 -4.77337;-0.61600;-2.47823;,
 -5.61567;-0.64786;-1.38508;,
 -5.00346;0.67947;-1.37881;,
 -4.86704;8.34529;0.09455;,
 -4.84162;8.24037;-0.73249;,
 -3.43886;7.05102;-1.90712;,
 -3.80136;7.43313;-1.83127;,
 -2.81751;6.93644;-2.07191;,
 -4.61171;3.36000;1.04844;,
 -4.83314;3.11647;0.02601;,
 -4.23679;5.14784;1.03617;,
 -4.24276;5.03606;0.08333;,
 -4.59776;3.12404;-1.08233;,
 -3.97173;5.05593;-0.81217;,
 -4.36153;7.86322;-1.41644;,
 -2.40994;0.09424;3.62346;,
 -1.37305;8.95823;1.52988;,
 -3.75219;8.56390;1.12585;,
 -3.49958;7.97446;1.60590;,
 -1.85608;8.02487;1.89019;,
 -1.64373;6.92191;-2.32960;,
 -1.75330;6.82242;2.07752;,
 -3.19194;6.97652;1.88363;,
 -2.41757;-1.60330;4.27969;,
 -1.91486;-1.63045;3.11865;,
 -5.00522;-2.02929;2.62035;,
 -4.87219;-2.06694;2.39511;,
 -6.08301;-1.87016;-1.63392;,
 -5.13862;-1.79306;-2.85339;,
 -4.98874;-1.73769;-2.53283;,
 -5.84697;-1.83338;-1.42907;,
 -6.04959;-2.01498;-0.03922;,
 -6.30522;-2.04683;-0.10633;,
 -2.12020;-1.89780;-4.31345;,
 -2.15050;-1.84763;-3.01963;,
 -5.99862;-2.11949;1.53026;,
 -5.77245;-2.11494;1.45010;,
 -4.61013;8.12179;1.05287;,
 -4.73549;8.23994;0.68946;,
 -4.38794;7.79879;1.43145;,
 -3.98531;7.08423;1.69173;,
 -3.80049;6.11604;1.41193;,
 -3.50741;6.17898;-1.35965;,
 -3.86919;5.83716;-0.09290;,
 -3.89342;5.83703;0.26258;,
 -3.72777;6.45957;-1.11431;,
 -3.98158;6.45400;1.09249;,
 -4.13200;6.63800;0.44182;,
 -4.08353;6.63822;-0.26915;,
 -4.45193;7.43897;0.56564;,
 -4.48077;7.43929;-0.50081;,
 -4.08260;7.16139;-1.26538;,
 -4.31452;7.28789;1.07268;,
 -3.49958;7.97446;1.60590;,
 -3.98531;7.08423;1.69173;,
 -3.19194;6.97652;1.88363;,
 -4.38794;7.79879;1.43145;,
 -3.02859;7.90334;-1.87471;,
 -3.43886;7.05102;-1.90712;,
 -3.80136;7.43313;-1.83127;,
 -2.81751;6.93644;-2.07191;,
 -0.02681;-1.36084;-1.85987;,
 -1.09591;-1.36084;-1.71647;,
 -2.15050;-1.84763;-3.01963;,
 -0.02681;-1.92256;-3.16411;,
 -2.00226;-1.36084;-1.30809;,
 -4.98874;-1.73769;-2.53283;,
 -2.60785;-1.36084;-0.69690;,
 -5.84697;-1.83338;-1.42907;,
 -2.82052;-1.36084;0.02404;,
 -6.04959;-2.01498;-0.03922;,
 -2.60785;-1.36084;0.74499;,
 -5.77245;-2.11494;1.45010;,
 -2.00226;-1.36084;1.35618;,
 -4.87219;-2.06694;2.39511;,
 -1.09591;-1.36084;1.76456;,
 -1.91486;-1.63045;3.11865;,
 -0.02681;-1.36084;1.90796;,
 -0.02681;-1.53908;3.27159;,
 1.04229;-1.36084;1.76456;,
 1.86124;-1.63045;3.11865;,
 1.94864;-1.36084;1.35618;,
 4.81857;-2.06694;2.39511;,
 2.55423;-1.36084;0.74499;,
 5.71883;-2.11494;1.45010;,
 2.76690;-1.36084;0.02404;,
 5.99598;-2.01498;-0.03922;,
 2.55423;-1.36084;-0.69690;,
 5.79335;-1.83338;-1.42907;,
 1.94864;-1.36084;-1.30809;,
 4.93512;-1.73769;-2.53283;,
 1.04229;-1.36084;-1.71647;,
 2.09688;-1.84763;-3.01963;,
 -0.02681;-1.36084;-1.85987;,
 -0.02681;-1.92256;-3.16411;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;,
 -0.02681;-0.94853;0.02404;;
 
 226;
 4;0,1,2,3;,
 4;4,5,0,3;,
 4;6,7,4,3;,
 4;2,8,6,3;,
 4;9,10,11,12;,
 4;13,14,15,12;,
 4;11,16,13,12;,
 4;17,18,19,20;,
 4;21,22,17,20;,
 4;23,24,21,20;,
 4;19,25,23,20;,
 4;26,27,28,29;,
 4;28,10,9,29;,
 4;30,8,31,32;,
 4;33,34,30,32;,
 4;19,18,35,36;,
 4;37,25,19,36;,
 4;38,34,33,39;,
 4;35,18,38,39;,
 4;40,10,28,41;,
 4;42,16,43,44;,
 4;30,34,45,46;,
 4;6,8,30,46;,
 4;47,7,6,46;,
 4;45,48,47,46;,
 4;38,18,17,49;,
 4;45,34,38,49;,
 4;50,48,45,49;,
 4;17,22,50,49;,
 4;43,16,11,51;,
 4;11,10,40,51;,
 4;2,1,52,53;,
 4;31,8,2,53;,
 4;54,55,56,57;,
 4;58,59,54,57;,
 4;56,27,26,57;,
 4;21,24,60,61;,
 4;42,22,21,61;,
 4;13,16,42,61;,
 4;60,14,13,61;,
 4;4,7,62,63;,
 4;64,5,4,63;,
 4;54,59,64,63;,
 4;62,55,54,63;,
 4;65,66,67,68;,
 4;67,69,70,68;,
 4;71,72,73,74;,
 4;75,76,71,74;,
 4;77,78,79,80;,
 4;73,72,77,80;,
 4;81,76,75,82;,
 4;70,69,81,82;,
 4;31,70,82,32;,
 4;82,75,33,32;,
 4;35,73,80,36;,
 4;80,79,37,36;,
 4;33,75,74,39;,
 4;74,73,35,39;,
 4;68,70,31,53;,
 4;52,65,68,53;,
 4;83,27,56,84;,
 4;28,27,83,41;,
 3;56,55,85;,
 3;84,56,85;,
 3;44,22,42;,
 3;62,7,86;,
 4;62,86,85,55;,
 3;86,7,87;,
 3;7,47,87;,
 3;50,22,88;,
 3;22,44,88;,
 3;89,48,90;,
 3;50,88,91;,
 3;87,47,92;,
 4;93,94,89,90;,
 4;90,48,50,91;,
 4;47,48,89,92;,
 3;93,90,91;,
 3;89,94,92;,
 3;41,83,95;,
 3;40,41,96;,
 3;41,95,96;,
 3;43,51,97;,
 3;84,85,98;,
 4;95,98,92,94;,
 4;91,97,96,93;,
 4;93,96,95,94;,
 4;96,97,51,40;,
 4;84,98,95,83;,
 3;99,100,101;,
 3;102,103,104;,
 3;105,106,107;,
 3;108,109,110;,
 3;43,88,44;,
 3;86,87,85;,
 4;87,92,98,85;,
 4;43,97,91,88;,
 4;111,112,1,0;,
 4;111,0,5,113;,
 4;111,113,114,115;,
 4;111,115,116,112;,
 4;117,118,119,120;,
 4;117,15,14,121;,
 4;117,121,122,118;,
 4;123,124,125,126;,
 4;123,126,127,128;,
 4;123,128,24,23;,
 4;123,23,25,124;,
 4;129,130,131,132;,
 4;129,120,119,130;,
 4;133,134,116,135;,
 4;133,135,136,137;,
 4;138,139,125,124;,
 4;138,124,25,37;,
 4;140,137,136,141;,
 4;140,141,125,139;,
 4;142,130,119,143;,
 4;144,145,122,146;,
 4;147,148,136,135;,
 4;147,135,116,115;,
 4;147,115,114,149;,
 4;147,149,150,148;,
 4;151,126,125,141;,
 4;151,141,136,148;,
 4;151,148,150,152;,
 4;151,152,127,126;,
 4;153,118,122,145;,
 4;153,143,119,118;,
 4;154,52,1,112;,
 4;154,112,116,134;,
 4;155,156,157,158;,
 4;155,158,59,58;,
 4;155,132,131,156;,
 4;159,60,24,128;,
 4;159,128,127,146;,
 4;159,146,122,121;,
 4;159,121,14,60;,
 4;160,161,114,113;,
 4;160,113,5,64;,
 4;160,64,59,158;,
 4;160,158,157,161;,
 4;162,163,66,65;,
 4;162,164,165,163;,
 4;166,167,168,169;,
 4;166,169,170,171;,
 4;172,79,78,173;,
 4;172,173,168,167;,
 4;174,171,170,175;,
 4;174,175,165,164;,
 4;133,174,164,134;,
 4;133,137,171,174;,
 4;138,172,167,139;,
 4;138,37,79,172;,
 4;140,166,171,137;,
 4;140,139,167,166;,
 4;154,134,164,162;,
 4;154,162,65,52;,
 4;176,156,131,177;,
 4;142,177,131,130;,
 3;178,157,156;,
 3;178,156,176;,
 3;146,127,144;,
 3;179,114,161;,
 4;157,178,179,161;,
 3;180,114,179;,
 3;180,149,114;,
 3;181,127,152;,
 3;181,144,127;,
 3;182,150,183;,
 3;184,181,152;,
 3;185,149,180;,
 4;182,183,186,187;,
 4;184,152,150,182;,
 4;185,183,150,149;,
 3;184,182,187;,
 3;185,186,183;,
 3;188,177,142;,
 3;189,142,143;,
 3;189,188,142;,
 3;190,153,145;,
 3;191,178,176;,
 4;186,185,191,188;,
 4;187,189,190,184;,
 4;186,188,189,187;,
 4;143,153,190,189;,
 4;177,188,191,176;,
 3;192,193,194;,
 3;193,192,195;,
 3;196,197,198;,
 3;197,196,199;,
 3;144,181,145;,
 3;178,180,179;,
 4;178,191,185,180;,
 4;181,184,190,145;,
 4;200,201,202,203;,
 4;201,204,205,202;,
 4;204,206,207,205;,
 4;206,208,209,207;,
 4;208,210,211,209;,
 4;210,212,213,211;,
 4;212,214,215,213;,
 4;214,216,217,215;,
 4;216,218,219,217;,
 4;218,220,221,219;,
 4;220,222,223,221;,
 4;222,224,225,223;,
 4;224,226,227,225;,
 4;226,228,229,227;,
 4;228,230,231,229;,
 4;230,232,233,231;,
 3;234,201,200;,
 3;235,204,201;,
 3;236,206,204;,
 3;237,208,206;,
 3;238,210,208;,
 3;239,212,210;,
 3;240,214,212;,
 3;241,216,214;,
 3;242,218,216;,
 3;243,220,218;,
 3;244,222,220;,
 3;245,224,222;,
 3;246,226,224;,
 3;247,228,226;,
 3;248,230,228;,
 3;249,232,230;;
 
 MeshMaterialList {
  2;
  226;
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
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  229;
  -0.000000;0.285986;0.958234;,
  -0.000082;0.242172;0.970233;,
  0.195123;0.255986;0.946783;,
  0.147154;0.259564;0.954449;,
  0.110586;0.174631;0.978404;,
  0.000000;0.211125;0.977459;,
  0.603798;0.190763;0.773975;,
  0.532685;0.160721;0.830913;,
  0.622563;0.262246;0.737321;,
  0.301908;0.906982;-0.293659;,
  0.440790;0.828330;-0.345793;,
  0.303347;0.607155;-0.734401;,
  0.180100;0.642093;-0.745172;,
  0.151618;0.373144;-0.915301;,
  0.000000;0.385618;-0.922659;,
  0.000000;0.563750;-0.825945;,
  0.201086;0.252323;-0.946519;,
  0.701967;0.187555;-0.687070;,
  0.646797;0.223330;-0.729231;,
  0.279008;0.173408;-0.944502;,
  0.299454;0.149171;-0.942377;,
  0.259454;0.221645;-0.939977;,
  0.749767;0.199044;-0.631055;,
  -0.000000;0.141980;-0.989869;,
  0.000000;0.234106;-0.972211;,
  -0.000000;0.165623;-0.986189;,
  0.296524;0.791171;0.534904;,
  0.409848;0.783898;0.466400;,
  0.483876;0.859141;0.166554;,
  0.350130;0.907602;0.231663;,
  0.903178;0.247691;0.350598;,
  0.641574;0.311891;0.700790;,
  0.866902;0.346428;0.358425;,
  0.925120;0.378136;0.034158;,
  0.960922;0.275974;0.021632;,
  0.600030;0.342580;-0.722913;,
  0.239281;0.315184;-0.918370;,
  -0.000000;0.322628;-0.946526;,
  0.882753;0.283591;-0.374598;,
  0.853993;0.389080;-0.345418;,
  0.567273;0.726301;-0.388187;,
  0.604800;0.790328;0.097970;,
  0.238745;0.143674;-0.960395;,
  0.500754;-0.111106;-0.858429;,
  0.278189;-0.004907;-0.960514;,
  0.975779;0.216035;-0.034419;,
  0.931994;0.155961;0.327206;,
  0.934339;0.230990;0.271392;,
  0.944650;0.310112;-0.107081;,
  0.906208;0.232434;-0.353216;,
  0.912955;0.226290;-0.339567;,
  0.391393;0.525560;-0.755379;,
  0.000921;0.376602;0.926375;,
  0.276800;0.339573;0.898929;,
  0.124716;0.304187;0.944413;,
  0.211124;0.315605;0.925106;,
  0.314927;0.641644;0.699367;,
  0.182233;0.562498;0.806466;,
  0.000000;0.377259;0.926108;,
  0.000000;0.253786;0.967260;,
  -0.000000;0.235002;-0.971995;,
  0.182508;0.225031;-0.957106;,
  0.191443;0.125649;0.973428;,
  0.107276;0.087410;0.990380;,
  0.000000;0.078327;0.996928;,
  0.002752;-0.999094;0.042471;,
  0.001382;-0.998680;-0.051354;,
  -0.072371;-0.997105;-0.023331;,
  -0.061036;-0.992665;0.104359;,
  -0.095913;-0.995251;-0.016631;,
  -0.032641;-0.991719;0.124210;,
  -0.157739;-0.987473;-0.004009;,
  -0.086306;-0.989238;0.118151;,
  -0.082802;-0.993848;0.073550;,
  -0.174142;-0.984494;-0.021124;,
  -0.127785;-0.988478;-0.081127;,
  -0.158189;-0.985011;-0.068777;,
  -0.015030;-0.980665;0.195115;,
  0.000000;-0.978151;0.207895;,
  0.000000;-0.999442;0.033416;,
  0.013288;-0.997836;0.064390;,
  -0.112617;-0.992030;-0.056512;,
  -0.025355;-0.999644;0.008360;,
  0.516074;0.762808;0.389605;,
  0.421284;0.677113;0.603355;,
  0.421902;0.279298;0.862549;,
  0.368453;0.076237;0.926515;,
  0.953884;-0.068932;0.292152;,
  0.887279;-0.099776;-0.450311;,
  0.998632;0.035825;-0.038097;,
  0.987264;0.025186;-0.157083;,
  0.896489;-0.201722;-0.394481;,
  0.970986;-0.126441;0.202973;,
  0.913940;-0.370715;-0.165181;,
  0.939063;-0.341197;0.041786;,
  0.922374;-0.375759;0.089624;,
  0.895552;-0.431400;-0.108999;,
  0.803410;-0.438148;-0.403186;,
  0.917093;-0.343128;0.202986;,
  -0.147154;0.259564;0.954449;,
  -0.192500;0.250180;0.948870;,
  -0.110586;0.174631;0.978404;,
  -0.532685;0.160721;0.830913;,
  -0.603798;0.190763;0.773975;,
  -0.620418;0.257921;0.740647;,
  -0.180100;0.642093;-0.745171;,
  -0.303347;0.607155;-0.734401;,
  -0.440791;0.828330;-0.345792;,
  -0.301908;0.906982;-0.293659;,
  -0.151618;0.373144;-0.915301;,
  -0.201086;0.252323;-0.946519;,
  -0.299454;0.149171;-0.942377;,
  -0.279008;0.173408;-0.944502;,
  -0.646799;0.223330;-0.729229;,
  -0.701968;0.187555;-0.687070;,
  -0.749767;0.199044;-0.631055;,
  -0.259454;0.221645;-0.939977;,
  -0.350130;0.907602;0.231663;,
  -0.483877;0.859141;0.166554;,
  -0.409849;0.783898;0.466399;,
  -0.296524;0.791171;0.534904;,
  -0.866904;0.346412;0.358437;,
  -0.631515;0.302625;0.713868;,
  -0.903178;0.247691;0.350599;,
  -0.960922;0.275974;0.021630;,
  -0.925125;0.378122;0.034167;,
  -0.239281;0.315184;-0.918370;,
  -0.600032;0.342580;-0.722911;,
  -0.853992;0.389080;-0.345419;,
  -0.882753;0.283590;-0.374599;,
  -0.604803;0.790326;0.097969;,
  -0.567274;0.726300;-0.388185;,
  -0.278189;-0.004907;-0.960514;,
  -0.500754;-0.111105;-0.858429;,
  -0.238745;0.143674;-0.960395;,
  -0.931994;0.155961;0.327206;,
  -0.975779;0.216034;-0.034420;,
  -0.934339;0.230990;0.271392;,
  -0.944650;0.310112;-0.107081;,
  -0.906208;0.232433;-0.353216;,
  -0.912955;0.226290;-0.339567;,
  -0.391393;0.525560;-0.755379;,
  -0.263110;0.329887;0.906613;,
  -0.182233;0.562498;0.806466;,
  -0.314927;0.641644;0.699367;,
  -0.211124;0.315605;0.925106;,
  -0.124716;0.304187;0.944413;,
  -0.182508;0.225031;-0.957106;,
  -0.107276;0.087410;0.990380;,
  -0.191443;0.125649;0.973428;,
  0.063858;-0.994205;0.086483;,
  0.073707;-0.996758;-0.032261;,
  0.032737;-0.993449;0.109483;,
  0.095848;-0.995106;-0.024021;,
  0.174143;-0.984494;-0.021124;,
  0.082804;-0.993848;0.073550;,
  0.086307;-0.989238;0.118152;,
  0.157739;-0.987473;-0.004009;,
  0.158189;-0.985011;-0.068777;,
  0.127784;-0.988478;-0.081127;,
  -0.013288;-0.997836;0.064390;,
  0.015030;-0.980665;0.195115;,
  0.025354;-0.999644;0.008360;,
  0.112616;-0.992030;-0.056511;,
  -0.421284;0.677113;0.603355;,
  -0.516075;0.762808;0.389603;,
  -0.421903;0.279298;0.862549;,
  -0.368453;0.076237;0.926515;,
  -0.953884;-0.068932;0.292152;,
  -0.887279;-0.099776;-0.450311;,
  -0.987264;0.025186;-0.157083;,
  -0.998632;0.035825;-0.038098;,
  -0.896490;-0.201721;-0.394481;,
  -0.970986;-0.126441;0.202973;,
  -0.939063;-0.341196;0.041785;,
  -0.913940;-0.370713;-0.165181;,
  -0.922375;-0.375757;0.089619;,
  -0.895553;-0.431399;-0.108998;,
  -0.803411;-0.438148;-0.403184;,
  -0.917093;-0.343127;0.202986;,
  0.000000;-0.955209;0.295931;,
  0.049321;-0.964171;0.260655;,
  0.096163;-0.982852;0.157335;,
  0.138048;-0.989267;0.047893;,
  0.167303;-0.985502;-0.028206;,
  0.166584;-0.980774;-0.101643;,
  0.129771;-0.979432;-0.154510;,
  0.068935;-0.982285;-0.174252;,
  0.000000;-0.983781;-0.179376;,
  -0.068935;-0.982285;-0.174252;,
  -0.129771;-0.979432;-0.154510;,
  -0.166584;-0.980774;-0.101643;,
  -0.167303;-0.985502;-0.028206;,
  -0.138048;-0.989267;0.047893;,
  -0.096163;-0.982852;0.157335;,
  -0.049321;-0.964171;0.260655;,
  -0.000000;-1.000000;0.000000;,
  0.659797;0.269720;0.701369;,
  0.862510;0.315521;0.395630;,
  0.933118;0.356811;0.044466;,
  0.578207;0.401204;-0.710431;,
  0.216629;0.401608;-0.889821;,
  0.000000;0.405719;-0.913998;,
  0.856001;0.394180;-0.334493;,
  0.343767;0.359742;0.867416;,
  0.002007;0.451827;0.892103;,
  0.955495;-0.102447;-0.276648;,
  0.996389;0.084363;0.009618;,
  0.919628;-0.387594;0.063677;,
  0.924701;-0.345320;0.160258;,
  0.892284;-0.427038;-0.146522;,
  0.791661;-0.425965;-0.437980;,
  0.918034;-0.328996;0.221304;,
  0.909861;-0.326745;0.255715;,
  -0.862512;0.315487;0.395652;,
  -0.643605;0.259250;0.720113;,
  -0.933128;0.356782;0.044488;,
  -0.216629;0.401608;-0.889821;,
  -0.578209;0.401204;-0.710429;,
  -0.856000;0.394180;-0.334493;,
  -0.321685;0.352274;0.878875;,
  -0.955495;-0.102447;-0.276647;,
  -0.996389;0.084363;0.009618;,
  -0.924702;-0.345320;0.160251;,
  -0.919629;-0.387594;0.063673;,
  -0.892283;-0.427043;-0.146512;,
  -0.791662;-0.425967;-0.437977;,
  -0.909861;-0.326744;0.255715;,
  -0.918034;-0.328996;0.221304;;
  226;
  4;0,1,2,3;,
  4;4,5,0,3;,
  4;6,7,4,3;,
  4;2,8,6,3;,
  4;9,10,11,12;,
  4;13,14,15,12;,
  4;11,16,13,12;,
  4;17,18,19,20;,
  4;21,22,17,20;,
  4;23,24,21,20;,
  4;19,25,23,20;,
  4;26,27,28,29;,
  4;28,10,9,29;,
  4;30,8,31,32;,
  4;33,34,30,32;,
  4;19,18,35,36;,
  4;37,25,19,36;,
  4;38,34,33,39;,
  4;35,18,38,39;,
  4;40,10,28,41;,
  4;42,16,43,44;,
  4;30,34,45,46;,
  4;6,8,30,46;,
  4;47,7,6,46;,
  4;45,48,47,46;,
  4;38,18,17,49;,
  4;45,34,38,49;,
  4;50,48,45,49;,
  4;17,22,50,49;,
  4;43,16,11,51;,
  4;11,10,40,51;,
  4;2,1,52,53;,
  4;31,8,2,53;,
  4;54,55,56,57;,
  4;58,59,54,57;,
  4;56,27,26,57;,
  4;21,24,60,61;,
  4;42,22,21,61;,
  4;13,16,42,61;,
  4;60,14,13,61;,
  4;4,7,62,63;,
  4;64,5,4,63;,
  4;54,59,64,63;,
  4;62,55,54,63;,
  4;65,66,67,68;,
  4;67,69,70,68;,
  4;71,72,73,74;,
  4;75,76,71,74;,
  4;77,78,79,80;,
  4;73,72,77,80;,
  4;81,76,75,82;,
  4;70,69,81,82;,
  4;31,197,198,32;,
  4;198,199,33,32;,
  4;35,200,201,36;,
  4;201,202,37,36;,
  4;33,199,203,39;,
  4;203,200,35,39;,
  4;204,197,31,53;,
  4;52,205,204,53;,
  4;83,27,56,84;,
  4;28,27,83,41;,
  3;56,55,85;,
  3;84,56,85;,
  3;44,22,42;,
  3;62,7,86;,
  4;62,86,85,55;,
  3;206,206,87;,
  3;7,47,87;,
  3;50,22,88;,
  3;22,207,88;,
  3;89,48,90;,
  3;50,88,91;,
  3;87,47,92;,
  4;93,94,89,90;,
  4;90,48,50,91;,
  4;47,48,89,92;,
  3;93,90,91;,
  3;89,94,92;,
  3;208,209,95;,
  3;210,208,96;,
  3;208,95,96;,
  3;43,211,97;,
  3;212,213,98;,
  4;95,98,92,94;,
  4;91,97,96,93;,
  4;93,96,95,94;,
  4;96,97,211,210;,
  4;212,98,95,209;,
  3;62,86,55;,
  3;85,55,86;,
  3;43,44,16;,
  3;42,16,44;,
  3;43,88,44;,
  3;86,87,85;,
  4;87,92,98,213;,
  4;43,97,91,88;,
  4;99,100,1,0;,
  4;99,0,5,101;,
  4;99,101,102,103;,
  4;99,103,104,100;,
  4;105,106,107,108;,
  4;105,15,14,109;,
  4;105,109,110,106;,
  4;111,112,113,114;,
  4;111,114,115,116;,
  4;111,116,24,23;,
  4;111,23,25,112;,
  4;117,118,119,120;,
  4;117,108,107,118;,
  4;121,122,104,123;,
  4;121,123,124,125;,
  4;126,127,113,112;,
  4;126,112,25,37;,
  4;128,125,124,129;,
  4;128,129,113,127;,
  4;130,118,107,131;,
  4;132,133,110,134;,
  4;135,136,124,123;,
  4;135,123,104,103;,
  4;135,103,102,137;,
  4;135,137,138,136;,
  4;139,114,113,129;,
  4;139,129,124,136;,
  4;139,136,138,140;,
  4;139,140,115,114;,
  4;141,106,110,133;,
  4;141,131,107,106;,
  4;142,52,1,100;,
  4;142,100,104,122;,
  4;143,144,145,146;,
  4;143,146,59,58;,
  4;143,120,119,144;,
  4;147,60,24,116;,
  4;147,116,115,134;,
  4;147,134,110,109;,
  4;147,109,14,60;,
  4;148,149,102,101;,
  4;148,101,5,64;,
  4;148,64,59,146;,
  4;148,146,145,149;,
  4;150,151,66,65;,
  4;150,152,153,151;,
  4;154,155,156,157;,
  4;154,157,158,159;,
  4;160,79,78,161;,
  4;160,161,156,155;,
  4;162,159,158,163;,
  4;162,163,153,152;,
  4;121,214,215,122;,
  4;121,125,216,214;,
  4;126,217,218,127;,
  4;126,37,202,217;,
  4;128,219,216,125;,
  4;128,127,218,219;,
  4;142,122,215,220;,
  4;142,220,205,52;,
  4;164,144,119,165;,
  4;130,165,119,118;,
  3;166,145,144;,
  3;166,144,164;,
  3;134,115,132;,
  3;167,102,149;,
  4;145,166,167,149;,
  3;168,221,221;,
  3;168,137,102;,
  3;169,115,140;,
  3;169,222,115;,
  3;170,138,171;,
  3;172,169,140;,
  3;173,137,168;,
  4;170,171,174,175;,
  4;172,140,138,170;,
  4;173,171,138,137;,
  3;172,170,175;,
  3;173,174,171;,
  3;176,223,224;,
  3;177,224,225;,
  3;177,176,224;,
  3;178,226,133;,
  3;179,227,228;,
  4;174,173,179,176;,
  4;175,177,178,172;,
  4;174,176,177,175;,
  4;225,226,178,177;,
  4;223,176,179,228;,
  3;145,167,149;,
  3;167,145,166;,
  3;110,132,133;,
  3;132,110,134;,
  3;132,169,133;,
  3;166,168,167;,
  4;227,179,173,168;,
  4;169,172,178,133;,
  4;180,181,161,78;,
  4;181,182,156,161;,
  4;182,183,157,156;,
  4;183,184,158,157;,
  4;184,185,163,158;,
  4;185,186,153,163;,
  4;186,187,151,153;,
  4;187,188,66,151;,
  4;188,189,67,66;,
  4;189,190,69,67;,
  4;190,191,81,69;,
  4;191,192,76,81;,
  4;192,193,71,76;,
  4;193,194,72,71;,
  4;194,195,77,72;,
  4;195,180,78,77;,
  3;196,181,180;,
  3;196,182,181;,
  3;196,183,182;,
  3;196,184,183;,
  3;196,185,184;,
  3;196,186,185;,
  3;196,187,186;,
  3;196,188,187;,
  3;196,189,188;,
  3;196,190,189;,
  3;196,191,190;,
  3;196,192,191;,
  3;196,193,192;,
  3;196,194,193;,
  3;196,195,194;,
  3;196,180,195;;
 }
 MeshTextureCoords {
  250;
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
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.750000;,
  0.062500;0.750000;,
  0.062500;0.500000;,
  0.000000;0.500000;,
  0.125000;0.750000;,
  0.125000;0.500000;,
  0.187500;0.750000;,
  0.187500;0.500000;,
  0.250000;0.750000;,
  0.250000;0.500000;,
  0.312500;0.750000;,
  0.312500;0.500000;,
  0.375000;0.750000;,
  0.375000;0.500000;,
  0.437500;0.750000;,
  0.437500;0.500000;,
  0.500000;0.750000;,
  0.500000;0.500000;,
  0.562500;0.750000;,
  0.562500;0.500000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.687500;0.750000;,
  0.687500;0.500000;,
  0.750000;0.750000;,
  0.750000;0.500000;,
  0.812500;0.750000;,
  0.812500;0.500000;,
  0.875000;0.750000;,
  0.875000;0.500000;,
  0.937500;0.750000;,
  0.937500;0.500000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  0.031250;1.000000;,
  0.093750;1.000000;,
  0.156250;1.000000;,
  0.218750;1.000000;,
  0.281250;1.000000;,
  0.343750;1.000000;,
  0.406250;1.000000;,
  0.468750;1.000000;,
  0.531250;1.000000;,
  0.593750;1.000000;,
  0.656250;1.000000;,
  0.718750;1.000000;,
  0.781250;1.000000;,
  0.843750;1.000000;,
  0.906250;1.000000;,
  0.968750;1.000000;;
 }
}
