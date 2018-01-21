
#include "EngineStop.hpp"

std::ostream &operator<<(std::ostream &out, const EngineErrorCode value) {
    const char *s = nullptr;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch (value) {
        PROCESS_VAL(UNKONWN);
        PROCESS_VAL(UNKONWN_INITIALISATON_FAILED);
        PROCESS_VAL(UNKONWN_SHUTDOWN_FAILED);
        PROCESS_VAL(UNKONWN_EARLY_UPDATE_FAILED);
        PROCESS_VAL(UNKONWN_UPDATE_FAILED);
        PROCESS_VAL(UNKONWN_LATE_UPDATE_FAILED);
        PROCESS_VAL(MEMORY_ALLOCATION_FAILED);
    }
#undef PROCESS_VAL
    return out << s;
}
