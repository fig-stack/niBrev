#ifndef NIBREV_H
#define NIBREV_H

#include <ctype.h>
#include <errno.h>
#include <mach-o/loader.h>
#include <mach/machine.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define base 0x10000000
#define BUFFER_SIZE 4
#define ERROR(msg)                                                             \
  fprintf(stderr, "ERROR: %s | %s\n", msg,                \
          strerror(errno));

typedef struct {
  uint32_t cmd;
  const char *name;
} LoadCommandEntry;

static const LoadCommandEntry loadCommandTable[] = {
    {LC_SYMTAB, "LC_SYMTAB"},
    {LC_DYSYMTAB, "LC_DYSYMTAB"},
    {LC_LOAD_DYLIB, "LC_LOAD_DYLIB"},
    {LC_LOAD_DYLINKER, "LC_LOAD_DYLINKER"},
    {LC_PREBOUND_DYLIB, "LC_PREBOUND_DYLIB"},
    {LC_SEGMENT_64, "LC_SEGMENT_64"},
    {LC_DYLD_CHAINED_FIXUPS, "LC_DYLD_CHAINED_FIXUPS"},
    {LC_DYLD_EXPORTS_TRIE, "LC_DYLD_EXPORTS_TRIE"},
    {LC_UUID, "LC_UUID"},
    {LC_BUILD_VERSION, "LC_BUILD_VERSION"},
    {LC_SOURCE_VERSION, "LC_SOURCE_VERSION"},
    {LC_MAIN, "LC_MAIN"},
    {LC_FUNCTION_STARTS, "LC_FUNCTION_STARTS"},
    {LC_DATA_IN_CODE, "LC_DATA_IN_CODE"},
    {LC_CODE_SIGNATURE, "LC_CODE_SIGNATURE"},
    {LC_ROUTINES_64, "LC_ROUTINES_64"},
    {LC_RPATH, "LC_RPATH"},
    {LC_SEGMENT_SPLIT_INFO, "LC_SEGMENT_SPLIT_INFO"},
    {LC_REEXPORT_DYLIB, "LC_REEXPORT_DYLIB"},
    {LC_LAZY_LOAD_DYLIB, "LC_LAZY_LOAD_DYLIB"},
    {LC_ENCRYPTION_INFO, "LC_ENCRYPTION_INFO"},
    {LC_DYLD_INFO, "LC_DYLD_INFO"},
    {LC_DYLD_INFO_ONLY, "LC_DYLD_INFO_ONLY"},
    {LC_LOAD_UPWARD_DYLIB, "LC_LOAD_UPWARD_DYLIB"},
    {LC_VERSION_MIN_MACOSX, "LC_VERSION_MIN_MACOSX"},
    {LC_VERSION_MIN_IPHONEOS, "LC_VERSION_MIN_IPHONEOS"},
    {LC_DYLD_ENVIRONMENT, "LC_DYLD_ENVIRONMENT"},
    {LC_DYLIB_CODE_SIGN_DRS, "LC_DYLIB_CODE_SIGN_DRS"},
    {LC_ENCRYPTION_INFO_64, "LC_ENCRYPTION_INFO_64"},
    {LC_LINKER_OPTION, "LC_LINKER_OPTION"},
    {LC_LINKER_OPTIMIZATION_HINT, "LC_LINKER_OPTIMIZATION_HINT"},
    {LC_VERSION_MIN_TVOS, "LC_VERSION_MIN_TVOS"},
    {LC_VERSION_MIN_WATCHOS, "LC_VERSION_MIN_WATCHOS"},
    {LC_NOTE, "LC_NOTE"},
};

#endif
