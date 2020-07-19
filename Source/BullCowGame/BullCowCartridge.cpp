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
    PrintLine(TEXT("You have %i Lives"), Lives);
    PrintLine(TEXT("Press WASD and your mouse to explore this level."));
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
    else 
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
    }
    else
    {
        --Lives;
        if (Lives > 0) {
            if (Guess.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
            }
            else
            {
                PrintLine(TEXT("Sorry, try again!"));
            }
            PrintLine(TEXT("You have %i lives remaining."), Lives);
        }
        else
        {
            PrintLine(TEXT("You have lost!."));
            EndGame();
        }
    }
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}