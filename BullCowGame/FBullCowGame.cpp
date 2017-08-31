//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by David Sternheim on 1/25/17.
//  Copyright © 2017 David Sternheim. All rights reserved.
//

#pragma once
#include "FBullCowGame.hpp"
#include <map>
#define TMAP std::map

using int32 = int;
using FString=std::string;

FBullCowGame::FBullCowGame(){
    Reset();
}

void FBullCowGame::Reset(){
    constexpr int32 MAX_TRIES=8;
    maxTries=MAX_TRIES;
    
    //If you want to edit the word change the value of the constant here
    const FString HIDDEN_WORD="diner";
    hiddenWord=HIDDEN_WORD;
    
    currentTry=1;
    return;
}

int32 FBullCowGame::GetMaxTries() const{
    return maxTries;
}

int32 FBullCowGame::GetCurrentTry()const{
    return currentTry;
}

bool FBullCowGame::IsGameWon(FString guess){
    if(guess==hiddenWord){
        bGameIsWon=true;
        return true;
    }else{
        bGameIsWon=false;
        return false;
    }
}

EWordStatus FBullCowGame::IsValidGuess(FString guess) const{
    if(!isIsogram(guess)){
        return EWordStatus::NOT_ISOGRAM;
    }else if (!IsLowerCase(guess)){
        return EWordStatus::NOT_LOWERCASE;
    }else if (guess.length()!=hiddenWord.length()){
        return EWordStatus::WRONG_LENGTH;
    }else
        return EWordStatus::OK;
}

int32 FBullCowGame::GetHiddenWordLength() const{
    return hiddenWord.length();
}

FBullCowCount FBullCowGame::SubmitGuess(FString guess){
    currentTry++;
    
    FBullCowCount bullCowCount;
    
    for(int32 i=0; i<hiddenWord.length();i++){
        for (int32 j=0; j<hiddenWord.length(); j++) {
            if(guess[i]==hiddenWord[j]){
                if (i==j) {
                    bullCowCount.bulls++;
                }else
                    bullCowCount.cows++;
            }
        }
    }
    return bullCowCount;
}

bool FBullCowGame::isIsogram(FString guess) const{
    if (guess.length()<=1) {
        return true;
    }
    
    TMAP<char, bool> LetterSeen;
    for(auto letter:guess){
        letter=tolower(letter);
        if(LetterSeen[letter]==true){
            return false;
        }else
            return true;
    }
    return true;
}

bool FBullCowGame::IsLowerCase(FString guess) const{
    for(auto letter:guess){
        if(!islower(letter))
            return false;
    }
    
    return true;
}
