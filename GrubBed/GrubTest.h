#ifndef GRUB_GRUB_TEST_H
#define GRUB_GRUB_TEST_H
#include "Grub.h"

class GrubTest : public Grub
{
public:
	GrubTest();
	void Update(float Delta);
	void Render();
	void Initialize();
};

#endif