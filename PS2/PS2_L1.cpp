#include <iostream>
#include <string>
#include <array>

class bender{
    public:
    std::string name;
    std::string element;
    int HP;
    int Attack;
    int Defense;
    int Speed;
    std::array<std::string,4> moveset;
    std::array<int,4> movepower;
    int max_HP;
    
    bender(std::string a,std::string b,int c,int d,int e,int f,std::array<std::string,4> g,std::array<int,4> h){
        name=a;element=b;HP=c;Attack=d;Defense=e;Speed=f;moveset=g;movepower=h;max_HP = c;
    }
    void display_stats(){
        std::cout << name << " (" << element << ")  "<<"HP: "
        <<HP<<"/"<<max_HP<<", Attack: "<<Attack<<", Defense: "<<Defense<<", Speed: "
        <<Speed<<"\n";
        std::cout<<"Moves: "<<moveset[0]<<" ("<<movepower[0]<<"), "
        <<moveset[1]<<" ("<<movepower[1]<<"), "
        <<moveset[2]<<" ("<<movepower[2]<<"), "
        <<moveset[3]<<" ("<<movepower[3]<<"), "<<"\n"<<"\n";
    }
    int attack(bender& opponent, int i){
       int damage =  (Attack * movepower[i])/opponent.Defense;
       opponent.HP -= damage;
       if(opponent.HP < 0) opponent.HP = 0;
       return damage;
    }
    bool is_fainted(){
        if(HP == 0) return true;
        else return false;
    }
};    
int main(){
    int damage;
    // create bender Kael and Mira
    std::cout << "Mira vs Kael!"<< "\n" << "\n";
    bender mira = bender("Mira","Water",92,50,45,60,{"Water Whip","Tide Push","Mist Veil","Tidal Wave"},{40,30,0,70});
    bender kael = bender("Kael","Fire",100,58,38,88,{"Ember Slash","Quick Jab","Focus","Flame Surge"},{35,25,0,60});
    
    kael.display_stats();
    mira.display_stats();
    
    damage = kael.attack(mira,0);
    std::cout << kael.name << " used "<< kael.moveset[0] <<"!" << "\n";
    std::cout << mira.name << " took "<< damage << " damage!"<< "\n"<<"\n";

    mira.display_stats();

    std::cout << mira.name <<" fainted: "<<  std::boolalpha<< mira.is_fainted()<<"\n"<<"\n";
    
    // create bender Zephyr and Doran
    std::cout << "Zephyr vs Doran!" << "\n" << "\n";
    bender zephyr = bender("Zephyr","Air",20,12,50,95,{"Gust","Wind Slap","Tumble","Cyclone"},{0,18,12,22});
    bender doran = bender("Doran","Earth",145,80,75,40,{"Boulder Throw","Rock Fist","Tremor","Mountain Crush"},{75,42,48,85});
    
    zephyr.display_stats();
    doran.display_stats();
    
    damage = doran.attack(zephyr,0);
    std::cout << doran.name << " used "<< doran.moveset[0] <<"!" << "\n";
    std::cout << zephyr.name << " took "<< damage << " damage!"<< "\n";

    zephyr.display_stats();
    
    std::cout << zephyr.name <<" fainted: "<<  std::boolalpha<< zephyr.is_fainted()<<"\n"<<"\n";
}    


