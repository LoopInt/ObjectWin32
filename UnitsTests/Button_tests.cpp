#include "pch.h"

#include "Window.h"
#include "Instance.h"
#include "Button.h"

TEST(Button, getText) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    Button b(w, L"OK");

    ASSERT_EQ(b.getText(), L"OK");
}

TEST(Button, setText) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    Button b(w, L"OK");
    b.setText(L"KO");

    ASSERT_EQ(b.getText(), L"KO");
}