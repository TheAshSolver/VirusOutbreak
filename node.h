#include<vector>

class Node{

    public:
        double x, y;
        int time_left;
        bool dead;
        bool infected; 
        bool saved;
        Node(double _x,double _y,int _time_left, bool _dead, bool _infected, bool _saved): x(_x), y(_y), dead(_dead), time_left(_time_left), infected(_infected), saved(_saved){}
        bool operator==(const Node &other) const= default;
};