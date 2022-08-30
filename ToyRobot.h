/*******************************************************************
* CLASS NAME  : ToyRobot class header file
*
* Author: Rahul Devireddy
*
********************************************************************/
#ifndef TOY_ROBOT_H
#define TOY_ROBOT_H

#include <string>
#include <vector>
#include <map>

#define MAX_GRID_SIZE   5

#define NORTH_PHASE_TEXT    "NORTH"
#define EAST_PHASE_TEXT     "EAST"
#define WEST_PHASE_TEXT     "WEST"
#define SOUTH_PHASE_TEXT    "SOUTH"
#define PLACE_COMMAND_TEXT  "PLACE"
#define REPORT_COMMAND_TEXT "REPORT"


typedef struct
{
    const char *command;
    int value;
} cmdmap_s;


enum
{
    NORTH, EAST, WEST, SOUTH,
    PLACE,
    MOVE, LEFT, RIGHT,
    REPORT,
    CMD_MAX,
};


const cmdmap_s commands[] =
{
    {   .command = NORTH_PHASE_TEXT,        .value = NORTH,     },
    {   .command = EAST_PHASE_TEXT,         .value = EAST,      },
    {   .command = WEST_PHASE_TEXT,         .value = WEST,      },
    {   .command = SOUTH_PHASE_TEXT,        .value = SOUTH,     },
    {   .command = PLACE_COMMAND_TEXT,      .value = PLACE,     },
    {   .command = "MOVE",                  .value = MOVE,      },
    {   .command = "LEFT",                  .value = LEFT,      },
    {   .command = "RIGHT",                 .value = RIGHT,     },
    {   .command = REPORT_COMMAND_TEXT,     .value = REPORT,    },
};


typedef struct
{
    std::pair<int, int> xy;
    std::string direction;
} RoboLocation;


class ToyRobot
{
    public:
       ToyRobot(void);
       void GetUserInput(void);
       void LocateRobot(void);

#ifndef UNIT_TEST
    private:
#endif
        bool isInitialCoordinatesSet;
        RoboLocation roboLocation;
        std::map<std::string, int> commandMap;           // stores the map of valid commands
        std::vector<std::string> roboCommands;      // stores the user input directions

        // Getter functions
        int GetX(void) { return roboLocation.xy.first; }
        int GetY(void) { return roboLocation.xy.second; }
        std::string GetDirection(void) { return roboLocation.direction; }

        // input validation functions
        bool AreCoordinatesValid(const int &x, const int &y);
        bool IsValidCommand(const std::string &direction);
        bool IsValidDirection(const std::string &dirction);

        // robo movement commands
        void SetInitialRobotCoordinates(const std::string &input);
        void AddCommandToRobot(const std::string &command);

        // Robo location related functions
        void UpdateRoboLocation(std::pair<int, int> xy);
        void UpdateRoboLocation(const std::string &direction);
        void UpdateRoboLocation(std::pair<int, int> xy, const std::string &direction);

        void Help(const std::string &category);
};

#endif  // end of TOY_ROBOT_H