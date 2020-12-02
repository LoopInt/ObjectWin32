#include "pch.h"

#include "Window.h"
#include "Instance.h"
#include "PushButton.h"

TEST(PushButton, getText) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    PushButton b(w, L"OK");

    ASSERT_EQ(b.getText(), L"OK");
}

TEST(PushButton, setText) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    PushButton b(w, L"OK");
    b.setText(L"KO");

    ASSERT_EQ(b.getText(), L"KO");
}

TEST(PushButton, getXPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    PushButton b(w, L"OK");

    ASSERT_EQ(b.getXPos(), 10);
}

TEST(PushButton, getYPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    PushButton b(w, L"OK");

    ASSERT_EQ(b.getYPos(), 10);
}

TEST(PushButton, setXPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    PushButton b(w, L"OK");

    b.setXPos(20);

    ASSERT_EQ(b.getXPos(), 20);
}

TEST(PushButton, setYPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    PushButton b(w, L"OK");

    b.setYPos(20);

    ASSERT_EQ(b.getYPos(), 20);
}

TEST(PushButton, setPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    PushButton b(w, L"OK");

    b.setXPos(25);
    b.setYPos(20);

    ASSERT_EQ(b.getYPos(), 20);
    ASSERT_EQ(b.getXPos(), 25);
}