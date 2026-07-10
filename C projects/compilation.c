// 
//created to be one of many web applications
//Note: a)rewrite the code in a different language. ex: JS b) combine different codes like this into a master code (in C) 
// make a menu to ask the user which one they what they would like to do
//19-11-2024

#include <stdio.h>
#include <string.h>

int main(){

//Program to convert a comma seperated list of items into a vertical bullet list 
    int n;
    printf("Paste your comma seperated list(maximum limit=1000 characters)");
    char str[1000];
    fgets(str, 1000, stdin);
    char* token = (str, ",");
    while (token != NULL) {
printf(" % s\n", token);
token = strtok(NULL, ",");
}

//tell the meaning of the error
scanf("%d", n);
printf("%s/n", strerror(n));

//find and replace all instances of a word/character in a block of text


return 0;
}

