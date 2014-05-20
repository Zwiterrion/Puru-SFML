#include "GameView.h"
#include "GameModel.h"
#include "Const.h"
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <iostream>

using namespace std;

int main()
{
    srand((unsigned) time(NULL));
    GameModel *model = new GameModel();
    GameView *view = new GameView(1024,768,32);
    view->setModel(model);
    view->treatEvents();
    //view->Test();
    delete view;
    delete model;
    
    return EXIT_SUCCESS;
}
