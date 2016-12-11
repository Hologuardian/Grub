#ifndef _INPUT_CLASS_H_
#define _INPUT_CLASS_H_

/*This class is currently a place holder for DirectInput. This class was created to make a quick iteration
of user input and will be refactored at a later date*/

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();
	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool keys[256];
};

#endif