// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "PongGameModeBase.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	launch_speed = 500000;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UStaticMeshComponent*> static_meshes;
	GetComponents<UStaticMeshComponent>(static_meshes);
	static_meshes[0]->OnComponentBeginOverlap.AddDynamic(this, &ABall::BeginOverlap);
	Cast<APongGameModeBase>(GetWorld()->GetAuthGameMode())->OnGameOver.AddDynamic(this, &ABall::PauseBall);
	Cast<APongGameModeBase>(GetWorld()->GetAuthGameMode())->OnRestartGame.AddDynamic(this, &ABall::StartBall);
	AddSpawnForce();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABall::AddSpawnForce() {
	int32 num_sign = ((rand() % 2) == 0 ? 1 : -1);
	if (RootComponent && RootComponent->IsAnySimulatingPhysics() && IsActorTickEnabled()) {
		Cast<UPrimitiveComponent>(RootComponent)->AddForce(FVector(num_sign * launch_speed, 0.0, 0.0));
	}
}

void ABall::PauseBall() {
	SetActorLocation(spawn_location);
	Cast<UPrimitiveComponent>(RootComponent)->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));
	SetActorTickEnabled(false);
}

void ABall::StartBall() {
	SetActorTickEnabled(true);
	AddSpawnForce();
}

void ABall::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherComp->ComponentHasTag(TEXT("Paddle"))) {
		FVector incoming_vector = Cast<UPrimitiveComponent>(RootComponent)->GetPhysicsLinearVelocity();
		Cast<UPrimitiveComponent>(RootComponent)->SetPhysicsLinearVelocity(FVector(-incoming_vector.X, incoming_vector.Y+OtherComp->GetPhysicsLinearVelocity().Y, 0.0));
	}
	else if (OtherComp->ComponentHasTag(TEXT("Wall"))) {
		FVector incoming_vector = Cast<UPrimitiveComponent>(RootComponent)->GetPhysicsLinearVelocity();
		Cast<UPrimitiveComponent>(RootComponent)->SetPhysicsLinearVelocity(FVector(incoming_vector.X, -incoming_vector.Y, 0.0));
	}
	else if (OtherComp->ComponentHasTag(TEXT("Goal_R"))) {
		SetActorLocation(spawn_location);
		Cast<UPrimitiveComponent>(RootComponent)->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));
		Cast<APongGameModeBase>(GetWorld()->GetAuthGameMode())->AddP1Score();
		AddSpawnForce();
	} else if (OtherComp->ComponentHasTag(TEXT("Goal_L"))) {
		SetActorLocation(spawn_location);
		Cast<UPrimitiveComponent>(RootComponent)->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));
		Cast<APongGameModeBase>(GetWorld()->GetAuthGameMode())->AddP2Score();
		AddSpawnForce();
	}
}

