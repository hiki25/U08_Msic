#include "CSlicableMesh.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Engine.h"
#include "Materials/Material.h"

ACSlicableMesh::ACSlicableMesh()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = RootComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetupAttachment(RootComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> StateMeshAsset(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	if (StateMeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(StateMeshAsset.Object);
	}

	StaticMeshComp->SetVisibility(false);
	StaticMeshComp->SetCollisionProfileName("NoCollision");

	ProcMeshComp = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMeshComp");
	ProcMeshComp->SetupAttachment(RootComp);

	ProcMeshComp->SetSimulatePhysics(true);
	ProcMeshComp->bUseComplexAsSimpleCollision = false;

	bRunConstructionScriptOnDrag = false;
}

UMaterial* ACSlicableMesh::GetCapMaterial()
{
	return CapMaterial;
}

void ACSlicableMesh::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(StaticMeshComp, 0, ProcMeshComp, true);
}
