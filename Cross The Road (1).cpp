#include <iostream>
#include <deque>
#include <vector>
#include <conio.h>
#include <time.h>
#include <iomanip>

int cmode = 0, D, z = 3, score = 0, scoreprev = 0;  bool quit = false;// #enhancements;  
double time1 = 0, time2 = 0;   clock_t S, E, Q, W;  //#execution time

using namespace std;
class cPlayer
{
public:
    int x, y; // position of the player(x,y)
    cPlayer(int width) { x = width / 2; y = 0; } // player constructor
};
class cLane
{
private:
    deque<bool> cars;
    bool right;
public:
    cLane(int width)
    {
        for (int i = 0; i < width; i++)
            cars.push_front(true);
        right = rand() % 2;
    }
    void Move()   // this is for random movement of the cars
    {
        if (right)
        {
            if (rand() % 5 == 1) //*
                cars.push_front(true);
            else
                cars.push_front(false);
            cars.pop_back(); // remove from back of deque
        }
        else
        {
            if (rand() % 5 == 1)//*
                cars.push_back(true);
            else
                cars.push_back(false);
            cars.pop_front(); //remove from front of deque
        }

    }
    bool CheckPos(int pos) { return cars[pos]; }
    void ChangeDirection() { right = !right; }
};
class cGame
{
private:
    int numberOfLanes;
    int width;
    cPlayer* player;
    vector<cLane*> map;
public:
    cGame(int w = 20, int h = 10)
    {
        numberOfLanes = h;
        width = w;
        quit = false;
        for (int i = 0; i < numberOfLanes; i++)
            map.push_back(new cLane(width));
        player = new cPlayer(width);
    }
    ~cGame() // constructor to free the memory that we allocated
    {
        delete player;
        for (int i = 0; i < map.size(); i++)
        {
            cLane* current = map.back();
            map.pop_back();
            delete current;
        }
    }
    void Draw()
    {
        system("cls");
        for (int i = 0; i < numberOfLanes; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i == 0 && (j == 0 || j == width - 1)) cout << "S"; // refers to the start of the game
                if (i == numberOfLanes - 1 && (j == 0 || j == width - 1)) cout << "F"; // refers to the end of the game
                if (map[i]->CheckPos(j) && i != 0 && i != numberOfLanes - 1)
                    cout << "#"; // car symbol in the game (it will not appear in the fist lane or finish lane)
                else if (player->x == j && player->y == i)
                    cout << "V"; // player symbol
                else
                    cout << " ";
            }
            cout << endl;
        }
        cout << "Score: " << score << endl;
    }
    void Input()   // game controllers
    {
        S = clock();
        if (_kbhit()) //determine if a key has been pressed or not
        {
            char current = _getch();
            if (current == 'a')
                player->x--;
            if (current == 'd')
                player->x++;
            if (current == 'w')
                player->y--;
            if (current == 's')
                player->y++;
            if (current == 'q')
                quit = true;  // to end the game
        }

        E = clock();
        time1 += (E - S) / double(CLOCKS_PER_SEC);
    }

    void Logic()  // how the game should work
    {
        scoreprev = score;
        for (int i = 1; i < numberOfLanes - 1; i++)
        {
            if (rand() % 10 == 1)
                map[i]->Move();
            if (map[i]->CheckPos(player->x) && player->y == i) // losing condition
                quit = true;
        }
        if ((player->x + 1) > width - 1)
            quit = true;
        else if (player->x == 0)
            quit = true;
        if (player->y == numberOfLanes - 1)
        {
            score++;
            player->y = 0; // go back to the begining
            cout << "\x07"; // release a sound on computer
            map[rand() % numberOfLanes]->ChangeDirection();
        }
    }
    void Run()
    {
        W = clock();
        while (!quit)
        {
            Input();
            Draw();
            Logic();
            if ((score - scoreprev == 1) && (cmode == 1)) break;
        }
        Q = clock();
        time2 = ((Q - W) / double(CLOCKS_PER_SEC));
        return;

    }
};
int main()
{
begin:
    int v, c, n;
    clock_t start, mid, after, end;
    start = clock();
    srand(time(NULL));
    cout << "Welcome, choose complexity \n\n" << endl;
    cout << "1__> EASY[const] \n\n\n";
    cout << "2__> MEDUIM[const] \n\n\n";
    cout << "3__> HARD[const] \n\n\n";
    cout << "4__>challenge[ GAME GETS HARDER EACH WIN]\n\n\n";
    mid = clock();
choice:
    cin >> n;
    if (!cin) // user didn't input a number
    {
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   //skip bad input
        cout << "ERROR!! ENTER A VALID CHOISE \n";
        goto choice;
    }
    if (n == 1) { v = 20; c = 5; }
    else
        if (n == 2) { v = 30; c = 8; }
        else
            if (n == 3) { v = 40; c = 10; }
            else
                if (n == 4) {
                    cmode = 1;// challenge mode is on
                    v = 20; c = 5; // first challenge 
                }
                else
                {
                    cout << "ERROR!! ENTER A VALID CHOISE [between 1 and 4 ]\n";
                    goto choice;
                }
    after = clock();
    if (cmode) {
      challengemode:
        cGame game(30, z + 2);
        if (score == 0)
            end = clock();
        game.Run();
        if (quit == false) {
            z++;
            goto challengemode;
        }
        cout << "Game over!\n\n" << endl;
        cout << "TRY AGAIN->1\n";
        cout << "EXIT->press any other key\n\n";
        cin >> D;
        if ((!cin) || (D != 1))
        {
            double time_taken = double((mid - start) +  (time2 - time1)) / double(CLOCKS_PER_SEC);
            cout << "Time taken by program is : " << fixed
                << time_taken;
            cout << " sec " << endl;
            return 0;
        }
        else {
            system("cls");
            cmode = 0, z = 3, score = 0, scoreprev = 0;  quit = false;
            time1 = 0, time2 = 0;  S = 0, E = 0, Q = 0, W = 0;
            start = 0, mid = 0;
            goto begin;
        }   }
    else {
        const int b = v, m = c;
        cGame game(b, m);
        game.Run();
        cout << "Game over!" << endl;
        cout << "TRY AGAIN->1\n";
        cout << "EXIT->press any other key\n\n";
        cin >> D;
        if ((!cin) || (D != 1))
        {
            double time_taken = double((mid - start) + (time2 - time1)) / double(CLOCKS_PER_SEC);
            cout << "Time taken by program is : " << fixed
                << time_taken;
            cout << " sec " << endl;
            return 0;
        }

        else {
            system("cls");
            cmode = 0, z = 3, score = 0, scoreprev = 0;  quit = false;
            start = 0, mid = 0;
            time1 = 0, time2 = 0;  S = 0, E = 0, Q = 0, W = 0;
            goto begin;
        }
    }
    return 0;

}
