/*
 * Summary: macros for marking symbols as exportable/importable.
 * Description: macros for marking symbols as exportable/importable.
 *
 * Copy: See Copyright for the status of this software.
 *
 * Author: Igor Zlatovic <igor@zlatkovic.com>
 */

#ifndef __XMLBUS_EXPORTS_H__
#define __XMLBUS_EXPORTS_H__

/**
 * XMLBUSPUBFUN, XMLBUSPUBVAR, XMLBUSCALL
 *
 * Macros which declare an exportable function, an exportable variable and
 * the calling convention used for functions.
 *
 * Please use an extra block for every platform/compiler combination when
 * modifying this, rather than overlong #ifdef lines. This helps
 * readability as well as the fact that different compilers on the same
 * platform might need different definitions.
 */

/**
 * XMLBUSPUBFUN:
 *
 * Macros which declare an exportable function
 */
#define XMLBUSPUBFUN
/**
 * XMLBUSPUBVAR:
 *
 * Macros which declare an exportable variable
 */
#define XMLBUSPUBVAR extern
/**
 * XMLBUSCALL:
 *
 * Macros which declare the called convention for exported functions
 */
#define XMLBUSCALL
/**
 * XMLBUSCDECL:
 *
 * Macro which declares the calling convention for exported functions that 
 * use '...'.
 */
#define XMLBUSCDECL

/** DOC_DISABLE */

/* Windows platform with MS compiler */
#if defined(_WIN32) && defined(_MSC_VER)
  #undef XMLBUSPUBFUN
  #undef XMLBUSPUBVAR
  #undef XMLBUSCALL
  #undef XMLBUSCDECL
  #if defined(IN_XMLBUS) && !defined(XMLBUS_STATIC)
    #define XMLBUSPUBFUN __declspec(dllexport)
    #define XMLBUSPUBVAR __declspec(dllexport)
  #else
    #define XMLBUSPUBFUN
    #if !defined(XMLBUS_STATIC)
      #define XMLBUSPUBVAR __declspec(dllimport) extern
    #else
      #define XMLBUSPUBVAR extern
    #endif
  #endif
  #if defined(XMLBUS_FASTCALL)
    #define XMLBUSCALL __fastcall
  #else
    #define XMLBUSCALL __cdecl
  #endif
  #define XMLBUSCDECL __cdecl
  #if !defined _REENTRANT
    #define _REENTRANT
  #endif
#endif

/* Windows platform with Borland compiler */
#if defined(_WIN32) && defined(__BORLANDC__)
  #undef XMLBUSPUBFUN
  #undef XMLBUSPUBVAR
  #undef XMLBUSCALL
  #undef XMLBUSCDECL
  #if defined(IN_XMLBUS) && !defined(XMLBUS_STATIC)
    #define XMLBUSPUBFUN __declspec(dllexport)
    #define XMLBUSPUBVAR __declspec(dllexport) extern
  #else
    #define XMLBUSPUBFUN
    #if !defined(XMLBUS_STATIC)
      #define XMLBUSPUBVAR __declspec(dllimport) extern
    #else
      #define XMLBUSPUBVAR extern
    #endif
  #endif
  #define XMLBUSCALL __cdecl
  #define XMLBUSCDECL __cdecl
  #if !defined _REENTRANT
    #define _REENTRANT
  #endif
#endif

/* Windows platform with GNU compiler (Mingw) */
#if defined(_WIN32) && defined(__MINGW32__)
  #undef XMLBUSPUBFUN
  #undef XMLBUSPUBVAR
  #undef XMLBUSCALL
  #undef XMLBUSCDECL
  #if defined(IN_XMLBUS) && !defined(XMLBUS_STATIC)
    #define XMLBUSPUBFUN __declspec(dllexport)
    #define XMLBUSPUBVAR __declspec(dllexport)
  #else
    #define XMLBUSPUBFUN
    #if !defined(XMLBUS_STATIC)
      #define XMLBUSPUBVAR __declspec(dllimport) extern
    #else
      #define XMLBUSPUBVAR extern
    #endif
  #endif
  #define XMLBUSCALL __cdecl
  #define XMLBUSCDECL __cdecl
  #if !defined _REENTRANT
    #define _REENTRANT
  #endif
#endif

/* Cygwin platform, GNU compiler */
#if defined(_WIN32) && defined(__CYGWIN__)
  #undef XMLBUSPUBFUN
  #undef XMLBUSPUBVAR
  #undef XMLBUSCALL
  #undef XMLBUSCDECL
  #if defined(IN_XMLBUS) && !defined(XMLBUS_STATIC)
    #define XMLBUSPUBFUN __declspec(dllexport)
    #define XMLBUSPUBVAR __declspec(dllexport)
  #else
    #define XMLBUSPUBFUN
    #if !defined(XMLBUS_STATIC)
      #define XMLBUSPUBVAR __declspec(dllimport) extern
    #else
      #define XMLBUSPUBVAR
    #endif
  #endif
  #define XMLBUSCALL __cdecl
  #define XMLBUSCDECL __cdecl
#endif

/* Compatibility */
#if !defined(XMLBUS_DLL_IMPORT)
#define XMLBUS_DLL_IMPORT XMLBUSPUBVAR
#endif

#endif /* __XMLBUS_EXPORTS_H__ */


