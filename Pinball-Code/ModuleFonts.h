#ifndef _FONTS_H_
#define _FONTS_H_


#include "Module.h"


class ModuleFonts : public Module
{
public:
	ModuleFonts(bool start_enabled = true);
	~ModuleFonts();
	bool Init()  override;
	bool CleanUp() override;
};

#endif // !_FONTS_H_

