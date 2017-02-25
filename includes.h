#ifndef INCLUDES_H
#define INCLUDES_H
//------------------------------------------------------------------------------
// includes.h
// 20040110 dan royer
//
// This code is released under the LGPL (http://creativecommons.org/licenses/LGPL/2.1/)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// pragmas + platform specific stuff
//------------------------------------------------------------------------------
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#pragma warning( disable : 4786 )  // truncate warnings to 255 characters
#pragma warning( disable : 4503 )  // decorated name length exceeded
#define _CRT_SECURE_NO_WARNING
#endif
#ifndef WIN32
#define stricmp strcasecmp
#endif

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <list>
#include <string>
#include <map>
#ifdef WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#endif
using namespace std;

//#define TIXML_USE_STL
//#include "tinyxml/tinyxml.h"


//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
#define PI           (3.142592653f)
#define TWOPI        (PI*2.0f)
#define DEG2RAD      (PI/180.0f)
#define RAD2DEG      (180.0f/PI)
#define WHITESPACE   " \t\r\n"
#define LOGFILE      "gamelog.txt"

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------
//#ifdef _DEBUG

#define Log1(x) { \
  FILE*fout; \
  fopen_s(&fout,LOGFILE,"at"); \
  if(fout) { \
    fprintf(fout,"%s (%d): %s",__FILE__,__LINE__,(x)); \
    fclose(fout); \
  } \
}


#define Log2(x,y) { \
  FILE*fout; \
  fopen_s(&fout,LOGFILE,"at"); \
  if(fout) { \
    fprintf(fout,"%s (%d): ",__FILE__,__LINE__); \
    fprintf(fout,(x),(y)); \
    fclose(fout); \
  } \
}


#define Log3(x,y,z) { \
  FILE*fout; \
  fopen_s(&fout,LOGFILE,"at"); \
  if(fout) { \
    fprintf(fout,"%s (%d): ",__FILE__,__LINE__); \
    fprintf(fout,(x),(y),(z)); \
    fclose(fout); \
  } \
}


#define LogAppend1(x) { \
  FILE*fout; \
  fopen_s(&fout,LOGFILE,"at"); \
  if(fout) { \
    fprintf(fout,(x)); \
    fclose(fout); \
  } \
}


#define LogAppend2(x,y) { \
  FILE*fout; \
  fopen_s(&fout,LOGFILE,"at"); \
  if(fout) { \
    fprintf(fout,(x),(y)); \
    fclose(fout); \
  } \
}
/*
#else

#define Log1(x)
#define Log2(x,y)
#define LogAppend1(x)
#define LogAppend2(x,y)

#endif
//*/

#define Error1(x) { \
  FILE*fout; \
  fopen_s(&fout,LOGFILE,"at"); \
  if(fout) { \
    fprintf(fout,"**ERROR**\n%s (%d):\n%s",__FILE__,__LINE__,(x)); \
    fclose(fout); \
  } \
  assert(0); \
  exit(1); \
}


#define Error2(x,y) { \
  FILE*fout; \
  fopen_s(&fout,LOGFILE,"at"); \
  if(fout) { \
    fprintf(fout,"**ERROR**\n%s (%d):\n",__FILE__,__LINE__); \
    fprintf(fout,(x),(y)); \
    fclose(fout); \
  } \
  assert(0); \
  exit(1); \
}


#define Error3(x,y,z) { \
  FILE*fout; \
  fopen_s(&fout,LOGFILE,"at"); \
  if(fout) { \
    fprintf(fout,"**ERROR**\n%s (%d):\n",__FILE__,__LINE__); \
    fprintf(fout,(x),(y),(z)); \
    fclose(fout); \
  } \
  assert(0); \
  exit(1); \
}


#ifndef ASSERT
#define ASSERT(x) { if(!(x)) Error1(#x); }
#endif


//------------------------------------------------------------------------------
#endif  // INCLUDES_H
