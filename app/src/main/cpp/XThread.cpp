//
// Created by 27515 on 2025-05-17.
//

#include "XThread.h"
#include "XLog.h"

#include <thread>
#include <chrono>

using namespace std;

void XSleep(int mis) {
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

bool XThread::Start() {
    this->isExit = false;
    this->isPause = false;
    thread th(&XThread::ThreadMain, this);
    th.detach();
    return true;
}

void XThread::ThreadMain() {
    this->isRunning = true;
    XLOGI("XThread in.");
    Main();
    XLOGI("XThread out.");
    this->isRunning = false;
}

void XThread::Stop() {
    this->isExit = true;
    for (int i = 0; i < 200; ++i) {
        if (!this->isRunning) {
            XLOGI("Stop XThread success!");
            return;
        }
        XSleep(1);
    }
    XLOGI("Stop XThread failed!");
}

void XThread::SetPause(bool isP) {
    this->isPause = isP;
    for (int i = 0; i < 10; ++i) {
        if (this->isPausing == isP) {
            break;
        }
        XSleep(10);
    }
}
