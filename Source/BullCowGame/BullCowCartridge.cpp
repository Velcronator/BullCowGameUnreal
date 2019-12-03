// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordsList.h"
#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game 
{
    Super::BeginPlay();
	ValidWords = GetValidWords(Words);
	IntiateGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
	ClearScreen();
	ProcessInput(PlayerInput);
}

void UBullCowCartridge::DisplayWelcomeMessage()
{
	PrintLine(TEXT("Velcro's Bulls and Cows"));
	PrintLine(TEXT("Please click press 'Tab' to start"));
	//PrintLine(TEXT("Enter a ") + FString::FromInt(GameLevel + 3) + TEXT(" letter word...")); // what you would normally do if it wasn't defined elsewhere
	PrintLine(TEXT("Enter a %i letter word."), HiddenWord.Len());
	PrintLine(TEXT("You have %i guesses."), Lives);

}

void UBullCowCartridge::ProcessInput(const FString& Input)
{
	if (Input == "H") {
		bIsItDebugTime = !bIsItDebugTime;
		if (bIsItDebugTime) { 
			PrintLine(TEXT("The Hidden word is %s"), *HiddenWord); 
		}
		return;
	}

	if (bEndPrompt) 
	{
		bResetGame = true;
		bEndPrompt = false;
		ClearScreen();
		IntiateGame();
		return;
	}

	if (!IsAnIsogram(Input)) 
	{
		PrintLine(TEXT("%s is not an Isogram"), *Input);
		return;
	}

	if (HiddenWord == Input)
	{
		PrintLine(TEXT("Nailed it."));
		PrintLine(TEXT("The Hidden word was %s"), *HiddenWord);
		EndGame();
	}
	else
	{
		FBullCowCount Score = GetBullsAndCows(Input);
		PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.BullCount, Score.CowCount);

		Lives--;

		if (Lives <= 0) {
			PrintLine(TEXT("The Hidden word was %s"), *HiddenWord);
			PrintLine(TEXT("You have lost dude."), Lives);
			EndGame();
			return;
		}
		else
		{
			PrintLine(TEXT("Try again. You have %i lives left."), Lives);
		}

		if (Input.Len() != HiddenWord.Len())
		{
			PrintLine(TEXT("The word has %i letters, numnuts."), HiddenWord.Len());
		}
	}
	
}


void UBullCowCartridge::IntiateGame()
{
	//Intiate game(lives Levels hidden word)
	bResetGame = false;
	bEndPrompt = false;
	HiddenWord = GetHiddenWord();
	Lives = HiddenWord.Len() * LivesMultiplier;
	DisplayWelcomeMessage();
}

FString UBullCowCartridge::GetHiddenWord()
{
	HiddenWord = ValidWords[FMath::RandRange(0, ValidWords.Num() -1 )];
	return HiddenWord;
}

void UBullCowCartridge::EndGame()
{
	ContinueGamePrompt();
}

void UBullCowCartridge::ContinueGamePrompt()
{
	bEndPrompt = true;
	PrintLine(TEXT("Enter to play again."));
}

bool UBullCowCartridge::IsAnIsogram(const FString& str) const
{
	for (int i = 0; i < str.Len(); i++)
	{
		for (int j = 0; j < str.Len(); j++)
		{
			if (i != j)
			{
				if (str[i] == str[j])
				{
					return false;
				}
			}
		}
	}
	return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Wordlist ) const
{
	TArray<FString> ValidWords;

	for (FString Words : Wordlist)
	{
		if (Words.Len() <= 8 && Words.Len() >= 4 && IsAnIsogram(Words))
		{
			ValidWords.Emplace(Words);
		}
	}
	return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullsAndCows(const FString& Guess) const
{
	FBullCowCount BullCowCount;
	
	BullCowCount.BullCount = 0;
	BullCowCount.CowCount = 0;

	for (int32 i = 0; i < Guess.Len(); i++) {
		if (Guess[i] == HiddenWord[i]) {
			BullCowCount.BullCount++; // Direct hit
		}
		else {
			for (int32 j = 0; j < Guess.Len(); j++)
			{	// See if char is repeated elsewhere.
				if ((Guess[i]) == HiddenWord[j] && (i != j))
				{
					BullCowCount.CowCount++;
					break;
				}
			}
		}
	}
	return BullCowCount;

// VERSION WITH THE OUT PARAMETERS.
//void UBullCowCartridge::GetBullsAndCows(const FString & Guess, int32 & BullCount, int32 & CowCount)
//{
//	BullCount = 0;
//	CowCount = 0;
//
//	for (int32 i = 0; i < Guess.Len(); i++) {
//		if (Guess[i] == HiddenWord[i]) {
//			BullCount++; // Direct hit
//		}
//		else {
//			for (int32 j = 0; j < Guess.Len(); j++)
//			{	// See if char is repeated elsewhere.
//				if ((Guess[i]) == HiddenWord[j] && (i != j))
//				{
//					CowCount++;
//				}
//			}
//		}
//	}
//}
}