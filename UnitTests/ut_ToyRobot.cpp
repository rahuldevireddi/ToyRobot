/*******************************************************************
* Test Group: Testing TestRobot.cpp
*
* Author: Rahul Devireddy
*
********************************************************************/
#include "ToyRobot.h"
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(ToyRobot)
{
    ToyRobot robot;

    void setup(void)
    {

    }

    void teardown(void)
    {

    }

    void ResetRoboPosition(void)
    {
        robot.SetInitialRobotCoordinates("0,0,SOUTH");      // default location
        CHECK(robot.isInitialCoordinatesSet == true);
    }

};


TEST(ToyRobot, SetInitialRobotCoordinates)
{
    ResetRoboPosition();

    robot.SetInitialRobotCoordinates("5,5,NORTH");          // out of range (5*5), expected it to remain at default location
    CHECK_EQUAL(robot.GetX(), 0);
    CHECK_EQUAL(robot.GetY(), 0);
    CHECK_EQUAL(robot.GetDirection(), SOUTH_PHASE_TEXT);

    robot.SetInitialRobotCoordinates("-1,-1,NORTH");        // invalid coordinates
    CHECK_EQUAL(robot.GetX(), 0);
    CHECK_EQUAL(robot.GetY(), 0);
    CHECK_EQUAL(robot.GetDirection(), SOUTH_PHASE_TEXT);

    robot.SetInitialRobotCoordinates("1,2,ABC");            // invalid direction
    CHECK_EQUAL(robot.GetX(), 0);
    CHECK_EQUAL(robot.GetY(), 0);
    CHECK_EQUAL(robot.GetDirection(), SOUTH_PHASE_TEXT);

    robot.SetInitialRobotCoordinates("2, 3, NORTH");        // valid co-ordinates, direction, expected the rebo coordinates to change
    CHECK_EQUAL(robot.GetX(), 2);
    CHECK_EQUAL(robot.GetY(), 3);
    CHECK_EQUAL(robot.GetDirection(), NORTH_PHASE_TEXT);

    robot.SetInitialRobotCoordinates("4,2,SOUTH");          // valid co-ordinates, direction, expected the rebo coordinates to change
    CHECK_EQUAL(robot.GetX(), 4);
    CHECK_EQUAL(robot.GetY(), 2);
    CHECK_EQUAL(robot.GetDirection(), SOUTH_PHASE_TEXT);
}


TEST(ToyRobot, ValidateUserComands)
{
    CHECK_FALSE(robot.isInitialCoordinatesSet);
    robot.AddCommandToRobot("LEFT");
    CHECK_EQUAL(robot.roboCommands.size(), 0);              // without setting initial co-ordinates, the robot shouldn't take any instructions

    robot.SetInitialRobotCoordinates("0,0,NORTH");
    robot.AddCommandToRobot("MOVE");
    robot.SetInitialRobotCoordinates("2,2,EAST");           // reset the robo coordinates
    CHECK_EQUAL(robot.roboCommands.size(), 0);              // should clear the previous commands

    robot.AddCommandToRobot("MOVE");
    robot.AddCommandToRobot("LEFT");
    robot.AddCommandToRobot("RIGHT");
    robot.AddCommandToRobot("REPORT");
    CHECK_EQUAL(robot.roboCommands.size(), 4);
    robot.AddCommandToRobot("ABCD");                        // invalid command should be ignored
    CHECK_EQUAL(robot.roboCommands.size(), 4);
}


TEST(ToyRobot, LocateRobot)
{
    // Make the robot move out of the table and see how it goes !!
    robot.SetInitialRobotCoordinates("4,4,EAST");
    robot.AddCommandToRobot("MOVE");                        // shouldn't execute this command otherwise it will fall-off
    robot.AddCommandToRobot("REPORT");
    robot.LocateRobot();
    CHECK_EQUAL(robot.GetX(), 4);
    CHECK_EQUAL(robot.GetY(), 4);
    CHECK_EQUAL(robot.GetDirection(), EAST_PHASE_TEXT);

    robot.SetInitialRobotCoordinates("0,2,WEST");
    robot.AddCommandToRobot("MOVE");                        // shouldn't execute this command otherwise it will fall-off
    robot.AddCommandToRobot("REPORT");
    robot.LocateRobot();
    CHECK_EQUAL(robot.GetX(), 0);
    CHECK_EQUAL(robot.GetY(), 2);
    CHECK_EQUAL(robot.GetDirection(), WEST_PHASE_TEXT);

    robot.SetInitialRobotCoordinates("0,0,NORTH");
    CHECK(robot.isInitialCoordinatesSet);
    robot.AddCommandToRobot("LEFT");
    robot.AddCommandToRobot("REPORT");
    CHECK_EQUAL(robot.roboCommands.size(), 2);
    robot.LocateRobot();
    CHECK_EQUAL(robot.GetX(), 0);
    CHECK_EQUAL(robot.GetY(), 0);
    CHECK_EQUAL(robot.GetDirection(), WEST_PHASE_TEXT);

    robot.SetInitialRobotCoordinates("1,2,EAST");
    robot.AddCommandToRobot("MOVE");
    robot.AddCommandToRobot("MOVE");
    robot.AddCommandToRobot("LEFT");
    robot.AddCommandToRobot("MOVE");
    robot.AddCommandToRobot("REPORT");
    CHECK_EQUAL(robot.roboCommands.size(), 5);
    robot.LocateRobot();
    CHECK_EQUAL(robot.GetX(), 3);
    CHECK_EQUAL(robot.GetY(), 3);
    CHECK_EQUAL(robot.GetDirection(), NORTH_PHASE_TEXT);

    robot.SetInitialRobotCoordinates("0,0,EAST");
    robot.AddCommandToRobot("RIGHT");
    robot.AddCommandToRobot("REPORT");
    CHECK_EQUAL(robot.roboCommands.size(), 2);
    robot.LocateRobot();
    CHECK_EQUAL(robot.GetX(), 0);
    CHECK_EQUAL(robot.GetY(), 0);
    CHECK_EQUAL(robot.GetDirection(), SOUTH_PHASE_TEXT);

    robot.SetInitialRobotCoordinates("0,0,SOUTH");
    robot.AddCommandToRobot("LEFT");
    robot.AddCommandToRobot("LEFT");                         // Rotate 180 (90+90) degress
    robot.AddCommandToRobot("REPORT");
    CHECK_EQUAL(robot.roboCommands.size(), 3);
    robot.LocateRobot();
    CHECK_EQUAL(robot.GetX(), 0);
    CHECK_EQUAL(robot.GetY(), 0);
    CHECK_EQUAL(robot.GetDirection(), NORTH_PHASE_TEXT);

    robot.SetInitialRobotCoordinates("0,0,NORTH");
    robot.AddCommandToRobot("RIGHT");
    robot.AddCommandToRobot("RIGHT");
    robot.AddCommandToRobot("RIGHT");
    robot.AddCommandToRobot("RIGHT");
    robot.AddCommandToRobot("REPORT");
    robot.LocateRobot();
    CHECK_EQUAL(robot.GetDirection(), NORTH_PHASE_TEXT);    // Rotated 360 degress
}


int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}
