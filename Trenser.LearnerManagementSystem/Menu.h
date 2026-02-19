#include <iostream>
#include <memory>
#pragma once
#include "LMSController.h"

class Menu
{
private:
	std::shared_ptr<LMSController> m_lmsController;
public:
	Menu() = default;
	Menu(std::shared_ptr<LMSController> lmsController) : m_lmsController(lmsController) {}
	void startSession();
	void studentMenu();
	void instructorMenu();
	void adminMenu();
};

