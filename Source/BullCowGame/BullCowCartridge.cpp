// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    ClearScreen();
    PrintLine(TEXT("Marco Bassaletti's Bull Cows Game. Welcome!"));
    PrintLine(TEXT("Press tab to activate terminal and type commands."));
    PrintLine(TEXT("Type \"help\" command for help."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("cake");
}