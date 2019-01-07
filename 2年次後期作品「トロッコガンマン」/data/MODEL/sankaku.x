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
 11;
 0.00000;0.00000;-83.09600;,
 0.00000;108.63000;0.00000;,
 71.96325;0.00000;41.54800;,
 0.00000;108.63000;0.00000;,
 -71.96325;0.00000;41.54799;,
 0.00000;108.63000;0.00000;,
 0.00000;0.00000;-83.09600;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;-83.09600;,
 71.96325;0.00000;41.54800;,
 -71.96325;0.00000;41.54799;;
 
 6;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;7,8,9;,
 3;7,9,10;,
 3;7,10,8;;
 
 MeshMaterialList {
  1;
  6;
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.000000;1.000000;;
   35.000000;
   0.680000;0.680000;0.680000;;
   0.740000;0.740000;0.000000;;
   TextureFilename {
    "C:\\Users\\touma.yoshihiro\\Documents\\DX22\\20150213_sample_01\\data\\TEXTURE\\question000.jpg";
   }
  }
 }
 MeshNormals {
  4;
  0.808880;0.357235;-0.467007;,
  -0.000000;0.357235;0.934014;,
  0.000000;-1.000000;-0.000000;,
  -0.808880;0.357235;-0.467007;;
  6;
  3;0,0,0;,
  3;1,1,1;,
  3;3,3,3;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;;
 }
 MeshTextureCoords {
  11;
  0.000000;1.000000;,
  0.166667;0.000000;,
  0.333333;1.000000;,
  0.333333;0.000000;,
  0.666667;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
