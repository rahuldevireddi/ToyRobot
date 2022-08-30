/*******************************************************************
 * FILE NAME  : ToyRobotMain.cpp
 *
 * Author: Rahul Devireddy
 *
 ********************************************************************/

#include "ToyRobot.h"


/*****************************************************************
DESCRIPTION : Main function
******************************************************************/
int main()
{
    ToyRobot robot;

    robot.GetUserInput();
    robot.LocateRobot();

    return 0;
}
