#include<iostream>
#include<vector>
#include "node.h"
#include<queue>
#include<algorithm>
#include<execution>
#include<cmath>
#include<array>
#include<random>

const double CONSTANT= -6;
const double INFECTION_RATE = 1.0;
const int OG_TIME = 5;
const double SURVIVAL_RATE = 0.7;
const int GENERATIONS = 1000;

void simulate_one_generation(std::vector<Node*> &infected, std::vector<Node*> &nodes, std::vector<Node> &deads, std::vector<Node> &saved){
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> unif(0.0, 1.0);
    std::vector<Node*> new_infected;
    std::vector<Node*> remaining;
    auto end = infected.end();
    std::for_each(std::execution::seq, infected.begin(), end, [&](Node* node){
        for(Node* normal_node:nodes){
            if(normal_node->infected==true|| normal_node->dead==true|| normal_node->saved==true){
                continue;
            }
            else{
                double number = unif(engine);
                double threshold = std::exp(CONSTANT * std::sqrt((normal_node->x-node->x)*(normal_node->x-node->x)+(normal_node->y-node->y)*(normal_node->y-node->y)));
                if(number<threshold){
                    number = unif(engine);
                    if(number<INFECTION_RATE){
                        normal_node->infected = 1;
                        normal_node->time_left = OG_TIME;
                        new_infected.push_back(normal_node); 
                    }
                }

            }
        }
    });
    std::for_each(infected.begin(), infected.end(), [&](Node* node){
            node->time_left--;
            if(!node->time_left){
                double survival_number = unif(engine);  
                if(survival_number<SURVIVAL_RATE){
                    node->infected=false;
                    node->saved=true;
                    saved.push_back(*node);
                }
                else{
                    node->dead=true;
                    deads.push_back(*node);
                    
                } 
            }
            else{
                remaining.push_back(node);
            }
    });
    infected.clear();
    infected.insert(infected.end(), remaining.begin(), remaining.end());
    infected.insert(infected.end(), new_infected.begin(), new_infected.end());


}

void simulate(std::vector<Node*> infected, std::vector<Node*> &nodes){
    std::vector<Node> dead;
    std::vector<Node> saved;
    for(int i =0;i<GENERATIONS;i++){
        std::cout<<"day"<<std::endl;
        simulate_one_generation(infected, nodes, dead, saved);   
        std::cout<< i<< " "<< infected.size()<< " "<< dead.size()<< " " << saved.size()<<  std::endl;
    }

}






int main(){
    std::random_device rand;
    std::mt19937 gen(rand());
    std::normal_distribution<double> normal(0, 5.5);
    std::uniform_real_distribution<double> unif(0,1);
    std::vector<Node*> nodes;
    std::vector<Node*> infected_nodes;
    for(int i =0;i<10000;i++){
        double x = normal(gen);
        double y = normal(gen);
        double uniform = unif(gen);
        bool infected = false;
        if(uniform<0.01){
            infected= true;
        }
        auto node =new Node(x,y,5, false, infected, false);
        nodes.push_back(node);
        if(infected){
            infected_nodes.push_back(node);
        }
    }
    simulate(infected_nodes, nodes);




    return 0;
}
