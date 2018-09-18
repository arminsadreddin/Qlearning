#include <QCoreApplication>
#include <iostream>
using namespace std;
struct node{
    double up;
    double right;
    double down;
    double left;
    double value;
};
char M_map[5][5]={
    {' ','#',' ','#',' '},
    {' ',' ',' ',' ','#'},
    {' ',' ','#',' ',' '},
    {' ',' ',' ',' ',' '},
    {' ',' ',' ','#','G'}};
node stateAction[5][5];
int myX = 0;
int myY = 0;
double alpha = 0.5;



string random_move();
string best_move();
void update_value();
void initStateActionTable();
void showMap();
void doAct(string action);
double getStateReward(int x , int y);
bool resetGame();


int main()
{
    initStateActionTable();
    cout << "here"<<endl;
    for(int e = 0 ; e < 1000 ; e++){
        while(!resetGame()){
            int r = rand()%100;
            if(r >= alpha*100){
                string action = best_move();
                //cout << action<<endl;
                doAct(action);
                update_value();
            }
            else{
                string action = random_move();
                //cout << action<<endl;
                doAct(action);
                update_value();
            }
        }
        myX = 0;
        myY = 0;
    }
    //cout << stateAction[0][0].up<<endl;
    //cout << stateAction[0][0].right<<endl;
    //cout << stateAction[0][0].down<<endl;
    //cout << stateAction[0][0].left<<endl;

    while(!resetGame()){
        string action = best_move();
        doAct(action);
        cout << action << endl;
        update_value();
        //showMap();
        cout << endl;
    }

    return 0;
}
void showMap(){
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            if(i == myX && j == myY){
                cout << "@";
            }
            else{
                cout<<M_map[i][j];
            }
        }
        cout << endl;
    }
}
string random_move(){
    vector<string> ways;
    ways.clear();
    ways.push_back("UP");
    ways.push_back("RIGHT");
    ways.push_back("DOWN");
    ways.push_back("LEFT");
    int index = rand()%ways.size();
    return ways.at(index);
}
string best_move(){
    double maxValue = stateAction[myX][myY].value;
    vector<string> ways;
    ways.clear();
    if(stateAction[myX][myY].up == maxValue){
        ways.push_back("UP");
    }
    if(stateAction[myX][myY].right == maxValue){
        ways.push_back("RIGHT");
    }
    if(stateAction[myX][myY].down == maxValue){
        ways.push_back("DOWN");
    }
    if(stateAction[myX][myY].left == maxValue){
        ways.push_back("LEFT");
    }

    int index = rand()%ways.size();
    return ways.at(index);
}
void update_value(){
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            stateAction[i][j].value = max(stateAction[i][j].up , max(stateAction[i][j].right , max(stateAction[i][j].down , stateAction[i][j].left)));
        }
    }
}
void initStateActionTable(){
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            node tmp;
            tmp.up = 0.0;
            tmp.right=0.0;
            tmp.down=0.0;
            tmp.left=0.0;
            tmp.value=0.0;
            stateAction[i][j]=tmp;
        }
    }
}
void doAct(string action){
    if(action == "UP"){
        //cout << "UP";
        myX--;
        if(myX < 0){
            stateAction[myX+1][myY].up = -10;
        }
        else{
            stateAction[myX+1][myY].up = stateAction[myX][myY].value + getStateReward(myX , myY) - 0.04;
        }

    }
    if(action == "RIGHT"){
        //cout << "RIGHT";
        myY++;
        if(myY > 4){
            stateAction[myX][myY-1].right = -10;
        }
        else{
            stateAction[myX][myY-1].right = stateAction[myX][myY].value + getStateReward(myX , myY) - 0.04;
        }
    }
    if(action == "DOWN"){
        //cout << "DOWN";
        myX++;
        if(myX > 4){
            stateAction[myX-1][myY].down= -10;
        }
        else{
            stateAction[myX-1][myY].down = stateAction[myX][myY].value + getStateReward(myX , myY) - 0.04;
        }
    }
    if(action == "LEFT"){
        //cout << "LEFT";
        myY--;
        if(myY < 0){
            stateAction[myX][myY+1].left = -10;
        }
        else{
            stateAction[myX][myY+1].left = stateAction[myX][myY].value + getStateReward(myX , myY) - 0.04;
        }
    }
}
double getStateReward(int x , int y){
    char data = M_map[x][y];
    if(data == '#'){
        return -10;
    }
    if(data == 'G'){
        return +10;
    }
    return 0.0;
}
bool resetGame(){
    char data = M_map[myX][myY];
    if(data == '#'){
        return true;
    }
    if(data == 'G'){
        return true;
    }
    if(myX < 0){
        return true;
    }
    if(myY < 0){
        return true;
    }
    if(myX > 4){
        return true;
    }
    if(myY > 4){
        return true;
    }
    return false;
}






