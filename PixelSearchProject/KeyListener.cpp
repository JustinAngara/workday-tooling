#include "KeyListener.h"

#include <windows.h>
#include <cstring>
#include <string>
#include <vector>

// detect a key press edge (up -> down) so it triggers once per press.
static bool PressedEdge(int vk, bool& wasDown) {
    SHORT s = GetAsyncKeyState(vk);
    bool isDown = (s & 0x8000) != 0;

    bool pressed = (!wasDown && isDown);
    wasDown = isDown;
    return pressed;
}

static void SendKeyDown(WORD vk) {
    INPUT in{};
    in.type = INPUT_KEYBOARD;
    in.ki.wVk = vk;
    SendInput(1, &in, sizeof(INPUT));
}

static void SendKeyUp(WORD vk) {
    INPUT in{};
    in.type = INPUT_KEYBOARD;
    in.ki.wVk = vk;
    in.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &in, sizeof(INPUT));
}

static void SendCtrlCombo(WORD vk) {
    SendKeyDown(VK_CONTROL);
    SendKeyDown(vk);
    SendKeyUp(vk);
    SendKeyUp(VK_CONTROL);
}

static void SendBackspace() {
    SendKeyDown(VK_BACK);
    SendKeyUp(VK_BACK);
}

KeyListener::KeyListener(const std::vector<Data::Table>& output)
    : m_output(output) {
}

void KeyListener::run() {
    bool down[10] = { false }; // index 0..9 => VK_NUMPAD0..VK_NUMPAD9

    while (true) {
        for (int i = 0; i <= 9; ++i) {
            int vk = VK_NUMPAD0 + i;
            if (PressedEdge(vk, down[i])) {
                runCopyPaste(vk);
            }
        }

        Sleep(2);
    }
}

void KeyListener::runCopyPaste(int vk_code) {
    // 0 toggles swap (table 1 <-> 3)
    if (vk_code == VK_NUMPAD0) {
        m_swapSecondWithFourth = !m_swapSecondWithFourth;
        return;
    }

    // only 1..9
    if (vk_code < VK_NUMPAD1 || vk_code > VK_NUMPAD9) {
        return;
    }

    int keyIndex = vk_code - VK_NUMPAD1; // 0..8
    int tableIndex = keyIndex / 3;       // 0,1,2
    int fieldIndex = keyIndex % 3;       // 0=title,1=company,2=desc

    // swap table 1 <-> 3 when toggled
    if (m_swapSecondWithFourth) {
        if (tableIndex == 1) {
            tableIndex = 3;
        }
        else if (tableIndex == 3) {
            tableIndex = 1;
        }
    }

    if (tableIndex >= static_cast<int>(m_output.size())) {
        return;
    }

    const Data::Table& t = m_output[tableIndex];

    switch (fieldIndex) {
    case 0:
        copyToClipboardAndPaste(t.title);
        break;
    case 1:
        copyToClipboardAndPaste(t.company);
        break;
    case 2:
        copyToClipboardAndPaste(t.description);
        break;
    default:
        break;
    }
}

void KeyListener::copyToClipboardAndPaste(const std::string& text) {
    // 1) Put text on clipboard
    if (!OpenClipboard(nullptr)) {
        return;
    }

    EmptyClipboard();

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    if (!hMem) {
        CloseClipboard();
        return;
    }

    void* ptr = GlobalLock(hMem);
    if (!ptr) {
        GlobalFree(hMem);
        CloseClipboard();
        return;
    }

    memcpy(ptr, text.c_str(), text.size() + 1);
    GlobalUnlock(hMem);

    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();

    SendCtrlCombo('A');
    SendBackspace();
    SendCtrlCombo('V');

}
