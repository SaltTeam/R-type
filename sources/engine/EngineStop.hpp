
#pragma once

#include <iostream>
#include <exception>
#include <string>

enum EngineErrorCode : unsigned int {
    /// 0x0? Unknown errors
    UNKONWN = 0x00,
    UNKONWN_INITIALISATON_FAILED = 0x01,
    UNKONWN_SHUTDOWN_FAILED = 0x02,
    UNKONWN_EARLY_UPDATE_FAILED = 0x03,
    UNKONWN_UPDATE_FAILED = 0x04,
    UNKONWN_LATE_UPDATE_FAILED = 0x05,
    /// 0x1? Memory errors
    MEMORY_ALLOCATION_FAILED = 0x10
};

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

class EngineErrorReason {
public:
    std::string msg;
    EngineErrorCode code;

    explicit EngineErrorReason(const std::string &msg, const EngineErrorCode code) : msg(msg), code(code) {}
};

class CriticalEngineError : public std::runtime_error {
public:
    EngineErrorReason reason;

    explicit CriticalEngineError(const EngineErrorReason &reason) : runtime_error(reason.msg), reason(reason) {}
};