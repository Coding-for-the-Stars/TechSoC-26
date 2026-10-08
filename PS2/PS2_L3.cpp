#include <iostream>
#include <string>
#include <array>
#include <ctime>
#include <vector>

    int turn = 0;
    int battle = 0;
    int crit = 0;
    int hit = 0;

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
    std::array<std::string,4> move_effect;
    std::string status = "";
    int frozen_count = 0;
    int burn_count = 0;
    int bury_count = 0;
    bool go = true;
    int ai_handle = 0;
    int move = 0;
   

    bender(std::string a,int b,int c,int d,int e,int f,std::array<std::string,4> g,std::array<int,4> h,std::array<std::string,4> i){
        name=a;element_number=b;HP=c;Attack=d;Defense=e;Speed=f;moveset=g;movepower=h;move_effect = i;max_HP = c;
    }
    int max(){
      int max_pow = 0;
    for(int i = 0; i < 4; i++){
        if (movepower[i] > movepower[0]){
            max_pow = i;
        }
        }
        return max_pow;}
    void display_stats(){
        std::cout << name << " (" << elements[element_number] << ", "<<"HP: "
        <<HP<<"/"<<max_HP<<") ";}
    void display_moves(){
        for(int i = 0; i < 4; i++){
            std::cout << i << ": "<<moveset[i] << "  ";
        }
        std::cout << "\n";

    }    
    bool has_status_move(){
        for(std::string name: move_effect){
            if(name != ""){
                return true;
            }}
        return false;
        
    }
    int healing_move(){
        for(int i = 0; i < 4; i++){
            if(moveset[i] == "Healing Wind"){
                return i;
            }
        }
        return -1;
    }
    
    
    void attack(bender& opponent, int i, int& crit_count, int& hit_count ){
        if ( ai_handle == 1) std::cout << "AI Analysis: Choosing a random move! " << "\n";
        else if ( ai_handle == 2) std::cout << "AI Analysis: Choosing the strongest move! " << "\n";
        if (status == "frozen") {
                frozen_count -= 1;
                std::cout << status << " duration: "<<frozen_count << " turns remaining." << "\n" ;
                if (rand()%2 == 0)   {
                go = false;
                std::cout << name << " is frozen solid and therefore cannot move! "<<"\n"<<"\n";}
                if (frozen_count == 0){
                    std::cout << "The ice thawed!" << "\n";
                    status = "";}
            }
        if (status == "buried")  {
            bury_count -=  1;
            std::cout << status << " duration: "<<bury_count << " turns remaining." << "\n" ;
            go = false;
            std::cout << name << " is buried and therfore cannot move! "<<"\n"<<"\n";
            if (bury_count == 0){
                std::cout << "The ground collapsed! "<<"\n";
                status = "";
            }
        }  
        if (go == true){
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
       if(moveset[i] == "Healing Wind"){
        HP += max_HP/2;
        std::cout << name << " recovered " << max_HP/2 << " HP!" << "\n";
        
        std::cout << "\n" << "\n";
       }
       if (move_effect[i] == "frozen"){
        opponent.status = move_effect[i];
        opponent.frozen_count = 3;
        std::cout << opponent.name << " is now frozen! "<<"("<<opponent.frozen_count<<" turns remaining)" << "\n" << "\n";}
       if (move_effect[i] == "burn"){
        opponent.status = move_effect[i];
        opponent.burn_count = 4;
        std::cout << opponent.name << " is now burnt! "<<"("<<opponent.burn_count<<" turns remaining)" << "\n" << "\n";        
       }
       if (move_effect[i] == "buried"){
        opponent.status = move_effect[i];
        opponent.bury_count = (rand()%3) + 2;
        std::cout << opponent.name << " is now buried underground! "<<"("<<opponent.bury_count<<" turns remaining)" <<"\n" << "\n";        
       }
       
       
       if (status == "burn"){
        burn_count -= 1;
        std::cout << status << " duration: "<<burn_count << " turns remaining." << "\n" ;

        HP -= max_HP/10;
        std::cout << name << " took "<< max_HP/10 << " burn damage!" << "\n"<<"\n";
        if (burn_count == 0) {status = "";
        std::cout << "The burn went away!" << "\n";}
        if (HP <= 0) HP = 0;
        display_stats();
         std::cout << "\n"<<"\n";}
        
       }
       
    go = true;
    }
    bool is_fainted(){
        if(HP == 0) {std::cout << name << " fainted!" << "\n" ;return true;}
        else return false;
    }
};   

void move_choose(bender& player, bender& opponent){
    if (player.ai_handle == 0){
            player.display_moves();
            std::cout << "Number of the move to be used by "<<player.name << ":  ";
            std::cin >> player.move;
            std::cout << "\n" ;}
    else if (player.ai_handle == 1){
        player.move = rand();
    }    
    else if (player.ai_handle == 2){

        player.move = player.max();
    }    
    else if (player.ai_handle == 3){
        if ((player.HP < 0.5 * player.max_HP)&& (player.healing_move() != -1)){
            player.move = player.healing_move();
            
        }
        else if ((opponent.HP > 0.7 * opponent.max_HP) && (player.has_status_move()) && (opponent.status == "")){
            for(int i = 0; i < 4; i++){
                if ( player.move_effect[i] != ""){
                    player.move = i;
                    break;
                }
                
            }
            

        }
        else player.move = player.max();
    }

}

