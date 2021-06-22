#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string.h>
#include <vector>


using namespace std;

#ifndef BUS_SYSTEM
#define BUS_SYSTEM

#include <sstream>
#include <math.h>
#include <algorithm>

class BusSystem
{
public:
    class Route;
    struct Buses;
protected:
    int Busmax;
    int numRoute;
    Route* RouteList;
public:
    BusSystem()
    {
        Busmax = 0;
        numRoute = 0;
        RouteList = NULL;
    }
    ~BusSystem()
    {
        while (RouteList->next != NULL)
        {
            if (RouteList->prev != NULL) delete RouteList->prev;
            RouteList = RouteList->next;
        }
        if (RouteList != NULL) {
            delete RouteList;
            RouteList = NULL;
        }
    };
    string query(string);
    string getCodeINS(string&, bool end = 0);
    string getLPINS(string&, bool end = 0);
    string DEL(string, int, int);
    bool checkINT(string);
    int getCaseINS(string&, bool end = 1);
    int getTime(string&, bool end = 1);

public:
    class Route
    {
    public:
        struct Buses
        {
            string LP;
            bool Case = 0;
            int Time_A = 0,
                Time_B = 0;
            Buses* next = NULL;
            Buses* prev = NULL;
            friend class BusSystem;
        };

    private:
        Route* prev;
        Route* next;
        int count;
        string Code;
        Buses* BusesList;
        friend class BusSystem;
    public:
        Route()
        {
            this->BusesList = 0;
            this->next = 0;
            this->prev = 0;
            this->count = 0;
        }
        ~Route()
        {
            this->next = 0;
            this->prev = 0;
            del();
        }
        void setCode(string _Code)
        {
            this->Code = _Code;
        }
        void add(string _LP, int TimeA, int TimeB, bool _case = 0)
        {
            if (BusesList == NULL) {
                BusesList = new Buses();
                BusesList->Case = _case;
                BusesList->LP = _LP;
                BusesList->Time_A = TimeA;
                BusesList->Time_B = TimeB;
            }
            else {
                Buses* tmp = this->BusesList;
                while (tmp->next != NULL) tmp = tmp->next;
                tmp->next = new Buses();
                tmp->next->Case = _case;
                tmp->next->LP = _LP;
                tmp->next->Time_A = TimeA;
                tmp->next->Time_B = TimeB;
                tmp->next->prev = tmp;
            }
            this->count++;
        }

        int del()
        {
            int n = 0;
            Buses* tmp = this->BusesList;
            while (tmp != NULL)
            {
                if (this->count == 1) {
                    delete tmp;
                    tmp = NULL;
                    this->BusesList = 0;
                    this->count--;
                }
                else {
                    Buses* p = tmp;
                    this->BusesList = tmp->next;
                    tmp->next->prev = NULL;
                    tmp = tmp->next;
                    delete p;
                    p = NULL;
                    this->count--;
                }
                n++;
            }
            return n;
        }

        int del(int timeA)
        {
            int n = 0;
            Buses* tmp = this->BusesList;
            while (tmp != NULL)
            {
                if (tmp->Time_A == timeA) {
                    if (this->count == 1) {
                        delete tmp;
                        tmp = NULL;
                        this->BusesList = 0;
                        this->count--;
                    }
                    else {
                        Buses* p = tmp;

                        if (tmp->prev == NULL) {
                            this->BusesList = tmp->next;
                            tmp->next->prev = NULL;
                            tmp = tmp->next;
                        }
                        else if (tmp->next == NULL) {
                            tmp->prev->next = NULL;
                            tmp = NULL;
                        }
                        else {
                            tmp->prev->next = tmp->next;
                            tmp->next->prev = tmp->prev;
                            tmp = tmp->next;
                        }
                        delete p;
                        p = NULL;
                        this->count--;
                    }
                    n++;
                }
                if (tmp != NULL) tmp = tmp->next;
            }
            return n;
        }

