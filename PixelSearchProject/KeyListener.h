#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include "Data.h"

class KeyListener {
public:
    explicit KeyListener(const std::vector<Data::Table>& output);
    void run();
    void runCopyPaste(int vk_code);
private:
    const std::vector<Data::Table>& m_output;
    bool m_swapSecondWithFourth = false;

    void copyToClipboardAndPaste(const std::string& text);
};
