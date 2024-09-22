#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TP_TopDownCharacter.generated.h"

UCLASS(Blueprintable)
class ATP_TopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATP_TopDownCharacter();

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};

