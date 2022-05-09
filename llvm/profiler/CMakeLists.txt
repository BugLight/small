add_llvm_library(small_profiler MODULE BUILDTREE_ONLY
    profiler.cpp
    DEPENDS intrinsics_gen
    PLUGIN_TOOL opt
)

