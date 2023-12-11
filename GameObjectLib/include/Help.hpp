#pragma once

#include "MenuObject.hpp"

class Help : public MenuObject
{
public:
	Help();
	~Help() override = default;

	void load(Window_s& window) override;
	void textureSetters(Window_s& window);
};
