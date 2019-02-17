#pragma once

#include <QtWidgets/QDialog>
#include "ui_protobufTest.h"

namespace addressbook
{
	class AddressBook;
}

class protobufTest : public QDialog
{
	Q_OBJECT

public:
	protobufTest(QWidget *parent = Q_NULLPTR);
	void test();
	void testPOD();
	static void print(const addressbook::AddressBook &info);

private:
	Ui::protobufTestClass ui;
};

struct Trival
{
	int i;
	Trival(int n)
	{
		i = n;
	}
	Trival() = default;
};
