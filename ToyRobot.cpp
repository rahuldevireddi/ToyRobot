/*******************************************************************
 * CLASS NAME  : ToyRobot
 * Implemenatation of toy robot
 *
 * Author: Rahul Devireddy
 *
 ********************************************************************/
#include <iostream>
#include <cstring>
#include <sstream>

#include "ToyRobot.h"

using namespace std;


/*****************************************************************
DESCRIPTION : Constructor
******************************************************************/
ToyRobot::ToyRobot()
{
    isInitialCoordinatesSet = false;

    roboLocation.xy.first = 0;
    roboLocation.xy.second = 0;
    roboLocation.direction = "";

    int size = sizeof(commands)/sizeof(commands[0]);
    for (int index = 0; index < size; index++)
    {
        commandMap.insert({commands[index].command, commands[index].value});
    }
}


/*****************************************************************
DESCRIPTION : Checks the validity of the user input command
******************************************************************/
bool ToyRobot::IsValidCommand(const std::string &command)
{
    return ((commandMap.find(command) != commandMap.end()) && (commandMap[command] >= PLACE) && (commandMap[command] < CMD_MAX));
}


/*****************************************************************
DESCRIPTION : Validate user input direction field
******************************************************************/
bool ToyRobot::IsValidDirection(const std::string &direction)
{
    return ((commandMap.find(direction) != commandMap.end()) && (commandMap[direction] >= NORTH) && (commandMap[direction] <= SOUTH));
}


/*****************************************************************
DESCRIPTION : Validate whether the given co-ordinates are within the given board range
******************************************************************/
bool ToyRobot::AreCoordinatesValid(const int &x, const int &y)
{
    return ((x >= 0) && (x < MAX_GRID_SIZE) && (y >= 0) && (y < MAX_GRID_SIZE));
}


/*****************************************************************
DESCRIPTION : Update the robo location (x, y)
******************************************************************/
void ToyRobot::UpdateRoboLocation(pair<int, int> xy)
{
    roboLocation.xy = xy;
}


/*****************************************************************
DESCRIPTION : Update the robo location (direction)
******************************************************************/
void ToyRobot::UpdateRoboLocation(const string &direction)
{
    roboLocation.direction = direction;
}


/*****************************************************************
DESCRIPTION : Update the robo location (x, y, direction)
******************************************************************/
void ToyRobot::UpdateRoboLocation(pair<int, int> xy, const string &direction)
{
    roboLocation.xy = xy;
    roboLocation.direction = direction;
}


/*****************************************************************
DESCRIPTION : Help text
******************************************************************/
void ToyRobot::Help(const string &category)
{
    ostringstream helpText;

    if (category.compare("app-help") == 0)
    {
        helpText << "Provide robo coordinates 'PLACE X,Y,[NORTH|EAST|WEST|SOUTH]\\n', followed by one or more commands (\\n delimiter)\n";
        for (auto itr = commandMap.begin(); itr != commandMap.end(); itr++)
        {
            if ((itr->second >= PLACE) && (itr->second <= CMD_MAX)) helpText << itr->first << "\n";
        }
        helpText << "Enter 'REPORT' to see the final position\n\n";
    }
    else if (category.compare("command-help") == 0)
    {
        for (auto itr = commandMap.begin(); itr != commandMap.end(); itr++)
        {
            if ((itr->second >= PLACE) && (itr->second <= CMD_MAX)) helpText << itr->first << "\n";
        }
        helpText << "Please try again (Enter 'REPORT' to exit)\n\n";
    }

    cout << helpText.str();
}


/*****************************************************************
DESCRIPTION : Parse (initial) robot coordinates (X,Y,F)
******************************************************************/
void ToyRobot::SetInitialRobotCoordinates(const string &token)
{
    int x;
    int y;
    char direction[10];

    if ((sscanf(token.c_str(), "%d,%d,%s", &x, &y, direction) > 0))
    {
        string dir(direction);
        if (AreCoordinatesValid(x, y) && IsValidDirection(dir))
        {
            isInitialCoordinatesSet = true;
            UpdateRoboLocation(make_pair(x, y), dir);
            // hard (re)setting the robot coordinates should clear the previous commands
            roboCommands.clear();
        }
        else
        {
            if (AreCoordinatesValid(x, y) == false)
            {
                cout << "\n**Info**: Invalid coordinates (" << x << ", " << y << ")" << endl;
                cout << "Allowed range is (0-" << MAX_GRID_SIZE << ", " << "0-" << MAX_GRID_SIZE << ")\n";
            }
            else if (IsValidDirection(dir) == false)
            {
                cout << "\n**Info**: Invalid direction\n";
            }

            cout << "Please try again ..\n";
        }
    }
    else
    {
        cout << "**Info**: Invalid format\nPlease try again ..\n";
    }
}


