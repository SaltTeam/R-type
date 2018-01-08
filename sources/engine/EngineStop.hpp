
#pragma once

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
