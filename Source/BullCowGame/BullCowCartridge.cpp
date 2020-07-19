// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    ClearScreen();
    SetupGame();
    PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord);
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows."));
    PrintLine(TEXT("Marco Bassaletti UE4 Demo."));

    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letters word!"), HiddenWord.Len());
    PrintLine(TEXT("Press tab to activate terminal and type guesses."));
}


void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // if game is over, reset game
    if (bGameOver) 
    {
        ClearScreen();
        SetupGame();
    } 
    else {
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You have Won!"));
            EndGame();
        }
        else
        {
            if (Input.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
            }
            else 
            {
                PrintLine(TEXT("Wrong Guess. Try again!"));
            }
            --Lives;
            if (Lives == 0)
            {
                PrintLine(TEXT("You have lost!."));
                EndGame();
            }
            else 
            {
                PrintLine(TEXT("Lives Left: %i"), Lives);
            }
        }
    }
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}