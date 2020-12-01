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

TEST(Button, getXPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    Button b(w, L"OK");

    ASSERT_EQ(b.getXPos(), 10);
}

TEST(Button, getYPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    Button b(w, L"OK");

    ASSERT_EQ(b.getYPos(), 10);
}

TEST(Button, setXPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    Button b(w, L"OK");

    b.setXPos(20);

    ASSERT_EQ(b.getXPos(), 20);
}

TEST(Button, setYPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    Button b(w, L"OK");

    b.setYPos(20);

    ASSERT_EQ(b.getYPos(), 20);
}

TEST(Button, setPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;
    w.create(GetModuleHandle(NULL));

    Button b(w, L"OK");

    b.setXPos(25);
    b.setYPos(20);

    ASSERT_EQ(b.getYPos(), 20);
    ASSERT_EQ(b.getXPos(), 25);
}