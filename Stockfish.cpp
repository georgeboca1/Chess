#include "Stockfish.h"

#include <windows.h>
#include <iostream>
#include <string>

StockfishEngine::StockfishEngine()
{
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;


    // Create pipes for communication
    if (!CreatePipe(&hChildStd_OUT_Rd, &hChildStd_OUT_Wr, &saAttr, 0)) {
        std::cerr << "Failed to create output pipe\n";
        return;
    }
    if (!CreatePipe(&hChildStd_IN_Rd, &hChildStd_IN_Wr, &saAttr, 0)) {
        std::cerr << "Failed to create input pipe\n";
        return;
    }

    // Ensure the write handle to the pipe for STDIN is not inherited.
    if (!SetHandleInformation(hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0)) {
        std::cerr << "Failed to set handle information\n";
        return;
    }

    // Set up STARTUPINFO
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = hChildStd_OUT_Wr;
    siStartInfo.hStdOutput = hChildStd_OUT_Wr;
    siStartInfo.hStdInput = hChildStd_IN_Rd;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

    // Start Stockfish process
    if (!CreateProcess(
        TEXT("stockfish.exe"),  // Path to Stockfish binary
        NULL, NULL, NULL, TRUE,
        CREATE_NO_WINDOW, NULL, NULL,
        &siStartInfo, &piProcInfo
    )) {
        std::cerr << "Failed to start Stockfish\n";
    }
}

StockfishEngine::~StockfishEngine() {
    // Cleanup
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
    CloseHandle(hChildStd_IN_Wr);
    CloseHandle(hChildStd_OUT_Rd);
    CloseHandle(hChildStd_OUT_Wr);
    CloseHandle(hChildStd_IN_Rd);
}

void StockfishEngine::sendCommand(const std::string& command) {
    std::string cmd = command + "\n";
    DWORD written;
    WriteFile(hChildStd_IN_Wr, cmd.c_str(), cmd.length(), &written, NULL);
    std::cout << "\nSent command to stockfish:" << command;
}

std::string StockfishEngine::readResponse() {
    DWORD bytesRead;
    char buffer[4096];
    std::string response;

    while (true) {
        if (!ReadFile(hChildStd_OUT_Rd, buffer, sizeof(buffer) - 1, &bytesRead, NULL) || bytesRead == 0) break;
        buffer[bytesRead] = '\0';
        std::string temp(buffer, bytesRead);
        if (temp.find("bestmove") != std::string::npos) {
            response = temp.substr(temp.find("bestmove"));
            break;
        }
    }
    std::cout << "\nRead response from stockfish:" << response;
    return response;
}


bool StockfishEngine::isReady()
{
    DWORD bytesRead;
    char buffer[4096];
    std::string response;

    while (true) {
        if (!ReadFile(hChildStd_OUT_Rd, buffer, sizeof(buffer) - 1, &bytesRead, NULL) || bytesRead == 0) break;
        buffer[bytesRead] = '\0';
        response += buffer;
        if (response.find("readyok") != std::string::npos)
        {
            std::cout << "\nStockfish is ready";
            return true;
            break;  // Stop reading when move is found
        }
    }
    return false;
}

void StockfishEngine::sendMoves(std::string move)
{
    moveHistory.push_back(move);
    std::string command = "position startpos moves";
    for (const auto& move : moveHistory) {
        command += " " + move;
    }
    sendCommand(command);
    sendCommand("go depth 10");
}

void StockfishEngine::addMove(std::string move)
{
    moveHistory.push_back(move);
}