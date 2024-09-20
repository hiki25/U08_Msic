#include "TP_TopDownPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "TP_TopDownCharacter.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/DecalComponent.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "TP_TopDownCharacter.h"
#include "RHI/CSlicableMesh.h"

ATP_TopDownPlayerController::ATP_TopDownPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATP_TopDownPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ATP_TopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATP_TopDownPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATP_TopDownPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Slice", IE_Pressed, this, &ATP_TopDownPlayerController::OnSlice);
}


void ATP_TopDownPlayerController::MoveToMouseCursor()
{
	
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	
}


void ATP_TopDownPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ATP_TopDownPlayerController::OnSetDestinationPressed()
{
	bMoveToMouseCursor = true;
}

void ATP_TopDownPlayerController::OnSetDestinationReleased()
{
	bMoveToMouseCursor = false;
}

void ATP_TopDownPlayerController::OnSlice()
{

	FVector Start = GetPawn()->GetActorLocation();
	FVector End = Start + GetPawn()->GetActorForwardVector() * 500.f;
	ATP_TopDownCharacter* TPCharacter = GetPawn<ATP_TopDownCharacter>();
	if (TPCharacter)
	{
		End = TPCharacter->GetCursorToWorld()->GetComponentLocation();
		End.Z = Start.Z;
	}

	TArray<AActor*> Ignores;
	Ignores.Add(GetPawn());

	FHitResult HitResult;

	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		Start,
		End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true,
		Ignores,
		EDrawDebugTrace::ForDuration,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.f);

	if (!HitResult.bBlockingHit)
	{
		return;
	}

	UProceduralMeshComponent* OtherComp = Cast<UProceduralMeshComponent>(HitResult.Component);
	ACSlicableMesh* OtherActor = Cast<ACSlicableMesh>(HitResult.Actor);

	if (OtherComp && OtherActor)
	{
		FVector Dir = End - Start;
		Dir.Normalize();

		UProceduralMeshComponent* NewComp = nullptr;

		UKismetProceduralMeshLibrary::SliceProceduralMesh
		(
			OtherComp,
			HitResult.Location,
			TPCharacter->GetActorUpVector() ^ Dir,
			true,
			NewComp,
			EProcMeshSliceCapOption::CreateNewSectionForCap,
			OtherActor->GetCapMaterial()
		);

		NewComp->SetSimulatePhysics(true);
		NewComp->AddImpulse(Dir * 600.f,NAME_None,true);
	}
}

