//
//  main.cpp
//  BullCowGame
//
//  Created by David Sternheim on 1/24/17.
//  Copyright © 2017 David Sternheim. All rights reserved.
//
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FString= std::string;
using int32= int;

void PrintIntro();
void PlayGame();
FString GetUserGuess();
bool AskToPlayAgain();
void PrintGameSummary(bool);

FBullCowGame BCGame;

int main(void){
    
    do{
        //Game introduction
        PrintIntro();
        
        //Gameplay
        PlayGame();
    }while (AskToPlayAgain());
}


void PrintIntro(){
    std::cout<<"Welcome to Bull and Cow Game, a fun word game!\n";
    std::cout<<"Can you guess the "<<BCGame.GetHiddenWordLength()
    <<" letter isogram I'm thinking of?\n";
    std::cout<<std::endl;
    return;
}

void PlayGame(){
    int32 maxTries = BCGame.GetMaxTries();
    BCGame.Reset();
    FString userGuess;
    bool bIsGameWon=false;
    while (!BCGame.IsGameWon(userGuess) && BCGame.GetCurrentTry()<=maxTries) {
        userGuess=GetUserGuess();
        if(BCGame.IsGameWon(userGuess)){
            bIsGameWon=true;
        }
        std::cout<<"Your guess was: "<<userGuess<<std::endl;
        FBullCowCount bullCowCount=BCGame.SubmitGuess(userGuess);
        std::cout<<"Bulls= "<<bullCowCount.bulls;
        std::cout<<" Cows= "<<bullCowCount.cows<<std::endl;
        std::cout<<std::endl;
    }
    PrintGameSummary(bIsGameWon);
    return;
}

void PrintGameSummary(bool bIsGameWon){
    if(bIsGameWon){
        std::cout<<"You Won!"<<std::endl;
    }else
        std::cout<<"You Lost"<<std::endl;
}

FString GetUserGuess(){
    EWordStatus status;
    FString guess="";
    do{
        int32 currentTry = BCGame.GetCurrentTry();
        std::cout<<"Try "<<currentTry<<"/"<<BCGame.GetMaxTries();
        std::cout<<": Enter your guess here: ";
        getline(std::cin,guess);
        status = BCGame.IsValidGuess(guess);
        switch (status) {
            case EWordStatus::NOT_LOWERCASE:
                std::cout<<"Enter an isogram with only lowercase letters\n";
                break;
            case EWordStatus::NOT_ISOGRAM:
                std::cout<<"Enter an isogram\n\n";
                break;
            case EWordStatus::WRONG_LENGTH:
                std::cout<<"Enter a word with the same length as the hidden word\n\n";
                break;
            default:
                break;
        }
    }while (status!=OK);
    return guess;
}

bool AskToPlayAgain(){
    std::cout<<"Would you like to play again? (y/n)"<<std::endl;
    FString response = "";
    getline(std::cin,response);
    if(response[0]=='y' || response[0]=='Y')
        return true;
    else
        return false;
}
