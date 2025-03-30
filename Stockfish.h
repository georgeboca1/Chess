#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

class StockfishEngine {
private:
    HANDLE hChildStd_IN_Rd = NULL, hChildStd_IN_Wr = NULL;
    HANDLE hChildStd_OUT_Rd = NULL, hChildStd_OUT_Wr = NULL;
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;

    std::vector<std::string> moveHistory;

public:
    StockfishEngine();
    ~StockfishEngine();

    void sendCommand(const std::string& command);
    void addMove(std::string move);
    void sendMoves(std::string move);
    std::string readResponse();
    bool isReady();
};