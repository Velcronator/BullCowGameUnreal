// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 BullCount = 0;
	int32 CowCount = 0;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void DisplayWelcomeMessage();
	void ProcessInput(const FString& Input);
	void IntiateGame();
	FString GetHiddenWord();
	void EndGame();
	void ContinueGamePrompt();
	bool IsAnIsogram(const FString& Input) const;
	TArray<FString>GetValidWords(const TArray<FString>& Wordlist) const;
	FBullCowCount GetBullsAndCows(const FString& Guess) const;




	// Your declarations go below!
	private:
	FString HiddenWord;
	FString GuessWord;
	int32 Lives;
	bool bResetGame;
	bool bEndPrompt;
	const int32 LivesMultiplier = 4;
	bool bIsItDebugTime = false;
	TArray<FString> ValidWords;
};
