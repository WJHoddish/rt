// force (functions) inline

#ifdef _MSC_VER_
#define force_inline __forceinline
#else
#ifdef __GNUC__
#define force_inline __inline__ __attribute__((always_inline))
#else
#define force_inline
#endif
#endif