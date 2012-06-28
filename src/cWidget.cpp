
#include "../include/cWidget.h"

Widget::Widget() {
	m_focused = false;
}

Widget::~Widget() {
}

void Widget::setFocus(bool foc) {
	m_focused = foc;
}

