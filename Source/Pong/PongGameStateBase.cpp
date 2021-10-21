// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameStateBase.h"

APongGameStateBase::APongGameStateBase() {
	
}

void APongGameStateBase::BeginPlay() {
	p1_score = 0;
	p2_score = 0;
	Super::BeginPlay();
}
