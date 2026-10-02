#include <iostream>
#include <string>
#include <array>
#include <ctime>

int crit_count = 0;
int hit_count = 0;
std::array<std::string,4> elements = {"Fire","Water","Earth","Air"};
class bender{
    public:
    std::string name;
    int element_number;
    int HP;
    int Attack;
    int Defense;
    int Speed;
    std::array<std::string,4> moveset;
    std::array<int,4> movepower;
    int max_HP;
    
    bender(std::string a,int b,int c,int d,int e,int f,std::array<std::string,4> g,std::array<int,4> h){
        name=a;element_number=b;HP=c;Attack=d;Defense=e;Speed=f;moveset=g;movepower=h;max_HP = c;
    }
    void display_stats(){
        std::cout << name << " (" << elements[element_number] << ", "<<"HP: "
        <<HP<<"/"<<max_HP<<") ";}
    void display_moves(){
        for(int i = 0; i < 4; i++){
            std::cout << i << ": "<<moveset[i] << "  ";
        }
        std::cout << "\n";

    }    
    
    void attack(bender& opponent, int i){
       // base damage 
       int base_damage =  (Attack * movepower[i])/opponent.Defense;
       // type effectiveness
     
       float type_mul;
       if ((element_number < 3 && opponent.element_number == element_number + 1)||(element_number == 3 && opponent.element_number == 0)){
        type_mul = 0.5;
     
       }
       else if ((element_number > 0  && opponent.element_number == element_number - 1)||(element_number == 0 && opponent.element_number == 3)){
        type_mul = 2;
        
       }
       else type_mul = 1;
       // crtitical hit
       int crit = 1;
       if (rand()%10 == 0) crit *= 2;
       // finally
       int final_damage = base_damage*type_mul*crit;
       opponent.HP -= final_damage;
       //stats
       std::cout << name << " used " << moveset[i] << "!" << "\n";
       if (type_mul == 0.5){
       std::cout<< "Not very effective... (" << elements[element_number] << " is weak against " << elements[opponent.element_number] << ")" << "\n";}
       else if (type_mul == 2){
        hit_count += 1;
        std::cout<< "Super effective! (" << elements[element_number] << " is strong against " << elements[opponent.element_number] << ")" << "\n";
       }
       if (crit == 2) {std::cout << "Critical Hit!" << "\n"; crit_count += 1;}
       std::cout << opponent.name << " took " << final_damage << " damage! " << "\n";
       if(opponent.HP < 0) opponent.HP = 0;
       std::cout << opponent.name << " HP: " << opponent.HP << "/" << opponent.max_HP << "\n"<<"\n";
       

    }
    bool is_fainted(){
        if(HP == 0) {std::cout << name << " fainted!" << "\n" ;return true;}
        else return false;
    }
};   
int duel(bender& one, bender& two, std::string mode) {
    
    std::cout <<"\n" << "=== DUEL BEGINS! ===" << "\n";
       one.display_stats();
    std::cout << "VS  ";
    two.display_stats();
    std::cout << "\n" << "\n";
    int count = 0;
    int move_one;
    int move_two;
    
    while (one.is_fainted()== false && two.is_fainted() == false){
        if (mode == "manual"){
            one.display_moves();
            std::cout << "Number of the move to be used by "<<one.name << ":  ";
            std::cin >> move_one;
            std::cout << "\n" ;
            two.display_moves();
            std::cout << "Number of the move to be used by "<<two.name << ":  ";
            std::cin >> move_two;
            std::cout << "\n" ;}
        else if (mode == "auto") {
            move_one = rand();
            move_two = rand();
        }   
        if (one.Speed > two.Speed){
            count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << one.name << " goes first!" << "   (Speed: "
            << one.Speed << " vs " << two.Speed << ")" << "\n";
            one.attack(two,move_one%4);
            if(two.is_fainted()){std::cout << one.name << " wins the duel! " << "\n"; break;}
                        count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << two.name << " strikes back!" << "\n";
            two.attack(one,move_two%4);
            if(one.is_fainted()){std::cout << two.name << " wins the duel! " << "\n";break;}}
        else if (one.Speed < two.Speed){
                        count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << two.name << " goes first!" << "   (Speed: "
            << two.Speed << " vs " << one.Speed << ")" << "\n";
            two.attack(one,move_two%4);
            if(one.is_fainted()){std::cout << two.name << " wins the duel! " << "\n";break;}
                        count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << one.name << " strikes back!" << "\n";
            one.attack(two,move_one%4);
            if(two.is_fainted()){std::cout << one.name << " wins the duel! " << "\n";break;}
        }
        else{
            std::cout << "Speed Tie! "<<"\n";
            if (rand()%2 == 0){
                            count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << two.name << " goes first!" << "   (Speed: "
            << one.Speed << " vs " << two.Speed << ")" << "\n";
                two.attack(one,move_two%4);
                if(one.is_fainted()) {
                    std::cout << two.name << " wins the duel! "<< "\n";
                     break;}
                            count += 1;
            std::cout << "Turn "<<count<<":  ";     
                std::cout << one.name << " strikes back!" << "\n";     
                one.attack(two,move_one%4);
                if(two.is_fainted()){
                    std::cout << one.name << " wins the duel! " << "\n"; 
                    break;}
                }
                else{
                                count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << one.name << " goes first!" << "   (Speed: "
            << one.Speed << " vs " << two.Speed << ")" << "\n";
                one.attack(two,move_one%4);
                if(two.is_fainted()){std::cout << one.name << " wins the duel! " << "\n"; break;}
                            count += 1;
            std::cout << "Turn "<<count<<":  ";
                std::cout << two.name << " strikes back!" << "\n";
                two.attack(one,move_two%4);
                if(one.is_fainted()) {std::cout << two.name << " wins the duel! " << "\n"; break;}
            }
        }
    }
    std::cout <<"\n" << "Duel Summary: "<<"\n";
    std::string winner;
    if (one.HP > 0) winner = one.name;
    else winner = two.name;
    std::cout << "- Winner: " << winner << "\n";
    std::cout << "- Turns: "<<count << "\n";
    std::cout << "- Critical Hits: " << crit_count << "\n";
    std::cout << "- Super Effective Hits: "<<hit_count << "\n";

}

int main()
{
    srand(time(0));
    

     // create bender Kael and Mira
 
    bender mira = bender("Mira",1,92,50,45,60,{"Water Whip","Tide Push","Mist Veil","Tidal Wave"},{40,30,0,70});
    bender kael = bender("Kael",0,100,58,38,88,{"Ember Slash","Quick Jab","Focus","Flame Surge"},{35,25,0,60});
    bender zephyr = bender("Zephyr",3,20,12,50,95,{"Gust","Wind Slap","Tumble","Cyclone"},{0,18,12,22});
    bender doran = bender("Doran",2,145,80,75,40,{"Boulder Throw","Rock Fist","Tremor","Mountain Crush"},{75,42,48,85});
    bender talon = bender("Talon",3,90,52,55,72,{"Gale Strike","Wind Cutter","Updraft","Cyclone Blast"},{38,28,0,48});
    bender nadia = bender("Nadia",1,85,48,60,72,{"Wave Crash","Splash Kick","Guard","Riptide"},{35,25,0,50});
    
 
    duel(mira,kael,"auto");
    duel(talon,nadia,"manual");

}
