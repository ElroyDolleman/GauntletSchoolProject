#ifndef __Tutorial1_H_
#define __Tutorial1_H_

#include <Application.h>
#include <SpriteBatch.h>

// Derived application class that wraps up all globals neatly
class Main : public NHTV::Application
{
public:

	Main();
	virtual ~Main();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	
private:

    int screenWidth;
	int screenHeight;
};

#endif