        int del(int timeA, int timeB)
        {
            int n = 0;
            Buses* tmp = this->BusesList;
            while (tmp != NULL)
            {
                if (tmp->Time_A >= timeA && tmp->Time_A <= timeB) {
                    if (this->count == 1) {
                        delete tmp;
                        tmp = NULL;
                        this->BusesList = 0;
                        this->count--;
                    }
                    else {
                        Buses* p = tmp;

                        if (tmp->prev == NULL) {
                            this->BusesList = tmp->next;
                            tmp = tmp->next;
                            p->next->prev = NULL;
                            p->next = NULL;

                        }
                        else if (tmp->next == NULL) {
                            tmp->prev->next = NULL;
                            tmp = NULL;
                        }
                        else {
                            tmp->prev->next = tmp->next;
                            tmp->next->prev = tmp->prev;
                            tmp = tmp->next;
                        }
                        delete p;
                        p = NULL;
                        this->count--;
                    }
                    n++;
                }
                else tmp = tmp->next;
            }
            return n;
        }

        int C(int _case, int time, bool begin = 1)
        {
            Buses* tmp = BusesList;

            int _count = 0;
            switch (_case)
            {
            case 2:
                while (tmp != NULL) {
                    if ((tmp->Time_A <= time && tmp->Time_B > time && begin) ||
                        (tmp->Time_B < time && !begin))
                        _count++;
                    tmp = tmp->next;
                }
                break;
            default:
                while (tmp != NULL) {
                    if (((tmp->Time_A <= time && tmp->Time_B > time && begin) ||
                        (tmp->Time_B < time && !begin)) &&
                        tmp->Case == (bool)_case)
                        _count++;
                    tmp = tmp->next;
                }
                break;
            }
            return _count;
        }

        string G(int _case, int time, bool begin = 1)
        {
            Buses* tmp = this->BusesList;
            string tmp_LP;
            int timestart = -1;
            int timeend = 0xfffff;
            switch (_case)
            {
            case 2:
                while (tmp != NULL) {
                    if ((tmp->Time_A <= time && tmp->Time_B > time && begin) ||
                        (tmp->Time_B < time && !begin)) {
                        if (begin && tmp->Time_A >= timestart) {
                            timestart = tmp->Time_A;
                            tmp_LP = tmp->LP;
                        }
                        else if (!begin && tmp->Time_B <= timeend) {
                            if ((tmp->Time_B == timeend && tmp->Time_A > timestart) || tmp->Time_B < timeend) {
                                timeend = tmp->Time_B;
                                timestart = tmp->Time_A;
                                tmp_LP = tmp->LP;
                            }
                        }
                    }
                    tmp = tmp->next;
                }
                break;
            default:
                while (tmp != NULL) {
                    if (((tmp->Time_A <= time && tmp->Time_B > time && begin) ||
                        (tmp->Time_B < time && !begin)) &&
                        tmp->Case == (bool)_case) {
                        if (begin && tmp->Time_A >= timestart) {
                            timestart = tmp->Time_A;
                            tmp_LP = tmp->LP;
                        }
                        else if (!begin && tmp->Time_B <= timeend) {
                            if ((tmp->Time_B == timeend && tmp->Time_A > timestart) || tmp->Time_B < timeend) {
                                timeend = tmp->Time_B;
                                timestart = tmp->Time_A;
                                tmp_LP = tmp->LP;
                            }
                        }
                    }
                    tmp = tmp->next;
                }
                break;
            }
            return tmp_LP;

        }

    };

};

bool BusSystem::checkINT(string instruction)
{
    if (instruction[0] < 48 || instruction[0] > 57) return 0;
    return 1;
}


