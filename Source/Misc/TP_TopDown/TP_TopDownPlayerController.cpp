#include "TP_TopDownPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "TP_TopDownCharacter.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/DecalComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "ProceduralMeshComponent.h"
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
	
	ATP_TopDownCharacter* ControlledPawn = GetPawn<ATP_TopDownCharacter>();
	if (ControlledPawn)
	{
		End = ControlledPawn->GetCursorToWorld()->GetComponentLocation();
		End.Z = Start.Z;
	}

	TArray<AActor*> Ignores;
	Ignores.Add(GetPawn());

	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		Start,
		End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		Ignores,
		EDrawDebugTrace::ForDuration,
		Hit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.f
	);

	if (!Hit.bBlockingHit)
	{
		return;
	}

	ACSlicableMesh* OtherActor = Cast<ACSlicableMesh>(Hit.GetActor());
	UProceduralMeshComponent* OtherComp = Cast<UProceduralMeshComponent>(Hit.Component);

	if (OtherActor && OtherComp)
	{
		FVector Direction = End - Start;
		Direction.Normalize();

		UProceduralMeshComponent* NewComp = nullptr;

		UKismetProceduralMeshLibrary::SliceProceduralMesh
		(
			OtherComp,
			Hit.Location,
			GetPawn()->GetActorUpVector() ^ Direction,
			true,
			NewComp,
			EProcMeshSliceCapOption::CreateNewSectionForCap,
			OtherActor->GetCapMaterial()
		);

		NewComp->SetSimulatePhysics(true);
		NewComp->AddImpulse(Direction * 600.f, NAME_None, true);
	}
}
