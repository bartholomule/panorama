/*
   Bilinear interpolation code.

   Currently excepts a 256x256 texture, but this restriction should be 
   easy to get rid of.

   - Jon Frydensbjerg
*/

typedef unsigned char byte;

inline int getOffset(int iu, int iv) {
  return ((iv % 128) * 128 * 3 + (iu % 128) * 3);
}

// Bilinear interpolate texture u/v-values using the texture map and
// write the resulting pixel to the corresponding RGB-pointers.
void lerpTexel(byte *texturemap, float ut, float vt, float *r, float *g, float *b) {
  int iu, iv, offset;
  float red, green, blue;
  float uv, iuv, uiv, iuiv;
  float tmu, tmv;
  double integralu, integralv;
  double fracu, fracv;

  tmu = ut * 128.0; // texture width  / 2
  tmv = vt * 128.0; // texture height / 2

  fracu = modf(tmu, &integralu);
  fracv = modf(tmv, &integralv);

  uv   = fracu * fracv;
  iuv  = (1.0 - fracu) * fracv;
  uiv  = fracu * (1.0 - fracv);
  iuiv = (1.0 - fracu) * (1.0 - fracv);

  // values in u and v

  iu = (int) integralu;
  iv = (int) integralv;

  offset = getOffset(iu, iv);

  red   = iuiv * ((float) texturemap[offset + 0]);
  green = iuiv * ((float) texturemap[offset + 1]);
  blue  = iuiv * ((float) texturemap[offset + 2]);

  offset = getOffset(iu+1, iv);

  red   += uiv * ((float) texturemap[offset + 0]);
  green += uiv * ((float) texturemap[offset + 1]);
  blue  += uiv * ((float) texturemap[offset + 2]);

  offset = getOffset(iu, iv+1);

  red   += iuv * ((float) texturemap[offset + 0]);
  green += iuv * ((float) texturemap[offset + 1]);
  blue  += iuv * ((float) texturemap[offset + 2]);

  offset = getOffset(iu+1, iv+1);

  red   += uv * ((float) texturemap[offset + 0]);
  green += uv * ((float) texturemap[offset + 1]);
  blue  += uv * ((float) texturemap[offset + 2]);

  *r += red;
  *g += green;
  *b += blue;
}