string BusSystem::query(string instruction) {
    int index = 0;
    string CODE;
    while (instruction[0] != ' ' && instruction[0] != '\0') {
        index += (int)instruction[0];
        instruction.erase(0, 1);
    }
    if (instruction[0] != ' ') return "-1";
    else instruction.erase(0, 1);

    switch (index)
    {
    case 164://SQ
    {
        if (!instruction.length() || instruction[0] == ' ' || !checkINT(instruction)) return "-1";
        this->Busmax = stoi(instruction);
        stringstream tmp;
        tmp << this->Busmax;
        if (instruction.length() - tmp.str().length())
            return "-1";
        break;
    }
    case 234://INS
    {
        CODE = this->getCodeINS(instruction);
        if (CODE.compare("-1") == 0) return "-1";

        string LP = this->getLPINS(instruction);
        if (LP.compare("-1") == 0) return "-1";

        int CASE = 0;

        if (count(instruction.begin(), instruction.end(), ' ') == 2) {
            CASE = this->getCaseINS(instruction, 0);
            if (CASE == -1) return "-1";
        }

        int time_A = this->getTime(instruction, 0);
        if (time_A == -1) return "-1";

        int time_B = this->getTime(instruction);
        if (time_B == -1) return "-1";

        if (time_A >= time_B) return "-1";

        if (this->RouteList == NULL) {
            this->RouteList = new Route();
            this->RouteList->setCode(CODE);
            this->numRoute++;
            this->RouteList->add(LP, time_A, time_B, CASE);
        }
        else {
            Route* tmp = this->RouteList;
            while (tmp->next != NULL && !(CODE.compare(tmp->Code)))
                tmp = tmp->next;

            if (CODE.compare(tmp->Code)) {
                tmp->next = new Route;
                tmp->next->setCode(CODE);
                this->numRoute++;
                tmp->next->add(LP, time_A, time_B, CASE);
            }
            else {
                if (this->Busmax <= tmp->count) return "-1";
                Route::Buses* tmpB = tmp->BusesList;
                while (tmpB != NULL) {
                    if (tmpB->Case == (bool)CASE) {
                        if (tmpB->Time_A == time_A ||
                            (tmpB->LP.compare(LP) == 0 && tmpB->Time_B >= time_A))
                            return "-1";
                    }

                    tmpB = tmpB->next;
                }
                tmp->add(LP, time_A, time_B, CASE);
                stringstream result;
                result << tmp->count;
                return result.str();
            }
        }
        break;
    }
    case 213://DEL
    {
        int timeA = 0;
        int timeB = 0;
        switch (count(instruction.begin(), instruction.end(), ' '))
        {
        case 0:
            CODE = this->getCodeINS(instruction, 1);
            if (CODE.compare("-1") == 0) return "-1";
            break;
        case 1:
            CODE = this->getCodeINS(instruction);
            if (CODE.compare("-1") == 0) return "-1";

            timeA = this->getTime(instruction, 1);
            if (timeA == -1) return "-1";
            break;
        case 2:
            CODE = this->getCodeINS(instruction);
            if (CODE.compare("-1") == 0) return "-1";

            timeA = this->getTime(instruction, 0);
            if (timeA == -1) return "-1";

            timeB = this->getTime(instruction);
            if (timeB == -1) return "-1";

            break;
        default:
            return "-1";
        }
        if (timeA > timeB) return "-1";
        return this->DEL(CODE, timeA, timeB);
        break;
    }
    case 150://CS
    {
        CODE = this->getCodeINS(instruction);
        if (CODE.compare("-1") == 0) return "-1";

        int CASE = 2;
        int Time;

        if (count(instruction.begin(), instruction.end(), ' ')) {
            Time = this->getTime(instruction, 0);
            if (Time == -1) return "-1";

            CASE = this->getCaseINS(instruction);
            if (CASE == -1) return "-1";
        }
        else {
            Time = this->getTime(instruction);
            if (Time == -1) return "-1";
        }

        Route* tmp = this->RouteList;
        while (tmp != NULL) {
            if (tmp->Code.compare(CODE) == 0) break;
            tmp = tmp->next;
        }
        stringstream result;
        if (tmp != NULL) {
            result << tmp->C(CASE, Time, 1);
            return result.str();
        }
        else return "0";

        break;
    }
    case 136://CE
    {
        CODE = this->getCodeINS(instruction);
        if (CODE.compare("-1") == 0) return "-1";

        int CASE = 2;
        int Time;

        if (count(instruction.begin(), instruction.end(), ' ')) {
            Time = this->getTime(instruction, 0);
            if (Time == -1) return "-1";

            CASE = this->getCaseINS(instruction);
            if (CASE == -1) return "-1";
        }
        else {
            Time = this->getTime(instruction);
            if (Time == -1) return "-1";
        }

        Route* tmp = this->RouteList;
        while (tmp != NULL) {
            if (tmp->Code.compare(CODE) == 0) break;
            tmp = tmp->next;
        }
        stringstream result;
        if (tmp != NULL) {
            result << tmp->C(CASE, Time, 0);
            return result.str();
        }
        else return "0";
        break;
    }
    case 154://GS
    {
        CODE = this->getCodeINS(instruction);
        if (CODE.compare("-1") == 0) return "-1";

        int CASE = 2;
        int Time;

        if (count(instruction.begin(), instruction.end(), ' ')) {
            Time = this->getTime(instruction, 0);
            if (Time == -1) return "-1";

            CASE = this->getCaseINS(instruction);
            if (CASE == -1) return "-1";
        }
        else {
            Time = this->getTime(instruction);
            if (Time == -1) return "-1";
        }

        Route* tmp = this->RouteList;
        while (tmp != NULL) {
            if (tmp->Code.compare(CODE) == 0) break;
            tmp = tmp->next;
        }
        if (tmp != NULL) {
            return tmp->G(CASE, Time, 1).length() ? tmp->G(CASE, Time, 1) : "-1";
        }
        else return "-1";
        break;
    }
    case 140://140
    {
        CODE = this->getCodeINS(instruction);
        if (CODE.compare("-1") == 0) return "-1";

        int CASE = 2;
        int Time;

        if (count(instruction.begin(), instruction.end(), ' ')) {
            Time = this->getTime(instruction, 0);
            if (Time == -1) return "-1";

            CASE = this->getCaseINS(instruction);
            if (CASE == -1) return "-1";
        }
        else {
            Time = this->getTime(instruction);
            if (Time == -1) return "-1";
        }

        Route* tmp = this->RouteList;
        while (tmp != NULL) {
            if (tmp->Code.compare(CODE) == 0) break;
            tmp = tmp->next;
        }
        if (tmp != NULL) {
            return tmp->G(CASE, Time, 0).length() ? tmp->G(CASE, Time, 0) : "-1";
        }
        else return "-1";
        break;
    }
    default:
        return "-1";
    }

    return "1";
}