bender duel(bender& one, bender& two, int ai_one, int ai_two , int& turn, int& battle, int& crit, int& hit ) {
    int crit_count = 0;
    int hit_count = 0;
    one.ai_handle = ai_one;
    two.ai_handle = ai_two;
    std::cout <<"\n" << "=== DUEL BEGINS! ===" << "\n";
       one.display_stats();
    std::cout << "VS  ";
    two.display_stats();
    std::cout << "\n" << "\n";
    int count = 0;

    
    while (one.is_fainted()== false && two.is_fainted() == false){
        move_choose(one,two);
        move_choose(two,one);
        if (one.Speed > two.Speed){
            count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << one.name << " goes first!" << "   (Speed: "
            << one.Speed << " vs " << two.Speed << ")" << "\n";

            one.attack(two,one.move%4,crit_count,hit_count);
            if(two.is_fainted()){std::cout << one.name << " wins the duel! " << "\n"; break;}
                        count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << two.name << " strikes back!" << "\n";
            two.attack(one,two.move%4,crit_count,hit_count);
            if(one.is_fainted()){std::cout << two.name << " wins the duel! " << "\n";break;}}
        else if (one.Speed < two.Speed){
                        count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << two.name << " goes first!" << "   (Speed: "
            << two.Speed << " vs " << one.Speed << ")" << "\n";
            two.attack(one,two.move%4,crit_count,hit_count);
            if(one.is_fainted()){std::cout << two.name << " wins the duel! " << "\n";break;}
                        count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << one.name << " strikes back!" << "\n";
            one.attack(two,one.move%4,crit_count,hit_count);
            if(two.is_fainted()){std::cout << one.name << " wins the duel! " << "\n";break;}
        }
        else{
            std::cout << "Speed Tie! "<<"\n";
            if (rand()%2 == 0){
                            count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << two.name << " goes first!" << "   (Speed: "
            << one.Speed << " vs " << two.Speed << ")" << "\n";
                two.attack(one,two.move%4,crit_count,hit_count);
                if(one.is_fainted()) {
                    std::cout << two.name << " wins the duel! "<< "\n";
                     break;}
                            count += 1;
            std::cout << "Turn "<<count<<":  ";     
                std::cout << one.name << " strikes back!" << "\n";     
                one.attack(two,one.move%4,crit_count,hit_count);
                if(two.is_fainted()){
                    std::cout << one.name << " wins the duel! " << "\n"; 
                    break;}
                }
                else{
                                count += 1;
            std::cout << "Turn "<<count<<":  ";
            std::cout << one.name << " goes first!" << "   (Speed: "
            << one.Speed << " vs " << two.Speed << ")" << "\n";
                one.attack(two,one.move%4,crit_count,hit_count);
                if(two.is_fainted()){std::cout << one.name << " wins the duel! " << "\n"; break;}
                            count += 1;
            std::cout << "Turn "<<count<<":  ";
                std::cout << two.name << " strikes back!" << "\n";
                two.attack(one,two.move%4,crit_count,hit_count);
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
    turn += count;
    crit += crit_count;
    hit += hit_count;
    if (one.HP > 0) return one;
    else return two;
}

void tournament(std::vector<bender>& participants,std::string display){

    int round_count = 0;
    int match_count = 0;

    std::cout << display << "\n";
    std::cout << "Participants: " << participants.size() << "\n" << "\n";

    while (participants.size() > 1){
    match_count = 0;
    round_count += 1;
    std::cout << "\n" << "ROUND " << round_count << "\n"<<"\n";
    std::vector<bender> next_round = {}; 
  
    std::cout << "PLAYERS IN GAME:" << "\n" << "\n";
    for (int i = 0; i < participants.size(); i++){
         
        std::cout << participants[i].name << " ";
        if (i % 2 == 0 ) std::cout << " VS ";
        else std::cout << "\n";
    }
    std::cout << "\n" << "\n";
  
    for(int i = 0; i < participants.size(); i+=2){
        match_count += 1;
        std::cout << "\n" << "MATCH: " << match_count <<"\n";
        next_round.push_back(duel(participants[i],participants[i+1],3,3,turn,battle,crit,hit));}
        
    participants = next_round;
}   
std::cout << "\n" << "=== TOURNAMENT SUMMARY ===" <<"\n"<<"\n";
std::cout << "Champion: " << participants[0].name << "\n";
std::cout << "Total Turns: " << turn << "\n";
std::cout << "Critical Hits: " << crit << "\n";
std::cout << "Super effective hits: " << hit << "\n" << "\n";
std::cout << "FINAL STANDINGS: " << "\n";

    
}

int main()
{
    srand(time(0));


     // create bender Kael and Mira
 
    bender mira = bender("Mira",1,92,50,45,60,{"Water Whip","Tide Push","Mist Veil","Tidal Wave"},{40,30,0,70},{"","","frozen",""});
    bender kael = bender("Kael",0,100,58,38,88,{"Ember Slash","Quick Jab","Ignite","Flame Surge"},{35,25,0,60},{"","","burn",""});
    bender zephyr = bender("Zephyr",3,75,12,50,95,{"Gust","Wind Slap","Tumble","Cyclone"},{0,18,12,22},{"","","",""});
    bender doran = bender("Doran",2,145,80,75,40,{"Boulder Throw","Rock Fist","Underground","Mountain Crush"},{75,0,0,85},{"","","buried",""});
    bender talon = bender("Talon",3,90,52,55,72,{"Gale Strike","Wind Cutter","Healing Wind","Cyclone Blast"},{38,28,0,48},{"","","",""});
    bender nadia = bender("Nadia",1,85,48,60,72,{"Wave Crash","Splash Kick","Guard","Riptide"},{35,25,0,50},{"","","",""});
    
    std::vector<bender> participants = {mira,kael,talon,nadia,doran,zephyr,kael,zephyr}; 
    tournament(participants, "TOURNEY STARTS TODAY!");
    //duel(nadia,talon,3,3,turn,battle,crit,hit);
    

}
