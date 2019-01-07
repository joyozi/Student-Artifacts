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
 74;
 5.57500;3.81328;-12.20000;,
 5.57500;3.81328;12.20000;,
 0.00000;-5.46700;12.20000;,
 0.00000;-5.46700;-12.20000;,
 -5.57500;3.81328;12.20000;,
 -5.57500;3.81328;-12.20000;,
 0.00000;-5.46700;-12.20000;,
 0.00000;-5.46700;12.20000;,
 5.57500;3.81328;-12.20000;,
 -5.57500;3.81328;-12.20000;,
 -5.57500;3.81328;-12.20000;,
 5.57500;3.81328;-12.20000;,
 5.57500;3.81328;12.20000;,
 -5.57500;3.81328;12.20000;,
 8.31909;6.52665;-15.48000;,
 11.04146;3.80429;-15.48000;,
 8.31909;1.08193;-15.48000;,
 5.59673;3.80429;-15.48000;,
 11.04146;3.80429;-15.48000;,
 11.04146;3.80429;15.48000;,
 8.31909;1.08193;15.48000;,
 8.31909;1.08193;-15.48000;,
 11.04146;3.80429;15.48000;,
 8.31909;6.52665;15.48000;,
 5.59673;3.80429;15.48000;,
 8.31909;1.08193;15.48000;,
 8.31909;6.52665;15.48000;,
 8.31909;6.52665;-15.48000;,
 5.59673;3.80429;-15.48000;,
 5.59673;3.80429;15.48000;,
 11.04146;3.80429;-15.48000;,
 8.31909;6.52665;-15.48000;,
 5.59673;3.80429;-15.48000;,
 8.31909;1.08193;-15.48000;,
 -8.31909;6.52665;-15.48000;,
 -5.59673;3.80429;-15.48000;,
 -8.31909;1.08193;-15.48000;,
 -11.04146;3.80429;-15.48000;,
 -11.04146;3.80429;-15.48000;,
 -8.31909;1.08193;-15.48000;,
 -8.31909;1.08193;15.48000;,
 -11.04146;3.80429;15.48000;,
 -11.04146;3.80429;15.48000;,
 -8.31909;1.08193;15.48000;,
 -5.59673;3.80429;15.48000;,
 -8.31909;6.52665;15.48000;,
 -8.31909;6.52665;15.48000;,
 -5.59673;3.80429;15.48000;,
 -5.59673;3.80429;-15.48000;,
 -8.31909;6.52665;-15.48000;,
 -8.31909;6.52665;-15.48000;,
 -11.04146;3.80429;-15.48000;,
 -5.59673;3.80429;-15.48000;,
 -8.31909;1.08193;-15.48000;,
 0.00000;-5.48901;-15.48000;,
 2.72236;-8.21138;-15.48000;,
 0.00000;-10.93374;-15.48000;,
 -2.72236;-8.21138;-15.48000;,
 2.72236;-8.21138;-15.48000;,
 2.72236;-8.21138;15.48000;,
 0.00000;-10.93374;15.48000;,
 0.00000;-10.93374;-15.48000;,
 2.72236;-8.21138;15.48000;,
 0.00000;-5.48901;15.48000;,
 -2.72236;-8.21138;15.48000;,
 0.00000;-10.93374;15.48000;,
 0.00000;-5.48901;15.48000;,
 0.00000;-5.48901;-15.48000;,
 -2.72236;-8.21138;-15.48000;,
 -2.72236;-8.21138;15.48000;,
 2.72236;-8.21138;-15.48000;,
 0.00000;-5.48901;-15.48000;,
 -2.72236;-8.21138;-15.48000;,
 0.00000;-10.93374;-15.48000;;
 
 23;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;4,1,8,9;,
 3;10,11,6;,
 3;12,13,2;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;26,19,30,31;,
 4;32,33,20,29;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;46,50,51,41;,
 4;52,47,40,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;66,59,70,71;,
 4;72,73,60,69;;
 
 MeshMaterialList {
  2;
  23;
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
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   33.330002;
   0.310000;0.310000;0.310000;;
   0.295455;0.295455;0.295455;;
  }
  Material {
   0.909804;1.000000;0.274510;1.000000;;
   72.730003;
   0.390000;0.390000;0.390000;;
   0.609569;0.670000;0.183922;;
  }
 }
 MeshNormals {
  19;
  -0.857214;-0.514960;0.000000;,
  0.857214;-0.514960;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.707106;-0.707108;-0.000000;,
  0.000000;0.000000;1.000000;,
  -0.707106;-0.707108;0.000000;,
  0.707107;-0.707107;-0.000000;,
  -0.707107;0.707107;0.000000;,
  0.707106;0.707108;0.000000;,
  -0.707107;-0.707107;0.000000;,
  0.707107;0.707107;0.000000;,
  -0.707106;0.707108;0.000000;,
  0.707107;-0.707107;-0.000000;,
  -0.707108;0.707105;0.000000;,
  0.707108;0.707105;0.000000;,
  -0.707107;-0.707107;0.000000;;
  23;
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  3;3,3,3;,
  3;4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;5,5,5,5;,
  4;8,8,8,8;,
  4;7,7,7,7;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;5,5,5,5;,
  4;9,9,9,9;,
  4;7,7,7,7;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;;
 }
 MeshTextureCoords {
  74;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
