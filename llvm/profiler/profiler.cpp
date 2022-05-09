#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Compiler.h"
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace {

    class Hello : public PassInfoMixin<Hello>  {
    public:
        PreservedAnalyses run(Function& f, FunctionAnalysisManager& am) {
            for (const auto& b : f) {
                for (const auto& i : b) {
                    if (const auto* call = dyn_cast<CallInst>(&i)) {
                        if (call->getCalledFunction()->getName() == "malloc") {
                            errs() << "Hello: found malloc call at ";
                            call->getDebugLoc().print(errs());
                            errs() << "\n";
                        }
                    }
                }
            }
            return PreservedAnalyses::all();
        }

        static bool isRequired() { return true; }
    };

};  // namespace

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "HelloWorldPass", "v0.1",
        [](PassBuilder& pb) {
            pb.registerPipelineParsingCallback(
                [](StringRef name, FunctionPassManager &fpm,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (name == "hello-world") {
                        fpm.addPass(Hello());
                        return true;
                    }
                    return false;
                }
            );
        }
    };
}