string BusSystem::DEL(string CODE, int timeA = 0, int timeB = 0)
{
    Route* tmp = this->RouteList;
    while (tmp->next != NULL && tmp->Code != CODE) {
        tmp = tmp->next;
    }
    int n = 0;
    if (tmp->Code == CODE) {
        if (timeA) {
            if (timeB) {
                n = tmp->del(timeA, timeB);
            }
            else {
                n = tmp->del(timeA);
            }
        }
        else {
            n = tmp->del();
        }
        stringstream result;
        result << n;
        return result.str();
    }
    return "-1";
}

string BusSystem::getCodeINS(string& instruction, bool end)
{
    string stored;
    int i = 0;
    while (instruction[i] != ' ' && instruction[i] != '\0') {
        stored.push_back(instruction[i]);
        i++;
    }
    if (!i || (end && instruction[i] != '\0') || (!end && instruction[i] != ' ')) return "-1";
    if (!end) instruction.erase(0, i + 1);
    return stored;
}

string BusSystem::getLPINS(string& instruction, bool end)
{
    string stored;
    int i = 0;
    while (instruction[i] != ' ' && instruction[i] != '\0') {
        stored.push_back(instruction[i]);
        i++;
    }
    if (!i || (end && instruction[i] != '\0') || (!end && instruction[i] != ' ')) return "-1";
    if (!end) instruction.erase(0, i + 1);
    return stored;
}

int BusSystem::getCaseINS(string& instruction, bool end)
{
    if (instruction[0] == ' ') return -1;
    int tmp = (int)instruction[0] - 48;
    if ((tmp != 1 && tmp != 0) || (end && instruction[1] != '\0') || (!end && instruction[1] != ' ')) return -1;
    instruction.erase(0, 2);
    return tmp;
}

int BusSystem::getTime(string& instruction, bool end)
{
    if (instruction[0] == ' ' || !instruction.length() || !checkINT(instruction)) return -1;
    int len = 0;
    int time = stoi(instruction);
    int _time = 0;
    while (instruction[len] != ' ' && instruction[len] != '\0') {
        _time = _time * 10 + ((int)instruction[len] - 48);
        len++;
    }
    if (time != _time) return -1;

    if ((end && instruction[len] != '\0') || (!end && instruction[len] != ' ')) return -1;
    instruction.erase(0, len + 1);
    return time;
}

#endif