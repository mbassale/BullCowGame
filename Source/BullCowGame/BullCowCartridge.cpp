// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    ClearScreen();
    SetupGame();
    PrintLine(TEXT("Words Number: %i"), Words.Num());
    for (FString Word : Words) 
    {
        PrintLine(TEXT("Word: %s"), *Word);
    }
    PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord);
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows."));
    PrintLine(TEXT("Marco Bassaletti UE4 Demo."));

    HiddenWord = Words[FMath::RandRange(0, Words.Num() - 1)];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letters word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i Lives"), Lives);
    PrintLine(TEXT("Press WASD and your mouse to explore this level."));
    PrintLine(TEXT("Press enter to activate console and type guesses."));
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

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
        return;
    }
    if (!IsIsogram(HiddenWord)) 
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }
    
    --Lives;
    if (Lives <= 0)
    {
        EndGame();
        return;
    }
    int32 Bulls, Cows;
    GetBullCows(Guess, Bulls, Cows);
    PrintLine(TEXT("Sorry, try again! You have %i Bulls and %i Cows."), Bulls, Cows);
    PrintLine(TEXT("You have %i lives remaining."), Lives);
}

void UBullCowCartridge::EndGame()
{
    if (Lives <= 0) 
    {
        PrintLine(TEXT("Game over!."));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
    }
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount = 0;
    CowCount = 0;
    for (int32 i = 0; i < Guess.Len(); i++)
    {
        if (Guess[i] == HiddenWord[i])
        {
            BullCount++;
            continue;
        }
        for (int32 j = 0; j < HiddenWord.Len(); j++)
        {
            if (Guess[i] == HiddenWord[j])
            {
                CowCount++;
            }
        }
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 i = 0; i < Word.Len() - 1; i++)
    {
        for (int32 j = i + 1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])
            {
                return false;
            }
        }
    }
    return true;
}