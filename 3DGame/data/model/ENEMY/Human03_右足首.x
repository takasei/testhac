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
 126;
 0.00000;-0.58346;2.85384;,
 0.00000;-0.58346;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;2.85384;,
 -5.67601;-0.58346;-0.00000;,
 -5.67601;-0.58346;2.85384;,
 -5.67601;0.00000;2.85384;,
 -5.67601;0.00000;0.00000;,
 0.00000;-0.58346;-0.88368;,
 0.00000;0.00000;-0.88368;,
 0.00000;-0.58346;3.73752;,
 0.00000;0.00000;3.73752;,
 -5.67601;-0.58346;-0.88368;,
 -5.67601;0.00000;-0.88368;,
 -5.67601;-0.58346;3.73752;,
 -5.67601;0.00000;3.73752;,
 0.00000;-0.58346;-1.84769;,
 0.00000;0.00000;-1.84769;,
 0.00000;-0.58346;4.70153;,
 0.00000;0.00000;4.70153;,
 -4.51118;-0.58346;-1.84769;,
 -5.67601;-0.58346;-1.84769;,
 -5.67601;0.00000;-1.84769;,
 -4.51118;0.00000;-1.84769;,
 -5.67601;-0.58346;4.70153;,
 -4.51118;-0.58346;4.70153;,
 -4.51118;0.00000;4.70153;,
 -5.67601;0.00000;4.70153;,
 0.00000;-0.58346;-2.95229;,
 0.00000;0.00000;-2.95229;,
 -3.38652;-0.58346;5.80613;,
 0.00000;-0.58346;5.80613;,
 0.00000;0.00000;5.80613;,
 -3.38652;0.00000;5.80613;,
 -3.38652;-0.58346;-2.95229;,
 -4.51118;-0.58346;-2.95229;,
 -4.51118;0.00000;-2.95229;,
 -3.38652;0.00000;-2.95229;,
 -4.51118;-0.58346;5.80613;,
 -4.51118;0.00000;5.80613;,
 0.00000;-1.96536;2.85384;,
 0.00000;-1.96536;0.00000;,
 0.00000;-1.96536;-0.88368;,
 0.00000;-1.96536;3.73752;,
 -5.67601;-1.96536;2.85384;,
 -5.67601;-1.96536;3.73752;,
 0.00000;-1.96536;-1.84769;,
 0.00000;-1.96536;4.70153;,
 -5.67601;-1.96536;-1.84769;,
 -5.67601;-1.96536;-0.88368;,
 -5.67601;-1.96536;4.70153;,
 -4.51118;-1.96536;4.70153;,
 0.00000;-1.96536;-2.95229;,
 -3.38652;-1.96536;5.80613;,
 0.00000;-1.96536;5.80613;,
 -4.51118;-1.96536;-2.95229;,
 -4.51118;-1.96536;-1.84769;,
 -4.51118;-1.96536;5.80613;,
 0.00000;-2.54883;2.85384;,
 0.00000;-2.54883;0.00000;,
 -3.38652;-2.54883;2.85384;,
 -3.38652;-2.54883;-0.00000;,
 -4.51118;-2.54883;2.85384;,
 -4.51118;-2.54883;-0.00000;,
 -5.67601;-2.54883;2.85384;,
 -5.67601;-2.54883;-0.00000;,
 0.00000;-2.54883;-0.88368;,
 -3.38652;-2.54883;-0.88368;,
 0.00000;-2.54883;3.73752;,
 -3.38652;-2.54883;3.73752;,
 -4.51118;-2.54883;-0.88368;,
 -4.51118;-2.54883;3.73752;,
 -5.67601;-2.54883;-0.88368;,
 -5.67601;-2.54883;3.73752;,
 0.00000;-2.54883;-1.84769;,
 -3.38652;-2.54883;-1.84769;,
 0.00000;-2.54883;4.70153;,
 -3.38652;-2.54883;4.70153;,
 -4.51118;-2.54883;-1.84769;,
 -4.51118;-2.54883;4.70153;,
 -5.67601;-2.54883;-1.84769;,
 -5.67601;-2.54883;4.70153;,
 0.00000;-2.54883;-2.95229;,
 -3.38652;-2.54883;-2.95229;,
 -3.38652;-2.54883;5.80613;,
 0.00000;-2.54883;5.80613;,
 -4.51118;-2.54883;-2.95229;,
 -4.51118;-2.54883;5.80613;,
 -5.67601;-2.54883;-5.00271;,
 -4.51118;-2.54883;-5.00271;,
 -5.67601;-1.96536;-5.00271;,
 -4.51118;-1.96536;-5.00271;,
 -3.38652;-2.54883;-5.00980;,
 0.00000;-2.54883;-5.00980;,
 0.00000;-1.96536;-5.00980;,
 -3.38652;-1.96536;-5.00980;,
 -3.38652;-1.96536;-2.95229;,
 -4.51118;-2.54883;-5.00980;,
 -4.51118;-1.96536;-5.00980;,
 -5.67601;-1.96536;-4.00918;,
 -4.51118;-1.96536;-4.00918;,
 -5.67601;-0.58346;-4.00918;,
 -4.51118;-0.58346;-4.00918;,
 -3.38652;-1.96536;-4.00792;,
 0.00000;-1.96536;-4.00792;,
 0.00000;-0.58346;-4.00792;,
 -3.38652;-0.58346;-4.00792;,
 -4.51118;-1.96536;-4.00792;,
 -4.51118;-0.58346;-4.00792;,
 -3.38652;-0.58346;-3.65860;,
 0.00000;-0.58346;-3.65860;,
 -3.38652;0.00000;-3.65860;,
 0.00000;0.00000;-3.65860;,
 -5.70044;-0.58346;2.85384;,
 -5.70044;-1.96536;2.85384;,
 -5.70044;-0.58346;-0.00000;,
 -5.70044;-1.96536;-0.00000;,
 -5.70044;-0.58346;-0.88368;,
 -5.70044;-1.96536;-0.88368;,
 -5.70044;-2.54883;2.85384;,
 -5.70044;-2.54883;-0.00000;,
 -5.70044;-2.54883;-0.88368;,
 -5.70044;-2.54883;3.73752;,
 -5.70044;-1.96536;3.73752;,
 -5.70044;-2.54883;-1.84769;,
 -5.70044;-1.96536;-1.84769;;
 
 115;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;1,8,9,2;,
 4;10,0,3,11;,
 4;12,4,7,13;,
 4;5,14,15,6;,
 4;8,16,17,9;,
 4;18,10,11,19;,
 4;20,21,22,23;,
 4;21,12,13,22;,
 4;24,25,26,27;,
 4;14,24,27,15;,
 4;16,28,29,17;,
 4;30,31,32,33;,
 4;31,18,19,32;,
 4;34,35,36,37;,
 4;35,20,23,36;,
 4;38,30,33,39;,
 4;25,38,39,26;,
 4;40,41,1,0;,
 4;41,42,8,1;,
 4;43,40,0,10;,
 4;44,45,14,5;,
 4;42,46,16,8;,
 4;47,43,10,18;,
 4;48,49,12,21;,
 4;50,51,25,24;,
 4;45,50,24,14;,
 4;46,52,28,16;,
 4;53,54,31,30;,
 4;54,47,18,31;,
 4;55,56,20,35;,
 4;57,53,30,38;,
 4;51,57,38,25;,
 4;58,59,41,40;,
 4;60,61,59,58;,
 4;62,63,61,60;,
 4;64,65,63,62;,
 4;59,66,42,41;,
 4;67,66,59,61;,
 4;68,58,40,43;,
 4;68,69,60,58;,
 4;70,67,61,63;,
 4;69,71,62,60;,
 4;72,70,63,65;,
 4;71,73,64,62;,
 4;66,74,46,42;,
 4;75,74,66,67;,
 4;76,68,43,47;,
 4;76,77,69,68;,
 4;78,75,67,70;,
 4;77,79,71,69;,
 4;80,78,70,72;,
 4;81,79,51,50;,
 4;73,81,50,45;,
 4;79,81,73,71;,
 4;74,82,52,46;,
 4;83,82,74,75;,
 4;84,85,54,53;,
 4;85,76,47,54;,
 4;85,84,77,76;,
 4;86,78,56,55;,
 4;86,83,75,78;,
 4;87,84,53,57;,
 4;79,87,57,51;,
 4;84,87,79,77;,
 4;88,89,78,80;,
 4;90,88,80,48;,
 4;91,90,48,56;,
 4;89,91,56,78;,
 4;89,88,90,91;,
 4;92,93,82,83;,
 4;94,95,96,52;,
 4;93,94,52,82;,
 4;93,92,95,94;,
 4;97,92,83,86;,
 4;98,97,86,55;,
 4;95,98,55,96;,
 4;92,97,98,95;,
 4;99,100,56,48;,
 4;101,99,48,21;,
 4;102,101,21,20;,
 4;100,102,20,56;,
 4;100,99,101,102;,
 4;103,104,52,96;,
 4;105,106,34,28;,
 4;104,105,28,52;,
 4;104,103,106,105;,
 4;107,103,96,55;,
 4;108,107,55,35;,
 4;106,108,35,34;,
 4;103,107,108,106;,
 4;109,110,28,34;,
 4;111,109,34,37;,
 4;112,111,37,29;,
 4;110,112,29,28;,
 4;110,109,111,112;,
 4;113,114,44,5;,
 4;115,113,5,4;,
 4;116,114,113,115;,
 4;117,115,4,12;,
 4;118,117,12,49;,
 4;118,116,115,117;,
 4;119,120,65,64;,
 4;120,119,114,116;,
 4;120,121,72,65;,
 4;121,120,116,118;,
 4;122,119,64,73;,
 4;123,122,73,45;,
 4;114,123,45,44;,
 4;119,122,123,114;,
 4;121,124,80,72;,
 4;125,118,49,48;,
 4;124,125,48,80;,
 4;124,121,118,125;;
 
 MeshMaterialList {
  6;
  115;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  5,
  0,
  0,
  0,
  0,
  0,
  0,
  5,
  5,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  5,
  0,
  0,
  5,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.056800;0.056800;0.056800;1.000000;;
   17.000000;
   0.120000;0.120000;0.120000;;
   0.006390;0.006390;0.006390;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   18.000000;
   0.160000;0.160000;0.160000;;
   0.160000;0.160000;0.160000;;
  }
  Material {
   0.800000;0.793600;0.000000;1.000000;;
   11.000000;
   0.100000;0.100000;0.100000;;
   0.100000;0.099200;0.000000;;
  }
  Material {
   0.351200;0.310400;0.000000;1.000000;;
   13.000000;
   0.090000;0.090000;0.090000;;
   0.065850;0.058200;0.000000;;
  }
  Material {
   0.800000;0.708800;0.442400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.367200;0.367200;0.367200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  6;
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  115;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;;
 }
 MeshTextureCoords {
  126;
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;;
 }
}
