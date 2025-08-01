// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBaseEnemyController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


// Sets default values
ARPGBaseEnemyController::ARPGBaseEnemyController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	// Criando e configurando o componente de percepção
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*PerceptionComponent);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 2000.f;
	SightConfig->LoseSightRadius = 2500.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->SetMaxAge(5.f);

	// Detectar todos os tipos (inimigo, aliado, neutro)
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	// Bind de evento
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ARPGBaseEnemyController::OnTargetPerceptionUpdated);

}

// Called when the game starts or when spawned
void ARPGBaseEnemyController::BeginPlay()
{
	Super::BeginPlay();
	SetGenericTeamId(FGenericTeamId(0));
	
}

// Called every frame
void ARPGBaseEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARPGBaseEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ARPGBaseEnemyController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	// Debug
	if (Stimulus.WasSuccessfullySensed())
	{
		//UE_LOG(LogTemp, Warning, TEXT("See %s"), *Actor->GetName());
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Lost sight %s"), *Actor->GetName());
	}
}