/*****************************************************************
DESCRIPTION : Instruct the robo to move according to the given command
******************************************************************/
void ToyRobot::AddCommandToRobot(const string &command)
{
    if ((isInitialCoordinatesSet == false) || (IsValidCommand(command) == false)) return;

    roboCommands.push_back(command);
}


/*****************************************************************
DESCRIPTION : Parse the user input
              NOTE: Used '\n' as the delimiter
******************************************************************/
void ToyRobot::GetUserInput(void)
{
    string input;
    size_t found;

    Help("app-help");

    do
    {
        input.clear();
        getline(cin, input);

        if ((found = input.find(PLACE_COMMAND_TEXT)) != string::npos)
        {
            string token = input.substr(strlen(PLACE_COMMAND_TEXT));
            SetInitialRobotCoordinates(token);
        }
        else if (isInitialCoordinatesSet && IsValidCommand(input))
        {
            AddCommandToRobot(input);
        }
        else if (isInitialCoordinatesSet == false)
        {
            cout << "\n**Warning**: Initial coordinateds are not set, ignored '" << input << "'\n\n";
            Help("app-help");
        }
        else
        {
            cout << "\n**Info**: Unknown command '" << input << "', the valid commands are:\n";
            Help("command-help");
        }
    } while (input.compare(REPORT_COMMAND_TEXT) != 0);
}


/*****************************************************************
DESCRIPTION : Move and locate the toy robo based on input directions
******************************************************************/
void ToyRobot::LocateRobot(void)
{
    cout << "\n\nInput data:\n";
    if (isInitialCoordinatesSet) cout << "PLACE " << roboLocation.xy.first << "," << roboLocation.xy.second << "," << roboLocation.direction << endl;
    for (auto cmd : roboCommands)
    {
        cout << cmd << endl;

        switch (commandMap[cmd])
        {
            case MOVE:
                if ((GetDirection().compare(NORTH_PHASE_TEXT) == 0) && (AreCoordinatesValid(GetX(), GetY() + 1))) UpdateRoboLocation(make_pair(GetX(), GetY() + 1));
                else if ((GetDirection().compare(EAST_PHASE_TEXT) == 0) && (AreCoordinatesValid(GetX() + 1, GetY()))) UpdateRoboLocation(make_pair(GetX() + 1, GetY()));
                else if ((GetDirection().compare(WEST_PHASE_TEXT) == 0) && (AreCoordinatesValid(GetX() - 1, GetY()))) UpdateRoboLocation(make_pair(GetX() - 1, GetY()));
                else if ((GetDirection().compare(SOUTH_PHASE_TEXT) == 0) && (AreCoordinatesValid(GetX(), GetY() - 1))) UpdateRoboLocation(make_pair(GetX(), GetY() - 1));
                break;
            case LEFT:
                if (GetDirection().compare(NORTH_PHASE_TEXT) == 0) UpdateRoboLocation(WEST_PHASE_TEXT);
                else if (GetDirection().compare(EAST_PHASE_TEXT) == 0) UpdateRoboLocation(NORTH_PHASE_TEXT);
                else if (GetDirection().compare(WEST_PHASE_TEXT) == 0) UpdateRoboLocation(SOUTH_PHASE_TEXT);
                else if (GetDirection().compare(SOUTH_PHASE_TEXT) == 0) UpdateRoboLocation(EAST_PHASE_TEXT);
                break;
            case RIGHT:
                if (GetDirection().compare(NORTH_PHASE_TEXT) == 0) UpdateRoboLocation(EAST_PHASE_TEXT);
                else if (GetDirection().compare(EAST_PHASE_TEXT) == 0) UpdateRoboLocation(SOUTH_PHASE_TEXT);
                else if (GetDirection().compare(WEST_PHASE_TEXT) == 0) UpdateRoboLocation(NORTH_PHASE_TEXT);
                else if (GetDirection().compare(SOUTH_PHASE_TEXT) == 0) UpdateRoboLocation(WEST_PHASE_TEXT);
                break;
            case REPORT:
                cout << "\nOutput: " << GetX() << "," << GetY() << "," << GetDirection() << endl;
                break;
            default:
                cout << "**Info**: Unknown command\n";
        }
    }
}
