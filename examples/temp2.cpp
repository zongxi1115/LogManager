#include "log_manager.h"
#include <iostream>
using namespace std;
int main()
{
    LogManager &manager = LogManager::getInstance();
    auto old_historys = manager.getHistorys(Level::INFO);
    for(auto hist: old_historys){
        cout << hist.parse() << endl;
    }
    return 0;
}