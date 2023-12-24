#ifndef EVENTPROCESS_H
#define EVENTPROCESS_H
#include"myworld.h"
#include"updatecameraprojection.h"
#include"RoleController/RoleContorller.h"
#include"Bag/BagGlobalSource.h"
#include"Bag/DrawBag.h"
#include"drawinfo.h"
#include"../exposureadjust.h"
///////////////////////////////////////////////////
enum EVENT {
	WINDOW_RESIZE, MOUSE_MOVE, F3_PRESS,
	ESCAPE_PRESS, W_PRESS, A_PRESS, S_PRESS, D_PRESS, SPACE_PRESS,
	WSAD_RELEASE, LEFT_MOUSE_CLICK, RIGHT_MOUSE_CLICK,
	ONE_PRESS,TWO_PRESS,THREE_PRESS,FOUR_PRESS,FIVE_PRESS,SIX_PRESS,SEVEN_PRESS,EIGHT_PRESS,NINE_PRESS,
	E_PRESS, F5_PRESS,F6_PRESS
};//ÊÂ¼þÃ¶¾Ù
///////////////////////////////////////////////////
void EventProcess();
///////////////////////////////////////////////////
void EVENT_W_PRESS();
void EVENT_A_PRESS();
void EVENT_S_PRESS();
void EVENT_D_PRESS();
void EVENT_SPACE_PRESS();
void EVENT_WINDOW_RESIZE();
void EVENT_MOUSE_MOVE();
void EVENT_F3_PRESS();
void EVENT_F5_PRESS();
void EVENT_F6_PRESS();
void EVENT_ESCAPE_PRESS();
void EVENT_WSAD_RELEASE();
void EVENT_LEFT_MOUSE_CLICK();
void EVENT_RIGHT_MOUSE_CLICK();
void EVENT_ONE_TO_NINE_PRESS(int id);
void EVENT_E_PRESS();
///////////////////////////////////////////////////
#endif // EVENTPROCESS_H
