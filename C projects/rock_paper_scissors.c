// Rock Paper Scissors game

#include <stdio.h>
#include <stdlib.h>

/* aditional features:
 - create a func for the code and create multiple rounds
 - include a menu from which user can chose from different games
 - in game menus for- click 1 to know the rules, etc
*/

int main()
{
    //user's move
    char user[8];
    printf("Hello!\nLet's play Rock, Paper, Scissors");
    scanf("Type Rock, Paper or Scissors/nYour move: %s", &user);
    return 0;

    //calculating the computer's move
    int i, n;
    char comp[8];
    char options[3]={'R','P','S'};
    n = rand() % 3; // to ensure that the random index lies within the 
    int length = sizeof ()
    
    //generate random number and store it in i
    
    //computer's move
    printf("My move:%s", comp);
    
    //calculating the winner
    char winner[];
    char no_one;

    if (user==comp){
        winner=no_one;
    }
    if ((user=="Rock" && comp=="Scissors") || (user=="Paper" && comp=="Rock") || (user=="Scissors" && comp=="Paper"))
    {
        winner=user;
    }
    if (user=="Rock" && comp=="Paper") || (user==Paper && comp==Rock) || (user==Scissors && comp==Paper))
    {
        winner=comp;
    }
    
    printf("%s vs %s:\n %s wins!", user, comp, winner);


    

    //winner declaration
    if (winner==user){
        printf("You win! :)/nWay to go!");
    }
    if (winner==comp){
        printf("You lose! :(/nBetter Luck next time");
    }
    if (winner==tie){
        printf("it's a tie!");
    }
}

