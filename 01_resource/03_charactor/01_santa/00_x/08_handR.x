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
 194;
 1.95690;-0.62374;-1.47032;,
 1.93050;-0.21686;-1.48083;,
 2.68201;-0.27919;-1.36731;,
 2.66886;-0.78722;-1.33886;,
 2.57430;-1.11670;-1.17229;,
 1.94024;-0.92578;-1.29188;,
 3.24764;-0.85902;-1.22175;,
 3.10817;-1.27418;-0.86862;,
 3.31076;-0.31447;-1.26705;,
 1.75672;-0.89997;1.27553;,
 1.74805;-1.10794;1.00422;,
 2.41531;-1.04257;0.94515;,
 2.42356;-0.77680;1.26995;,
 2.47624;-0.40537;1.34314;,
 1.81335;-0.50416;1.32474;,
 2.91335;-0.61075;1.23477;,
 2.95711;-0.29727;1.31615;,
 2.91811;-0.87765;0.86637;,
 3.13896;-0.25760;1.12920;,
 3.11743;-0.42720;1.08539;,
 3.12267;-0.60610;0.81954;,
 3.17207;-0.26405;0.83569;,
 3.15056;0.55475;0.19229;,
 3.05372;0.30983;0.97240;,
 3.20023;0.05711;0.88156;,
 3.35847;0.17217;0.09831;,
 3.49481;0.19221;-0.64535;,
 3.21261;0.53468;-0.71233;,
 3.34896;-0.29992;0.02611;,
 3.48864;-0.30338;-0.65658;,
 1.85885;0.30793;-1.23213;,
 1.69196;0.79872;-0.69552;,
 2.65450;0.66274;-0.73232;,
 2.63045;0.31150;-1.13966;,
 3.30138;0.25455;-1.09764;,
 1.89496;0.07445;1.37447;,
 2.53978;0.06390;1.35138;,
 2.58375;0.49773;1.06931;,
 1.93563;0.60054;1.13795;,
 2.99771;0.02547;1.29562;,
 2.03311;-1.05338;-0.96508;,
 2.38179;-1.17065;-0.98596;,
 2.51352;-1.23694;-0.60091;,
 1.87814;-1.06297;-0.54168;,
 1.86917;0.83686;0.32654;,
 2.57769;0.76281;0.27158;,
 0.21936;-0.97291;0.76187;,
 0.08914;-0.63938;0.55655;,
 0.11332;-0.60252;0.01997;,
 0.27021;-0.87783;0.10332;,
 0.56443;-0.96375;0.19673;,
 0.48443;-1.02758;0.89093;,
 0.31250;-0.79537;-0.50173;,
 0.64297;-0.89040;-0.48852;,
 0.17490;-0.46424;-0.46692;,
 0.38382;0.45836;1.07860;,
 0.05979;0.24766;0.77148;,
 0.05654;0.01158;0.85117;,
 0.30946;0.01366;1.20888;,
 0.60043;0.02038;1.29889;,
 0.68572;0.51619;1.12426;,
 0.25285;-0.42958;1.11339;,
 0.52946;-0.50162;1.21523;,
 0.06768;-0.30975;0.78417;,
 0.57508;-0.00368;-1.29183;,
 0.16124;0.13201;-0.72704;,
 0.16452;0.38827;-0.51535;,
 0.59556;0.32554;-1.15482;,
 0.89270;0.24225;-1.48696;,
 0.84413;-0.08506;-1.63144;,
 0.60744;0.59107;-0.95013;,
 0.91652;0.52274;-1.22670;,
 0.14740;0.50591;-0.07359;,
 0.07411;-0.53507;0.72148;,
 0.21862;-0.78778;1.04288;,
 0.48175;-0.86262;1.15806;,
 0.39470;-0.60906;-1.10798;,
 0.16693;-0.18423;-0.70973;,
 0.49045;-0.31800;-1.22755;,
 0.79243;-0.39331;-1.54787;,
 0.74640;-0.66781;-1.39708;,
 0.77122;0.75859;0.37332;,
 1.25314;0.58651;1.15078;,
 1.25424;0.81608;0.35885;,
 1.20847;0.83968;-0.49848;,
 0.84376;0.79161;-0.45544;,
 1.19928;-0.98825;-0.43532;,
 0.64707;-0.98139;-0.74053;,
 1.20287;-1.08006;-0.69145;,
 1.70673;-1.13751;-0.71287;,
 1.18682;-1.19791;-0.78021;,
 1.56388;-1.20923;-0.77499;,
 0.63780;-1.10081;-0.83682;,
 1.10731;-0.52925;1.28616;,
 1.18910;0.05324;1.35706;,
 1.24754;0.60903;-1.14575;,
 1.29671;0.26071;-1.42919;,
 1.30691;-0.15409;-1.63161;,
 1.04951;-1.08564;0.98248;,
 1.05241;-0.91094;1.24076;,
 1.30607;-0.49596;-1.58455;,
 1.29364;-0.77108;-1.43634;,
 0.54467;0.78139;-0.35264;,
 0.66660;0.71748;-0.82125;,
 0.89497;0.69818;-0.96355;,
 0.20609;-0.76853;-0.78658;,
 0.31938;-0.92333;-0.65870;,
 0.35786;-1.02962;-0.81827;,
 0.31158;-0.96080;-0.88271;,
 0.34201;-0.98217;-1.06585;,
 0.38289;-1.05950;-0.99757;,
 0.67570;-1.11768;-1.06395;,
 0.69449;-1.03835;-1.26153;,
 0.45833;0.72085;0.38947;,
 0.10223;0.45686;0.37765;,
 1.13182;0.75481;-0.94916;,
 3.41753;-0.78158;-0.72318;,
 3.38338;-0.86053;-1.10704;,
 3.45734;-0.30103;-1.14151;,
 3.48886;0.08090;-1.10219;,
 3.01615;-1.12054;0.06231;,
 3.26949;-0.77651;0.01221;,
 3.16959;-0.08239;1.10167;,
 1.74749;-1.07877;-1.16479;,
 1.26890;-0.98717;-1.33515;,
 0.71578;-0.88653;-1.33702;,
 1.23725;-1.13645;-1.20982;,
 1.59703;-1.16653;-1.09539;,
 2.48500;-1.19493;0.18208;,
 1.80951;-1.12921;0.28692;,
 1.12340;-1.05019;0.27669;,
 1.69977;-1.24065;-0.90035;,
 1.20406;-1.21189;-0.98873;,
 1.89103;-1.13157;-0.91468;,
 0.34542;-0.83256;-1.07785;,
 0.03879;-0.34227;-0.30250;,
 0.08644;-0.05158;0.09583;,
 0.03314;-0.14376;-0.47463;,
 0.03314;-0.14376;-0.47463;,
 0.08644;-0.05158;0.09583;,
 0.02909;0.08042;-0.48691;,
 0.02909;0.08042;-0.48691;,
 0.02234;0.26209;-0.33714;,
 0.02234;0.26209;-0.33714;,
 0.08644;-0.05158;0.09583;,
 -0.00580;0.34549;-0.02448;,
 -0.00580;0.34549;-0.02448;,
 0.08644;-0.05158;0.09583;,
 -0.02802;0.31073;0.29573;,
 -0.02802;0.31073;0.29573;,
 0.08644;-0.05158;0.09583;,
 -0.04281;0.16240;0.57543;,
 -0.04281;0.16240;0.57543;,
 0.08644;-0.05158;0.09583;,
 -0.04512;-0.00495;0.63191;,
 -0.04512;-0.00495;0.63191;,
 0.08644;-0.05158;0.09583;,
 -0.03722;-0.23275;0.58441;,
 -0.03722;-0.23275;0.58441;,
 0.08644;-0.05158;0.09583;,
 -0.03267;-0.39248;0.53998;,
 -0.03267;-0.39248;0.53998;,
 0.08644;-0.05158;0.09583;,
 -0.02201;-0.46643;0.42305;,
 -0.02201;-0.46643;0.42305;,
 0.08644;-0.05158;0.09583;,
 -0.00489;-0.44030;0.04267;,
 0.08644;-0.05158;0.09583;,
 0.03879;-0.34227;-0.30250;,
 -0.00489;-0.44030;0.04267;,
 0.11332;-0.60252;0.01997;,
 0.17490;-0.46424;-0.46692;,
 0.16693;-0.18423;-0.70973;,
 0.17490;-0.46424;-0.46692;,
 0.16124;0.13201;-0.72704;,
 0.16693;-0.18423;-0.70973;,
 0.16452;0.38827;-0.51535;,
 0.16124;0.13201;-0.72704;,
 0.14740;0.50591;-0.07359;,
 0.16452;0.38827;-0.51535;,
 0.10223;0.45686;0.37765;,
 0.14740;0.50591;-0.07359;,
 0.05979;0.24766;0.77148;,
 0.10223;0.45686;0.37765;,
 0.05654;0.01158;0.85117;,
 0.05979;0.24766;0.77148;,
 0.06768;-0.30975;0.78417;,
 0.05654;0.01158;0.85117;,
 0.07411;-0.53507;0.72148;,
 0.06768;-0.30975;0.78417;,
 0.08914;-0.63938;0.55655;,
 0.07411;-0.53507;0.72148;,
 0.11332;-0.60252;0.01997;,
 0.08914;-0.63938;0.55655;;
 
 152;
 4;0,1,2,3;,
 4;4,5,0,3;,
 4;6,7,4,3;,
 4;2,8,6,3;,
 4;9,10,11,12;,
 4;13,14,9,12;,
 4;15,16,13,12;,
 4;11,17,15,12;,
 4;18,16,15,19;,
 4;20,21,18,19;,
 4;15,17,20,19;,
 4;22,23,24,25;,
 4;26,27,22,25;,
 4;28,29,26,25;,
 4;24,21,28,25;,
 4;30,31,32,33;,
 4;2,1,30,33;,
 4;34,8,2,33;,
 4;32,27,34,33;,
 4;35,14,13,36;,
 4;37,38,35,36;,
 4;39,23,37,36;,
 4;13,16,39,36;,
 4;40,5,4,41;,
 4;42,43,40,41;,
 4;4,7,42,41;,
 4;44,38,37,45;,
 4;32,31,44,45;,
 4;22,27,32,45;,
 4;37,23,22,45;,
 4;46,47,48,49;,
 4;50,51,46,49;,
 4;52,53,50,49;,
 4;48,54,52,49;,
 4;55,56,57,58;,
 4;59,60,55,58;,
 4;61,62,59,58;,
 4;57,63,61,58;,
 4;64,65,66,67;,
 4;68,69,64,67;,
 4;70,71,68,67;,
 4;66,72,70,67;,
 4;61,63,73,74;,
 4;75,62,61,74;,
 4;46,51,75,74;,
 4;73,47,46,74;,
 4;76,54,77,78;,
 4;79,80,76,78;,
 4;64,69,79,78;,
 4;77,65,64,78;,
 4;81,60,82,83;,
 4;84,85,81,83;,
 4;44,31,84,83;,
 4;82,38,44,83;,
 4;86,53,87,88;,
 4;89,43,86,88;,
 4;90,91,89,88;,
 4;87,92,90,88;,
 4;59,62,93,94;,
 4;82,60,59,94;,
 4;35,38,82,94;,
 4;93,14,35,94;,
 4;68,71,95,96;,
 4;97,69,68,96;,
 4;30,1,97,96;,
 4;95,31,30,96;,
 4;75,51,98,99;,
 4;93,62,75,99;,
 4;9,14,93,99;,
 4;98,10,9,99;,
 4;79,69,97,100;,
 4;101,80,79,100;,
 4;0,5,101,100;,
 4;97,1,0,100;,
 4;70,72,102,103;,
 4;104,71,70,103;,
 4;102,85,104,103;,
 4;52,54,105,106;,
 4;87,53,52,106;,
 4;107,92,87,106;,
 4;105,108,107,106;,
 4;107,108,109,110;,
 4;111,92,107,110;,
 4;109,112,111,110;,
 4;81,85,102,113;,
 4;55,60,81,113;,
 4;114,56,55,113;,
 4;102,72,114,113;,
 4;84,31,95,115;,
 4;104,85,84,115;,
 4;95,71,104,115;,
 4;116,7,6,117;,
 4;118,29,116,117;,
 4;6,8,118,117;,
 4;26,29,118,119;,
 4;34,27,26,119;,
 4;118,8,34,119;,
 4;20,17,120,121;,
 4;28,21,20,121;,
 4;116,29,28,121;,
 4;120,7,116,121;,
 4;18,21,24,122;,
 4;39,16,18,122;,
 4;24,23,39,122;,
 4;101,5,123,124;,
 4;125,80,101,124;,
 4;126,112,125,124;,
 4;123,127,126,124;,
 4;42,7,120,128;,
 4;129,43,42,128;,
 4;11,10,129,128;,
 4;120,17,11,128;,
 4;86,43,129,130;,
 4;50,53,86,130;,
 4;98,51,50,130;,
 4;129,10,98,130;,
 4;126,127,131,132;,
 4;111,112,126,132;,
 4;90,92,111,132;,
 4;131,91,90,132;,
 4;40,43,89,133;,
 4;123,5,40,133;,
 4;131,127,123,133;,
 4;89,91,131,133;,
 4;76,80,125,134;,
 4;105,54,76,134;,
 4;109,108,105,134;,
 4;125,112,109,134;,
 3;135,136,137;,
 3;138,139,140;,
 3;141,139,142;,
 3;143,144,145;,
 3;146,147,148;,
 3;149,150,151;,
 3;152,153,154;,
 3;155,156,157;,
 3;158,159,160;,
 3;161,162,163;,
 3;164,165,166;,
 3;167,168,169;,
 4;170,169,168,171;,
 4;135,137,172,173;,
 4;138,140,174,175;,
 4;141,142,176,177;,
 4;178,179,143,145;,
 4;146,148,180,181;,
 4;149,151,182,183;,
 4;152,154,184,185;,
 4;186,187,155,157;,
 4;158,160,188,189;,
 4;161,163,190,191;,
 4;164,166,192,193;;
 
 MeshMaterialList {
  1;
  152;
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
  150;
  0.136185;-0.305852;-0.942289;,
  0.160766;-0.516697;0.840939;,
  0.857454;-0.326792;0.397467;,
  0.955144;0.226356;0.190954;,
  0.126959;0.582817;-0.802624;,
  0.127445;0.270390;0.954278;,
  -0.218549;-0.948344;-0.229957;,
  0.238088;0.963418;0.123043;,
  -0.605661;-0.781318;-0.150722;,
  -0.598301;0.103270;0.794589;,
  -0.654469;0.491062;-0.574916;,
  -0.750056;-0.354603;0.558277;,
  -0.804439;-0.057105;-0.591285;,
  -0.060695;0.987109;0.148091;,
  -0.122189;-0.793074;0.596744;,
  -0.066695;0.134930;0.988608;,
  0.162193;0.560108;-0.812387;,
  -0.104190;-0.514262;0.851281;,
  0.010418;-0.313872;-0.949408;,
  -0.373674;0.853575;-0.363012;,
  -0.553051;-0.706953;0.440854;,
  -0.506971;-0.847042;-0.159689;,
  -0.381630;0.909236;0.166277;,
  -0.068140;0.920686;-0.384310;,
  0.853124;-0.331748;-0.402645;,
  0.846812;0.300069;-0.439167;,
  0.904126;-0.368914;0.215542;,
  0.902410;0.078067;0.423747;,
  0.028155;-0.537142;-0.843022;,
  0.046208;-0.991922;0.118132;,
  -0.113679;-0.990575;-0.076407;,
  -0.088840;-0.986288;-0.139083;,
  0.390516;-0.918613;-0.060388;,
  -0.792532;-0.044196;-0.608227;,
  0.062200;-0.110815;0.991893;,
  0.901308;-0.151616;0.405779;,
  0.539460;0.268404;0.798087;,
  0.524876;-0.484802;0.699624;,
  0.407664;0.537078;-0.738483;,
  0.634191;0.755714;0.163396;,
  0.470150;-0.399873;-0.786804;,
  0.528269;-0.820766;0.217426;,
  -0.041305;-0.789904;-0.611838;,
  0.243781;0.769021;0.590912;,
  -0.702217;0.700222;0.128765;,
  -0.845573;-0.511510;-0.152855;,
  -0.870719;0.052675;0.488952;,
  -0.765975;0.498350;-0.406115;,
  -0.923260;-0.238489;0.301187;,
  -0.870941;-0.124103;-0.475458;,
  -0.690040;-0.714692;0.114281;,
  -0.758212;0.194955;-0.622179;,
  -0.555614;0.675364;-0.484950;,
  -0.083582;-0.113311;0.990038;,
  -0.014920;-0.463569;-0.885935;,
  -0.068676;0.738333;0.670931;,
  0.192078;-0.893809;0.405230;,
  0.151769;0.155998;-0.976028;,
  0.164316;0.917405;-0.362448;,
  0.068246;0.989998;0.123476;,
  0.051086;-0.982094;-0.181330;,
  0.017448;0.182506;0.983050;,
  0.183930;0.583500;-0.791011;,
  0.020644;-0.505914;0.862337;,
  0.116821;-0.279940;-0.952883;,
  -0.099836;-0.957792;0.269569;,
  0.123435;0.153508;-0.980408;,
  0.071577;0.789807;-0.609164;,
  -0.661505;-0.104225;0.742663;,
  -0.800054;-0.026381;-0.599347;,
  -0.515044;0.632385;0.578636;,
  -0.449609;-0.218987;-0.865966;,
  -0.307217;-0.505830;0.806073;,
  -0.279516;0.537924;-0.795304;,
  -0.204557;0.113390;0.972265;,
  -0.223663;-0.957577;-0.181716;,
  -0.118954;0.977990;0.171420;,
  -0.134643;-0.982327;0.130022;,
  -0.177431;-0.977174;-0.116833;,
  -0.090163;-0.995916;-0.004771;,
  -0.170152;0.905968;-0.387648;,
  -0.372480;0.922160;-0.104306;,
  -0.050257;0.990022;-0.131648;,
  0.872195;-0.044207;-0.487156;,
  0.917031;-0.398802;0.003199;,
  0.951132;0.308617;0.010184;,
  0.973536;-0.110449;0.200071;,
  0.900674;-0.355653;0.249594;,
  0.956284;0.154657;0.248198;,
  -0.142761;-0.904580;0.401689;,
  -0.123685;-0.870432;0.476497;,
  -0.753509;-0.475375;-0.454140;,
  0.182438;-0.981178;-0.063287;,
  -0.006492;-0.809066;-0.587682;,
  -0.627523;-0.767414;0.131492;,
  -0.127262;-0.989996;-0.060932;,
  -0.342895;-0.290961;-0.893177;,
  0.250926;-0.748813;-0.613446;,
  -0.153074;-0.798757;0.581856;,
  -0.971053;-0.226849;-0.074808;,
  0.169630;-0.863045;0.475793;,
  0.366629;0.069957;-0.927733;,
  0.448264;-0.141083;0.882697;,
  0.638213;0.615040;0.463045;,
  0.565262;-0.726844;0.390098;,
  0.640474;0.766115;-0.053479;,
  0.393812;-0.884971;-0.248471;,
  -0.888395;-0.101588;0.447699;,
  -0.892040;-0.450189;0.039935;,
  -0.923982;-0.293714;-0.244928;,
  -0.834434;0.178140;-0.521523;,
  -0.699382;0.692603;-0.176540;,
  -0.814848;0.435757;0.382282;,
  -0.014503;-0.106525;0.994204;,
  0.069823;-0.699266;-0.711443;,
  0.062524;0.757861;0.649413;,
  0.013907;-0.940273;0.340136;,
  0.193236;0.187575;-0.963055;,
  0.115927;0.920322;-0.373588;,
  -0.234320;-0.948026;0.215268;,
  -0.399365;0.164172;-0.901973;,
  -0.223549;0.719617;-0.657401;,
  -0.247222;-0.123011;0.961119;,
  -0.408386;-0.266565;-0.873020;,
  -0.174343;0.716571;0.675374;,
  -0.059174;-0.995438;0.074848;,
  -0.108865;0.991824;-0.066586;,
  0.992732;-0.096117;0.072421;,
  0.979206;-0.129446;0.156202;,
  0.094974;-0.870260;0.483351;,
  0.175302;-0.841330;-0.511305;,
  -0.292106;-0.670822;-0.681668;,
  -0.198082;-0.969369;0.145217;,
  -0.908640;-0.411830;-0.069068;,
  -0.170138;-0.886848;0.429598;,
  -0.996372;-0.015775;-0.083628;,
  -0.969918;-0.173124;-0.171135;,
  -0.976568;-0.102294;-0.189341;,
  -0.979786;0.047453;-0.194337;,
  -0.972860;0.168992;-0.158068;,
  -0.969325;0.228375;-0.090845;,
  -0.976943;0.213416;-0.006037;,
  -0.991380;0.114201;0.064222;,
  -0.995399;-0.005014;0.095682;,
  -0.993612;-0.055315;0.098359;,
  -0.992680;-0.107787;0.054486;,
  -0.984295;-0.175072;-0.022638;,
  -0.976812;-0.180968;-0.114410;,
  0.149013;0.778562;-0.609620;,
  -0.850044;-0.525740;0.031965;;
  152;
  4;64,117,57,0;,
  4;42,114,64,0;,
  4;40,106,42,0;,
  4;57,101,40,0;,
  4;63,116,56,1;,
  4;34,113,63,1;,
  4;37,102,34,1;,
  4;56,104,37,1;,
  4;35,102,37,2;,
  4;87,128,35,2;,
  4;37,104,87,2;,
  4;39,103,88,3;,
  4;85,105,39,3;,
  4;86,127,85,3;,
  4;88,128,86,3;,
  4;62,118,58,4;,
  4;57,117,62,4;,
  4;38,101,57,4;,
  4;58,148,38,4;,
  4;61,113,34,5;,
  4;43,115,61,5;,
  4;36,103,43,5;,
  4;34,102,36,5;,
  4;60,114,42,6;,
  4;95,125,60,6;,
  4;42,106,95,6;,
  4;59,115,43,7;,
  4;58,118,59,7;,
  4;39,105,58,7;,
  4;43,103,39,7;,
  4;50,108,45,8;,
  4;78,119,50,8;,
  4;94,132,78,8;,
  4;45,109,94,8;,
  4;70,112,46,9;,
  4;74,124,70,9;,
  4;68,122,74,9;,
  4;46,107,68,9;,
  4;51,110,47,10;,
  4;73,120,51,10;,
  4;52,121,73,10;,
  4;47,111,52,10;,
  4;68,107,48,11;,
  4;72,122,68,11;,
  4;50,119,72,11;,
  4;48,108,50,11;,
  4;69,109,49,12;,
  4;71,123,69,12;,
  4;51,120,71,12;,
  4;49,110,51,12;,
  4;76,124,55,13;,
  4;82,126,76,13;,
  4;59,118,82,13;,
  4;55,115,59,13;,
  4;77,132,98,14;,
  4;100,125,77,14;,
  4;90,129,100,14;,
  4;98,134,90,14;,
  4;74,122,53,15;,
  4;55,124,74,15;,
  4;61,115,55,15;,
  4;53,113,61,15;,
  4;73,121,67,16;,
  4;66,120,73,16;,
  4;62,117,66,16;,
  4;67,118,62,16;,
  4;72,119,65,17;,
  4;53,122,72,17;,
  4;63,113,53,17;,
  4;65,116,63,17;,
  4;71,120,66,18;,
  4;54,123,71,18;,
  4;64,114,54,18;,
  4;66,117,64,18;,
  4;52,111,81,19;,
  4;80,121,52,19;,
  4;81,126,80,19;,
  4;94,109,99,20;,
  4;98,132,94,20;,
  4;89,134,98,20;,
  4;99,133,149,20;,
  4;149,133,91,21;,
  4;75,134,89,21;,
  4;91,131,75,21;,
  4;76,126,81,22;,
  4;70,124,76,22;,
  4;44,112,70,22;,
  4;81,111,44,22;,
  4;82,118,67,23;,
  4;80,126,82,23;,
  4;67,121,80,23;,
  4;84,106,40,24;,
  4;83,127,84,24;,
  4;40,101,83,24;,
  4;85,127,83,25;,
  4;38,105,85,25;,
  4;83,101,38,25;,
  4;87,104,41,26;,
  4;86,128,87,26;,
  4;84,127,86,26;,
  4;41,106,84,26;,
  4;35,128,88,27;,
  4;36,102,35,27;,
  4;88,103,36,27;,
  4;54,114,97,28;,
  4;96,123,54,28;,
  4;93,131,96,28;,
  4;97,130,93,28;,
  4;95,106,41,29;,
  4;79,125,95,29;,
  4;56,116,79,29;,
  4;41,104,56,29;,
  4;77,125,79,30;,
  4;78,132,77,30;,
  4;65,119,78,30;,
  4;79,116,65,30;,
  4;93,130,92,31;,
  4;75,131,93,31;,
  4;90,134,75,31;,
  4;92,129,90,31;,
  4;60,125,100,32;,
  4;97,114,60,32;,
  4;92,130,97,32;,
  4;100,129,92,32;,
  4;69,123,96,33;,
  4;99,109,69,33;,
  4;91,133,99,33;,
  4;96,131,91,33;,
  3;136,135,137;,
  3;137,135,138;,
  3;138,135,139;,
  3;139,135,140;,
  3;140,135,141;,
  3;141,135,142;,
  3;142,135,143;,
  3;143,135,144;,
  3;144,135,145;,
  3;145,135,146;,
  3;146,135,147;,
  3;135,136,147;,
  4;45,147,136,109;,
  4;136,137,49,109;,
  4;137,138,110,49;,
  4;138,139,47,110;,
  4;111,47,139,140;,
  4;140,141,44,111;,
  4;141,142,112,44;,
  4;142,143,46,112;,
  4;107,46,143,144;,
  4;144,145,48,107;,
  4;145,146,108,48;,
  4;146,147,45,108;;
 }
 MeshTextureCoords {
  194;
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
  0.135420;0.875000;,
  0.125000;1.000000;,
  0.114580;0.875000;,
  0.510420;0.875000;,
  0.958330;1.000000;,
  0.489580;0.875000;,
  0.968750;0.875000;,
  0.947920;0.875000;,
  0.885420;0.875000;,
  0.875000;1.000000;,
  0.864580;0.875000;,
  0.802080;0.875000;,
  0.791670;1.000000;,
  0.781250;0.875000;,
  0.718750;0.875000;,
  0.708330;1.000000;,
  0.697920;0.875000;,
  0.635420;0.875000;,
  0.625000;1.000000;,
  0.614580;0.875000;,
  0.552080;0.875000;,
  0.541670;1.000000;,
  0.531250;0.875000;,
  0.468750;0.875000;,
  0.458330;1.000000;,
  0.447920;0.875000;,
  0.385420;0.875000;,
  0.375000;1.000000;,
  0.364580;0.875000;,
  0.302080;0.875000;,
  0.291670;1.000000;,
  0.281250;0.875000;,
  0.208330;1.000000;,
  0.197920;0.875000;,
  0.218750;0.875000;,
  0.229170;0.750000;,
  0.187500;0.750000;,
  0.104170;0.750000;,
  0.145830;0.750000;,
  0.020830;0.750000;,
  0.062500;0.750000;,
  0.937500;0.750000;,
  0.979170;0.750000;,
  0.854170;0.750000;,
  0.895830;0.750000;,
  0.770830;0.750000;,
  0.812500;0.750000;,
  0.687500;0.750000;,
  0.729170;0.750000;,
  0.604170;0.750000;,
  0.645830;0.750000;,
  0.520830;0.750000;,
  0.562500;0.750000;,
  0.437500;0.750000;,
  0.479170;0.750000;,
  0.354170;0.750000;,
  0.395830;0.750000;,
  0.270830;0.750000;,
  0.312500;0.750000;;
 }
}
