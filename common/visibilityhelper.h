/*
 * visibilityhelper.h
 *
 *  Created on: 5-nov.-2013
 *      Author: vincent
 */


// source found at: http://gcc.gnu.org/wiki/Visibility

#ifndef VISIBILITYHELPER_H_
#define VISIBILITYHELPER_H_


// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define WLAN_HELPER_DLL_IMPORT __declspec(dllimport)
  #define WLAN_HELPER_DLL_EXPORT __declspec(dllexport)
  #define WLAN_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define WLAN_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define WLAN_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define WLAN_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define WLAN_HELPER_DLL_IMPORT
    #define WLAN_HELPER_DLL_EXPORT
    #define WLAN_HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define WLAN_API and WLAN_LOCAL.
// WLAN_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// WLAN_LOCAL is used for non-api symbols.

#ifdef WLAN_DLL // defined if WLAN is compiled as a DLL
  #ifdef WLAN_DLL_EXPORTS // defined if we are building the WLAN DLL (instead of using it)
    #define WLAN_API WLAN_HELPER_DLL_EXPORT
  #else
    #define WLAN_API WLAN_HELPER_DLL_IMPORT
  #endif // WLAN_DLL_EXPORTS
  #define WLAN_LOCAL WLAN_HELPER_DLL_LOCAL
#else // WLAN_DLL is not defined: this means WLAN is a static lib.
  #define WLAN_API
  #define WLAN_LOCAL
#endif // WLAN_DLL

#endif /* VISIBILITYHELPER_H_ */
