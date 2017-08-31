//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by David Sternheim on 1/25/17.
//  Copyright © 2017 David Sternheim. All rights reserved.
//
#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp
#include <string>
#include <stdio.h>
using FString=std::string;
using int32=int;
#endif /* FBullCowGame_hpp */

struct FBullCowCount{
    int32 bulls=0;
    int32 cows=0;
};

enum EWordStatus{
    OK,
    NOT_ISOGRAM,
    WRONG_LENGTH,
    NOT_LOWERCASE   
};

class FBullCowGame{

public:
    FBullCowGame();
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon(FString);
    
    void Reset(); //TODO change return value
    EWordStatus IsValidGuess(FString) const;
    FBullCowCount SubmitGuess(FString);
    
private:
    int32 currentTry;
    int32 maxTries;
    FString hiddenWord;
    bool bGameIsWon;
    
    bool IsLowerCase(FString) const;
    bool isIsogram(FString) const;
};
