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
 18;
 0.00000;-4.57994;1.51693;,
 1.31636;-4.57994;-0.76307;,
 1.31636;-3.80475;-0.76307;,
 0.00000;-3.80475;1.51693;,
 -1.31636;-4.57994;-0.76307;,
 -1.31636;-3.80475;-0.76307;,
 0.00000;-4.57994;1.51693;,
 0.00000;-3.80475;1.51693;,
 1.30981;0.61376;-0.75740;,
 0.00000;0.61376;1.51126;,
 -1.30981;0.61376;-0.75740;,
 0.00000;0.61376;1.51126;,
 0.00000;-4.57994;-0.00307;,
 0.00000;-4.57994;-0.00307;,
 0.00000;-4.57994;-0.00307;,
 0.00000;4.57994;0.04933;,
 0.00000;4.57994;0.04933;,
 0.00000;4.57994;0.04933;;
 
 12;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 3;12,1,0;,
 3;13,4,1;,
 3;14,6,4;,
 3;15,9,8;,
 3;16,8,10;,
 3;17,10,11;;
 
 MeshMaterialList {
  2;
  12;
  0,
  0,
  0,
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  1;;
  Material {
   0.800000;0.000000;0.028235;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.398431;0.740392;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  13;
  0.000000;-1.000000;-0.000000;,
  0.866025;0.000000;0.500000;,
  -0.000000;0.000000;-1.000000;,
  0.866025;0.000321;0.500000;,
  -0.000000;0.000642;-1.000000;,
  0.862407;0.091321;0.497911;,
  -0.000000;0.100802;-0.994906;,
  0.851682;0.181248;0.491719;,
  -0.866025;0.000000;0.500000;,
  -0.866025;0.000321;0.500000;,
  -0.862407;0.091321;0.497911;,
  -0.000000;0.199320;-0.979934;,
  -0.851682;0.181248;0.491719;;
  12;
  4;1,1,3,3;,
  4;2,2,4,4;,
  4;8,8,9,9;,
  4;3,3,5,5;,
  4;4,4,6,6;,
  4;9,9,10,10;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;7,5,5;,
  3;11,6,6;,
  3;12,10,10;;
 }
 MeshTextureCoords {
  18;
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.333333;0.500000;,
  0.000000;0.500000;,
  0.666667;0.000000;,
  0.666667;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.166667;0.000000;,
  0.500000;0.000000;,
  0.833333;0.000000;,
  0.166667;1.000000;,
  0.500000;1.000000;,
  0.833333;1.000000;;
 }
}
