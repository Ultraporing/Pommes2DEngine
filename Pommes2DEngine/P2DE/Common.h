#pragma once

#ifdef LIB_P2DE_DYNAMIC
#define P2DE_DECLSPEC __declspec (dllexport)
#else
#define P2DE_DECLSPEC __declspec (dllimport)
#endif
