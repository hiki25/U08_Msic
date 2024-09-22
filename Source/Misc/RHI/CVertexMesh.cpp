#include "CVertexMesh.h"

ACVertexMesh::ACVertexMesh()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.f;

	ProcMeshComp = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMesh");
	RootComponent = ProcMeshComp;

	FVector V = FVector(0.5f);

	//Front
	Positions.Add(FVector(-V.X, -V.Y, -V.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-V.X, -V.Y, +V.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-V.X, +V.Y, -V.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(-V.X, +V.Y, +V.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(-1, 0, 0));
		Tangents.Add(FProcMeshTangent(0, 1, 0));
		Colors.Add(FColor::Red);
	}
	AddIndices(0);

	//Back
	Positions.Add(FVector(+V.X, +V.Y, -V.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+V.X, +V.Y, +V.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+V.X, -V.Y, -V.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+V.X, -V.Y, +V.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(+1, 0, 0));
		Tangents.Add(FProcMeshTangent(0, -1, 0));
		Colors.Add(FColor::Green);
	}
	AddIndices(4);


	//Top
	Positions.Add(FVector(-V.X, -V.Y, +V.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+V.X, -V.Y, +V.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-V.X, +V.Y, +V.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+V.X, +V.Y, +V.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, +1));
		Tangents.Add(FProcMeshTangent(0, 1, 0));
		Colors.Add(FColor::Blue);
	}
	AddIndices(8);


	//Bottom
	Positions.Add(FVector(-V.X, -V.Y, -V.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-V.X, +V.Y, -V.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+V.X, -V.Y, -V.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+V.X, +V.Y, -V.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, -1));
		Tangents.Add(FProcMeshTangent(0, 1, 0));
		Colors.Add(FColor::Cyan);
	}
	AddIndices(12);


	//Left
	Positions.Add(FVector(+V.X, -V.Y, -V.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+V.X, -V.Y, +V.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-V.X, -V.Y, -V.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(-V.X, -V.Y, +V.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, -1, 0));
		Tangents.Add(FProcMeshTangent(1, 0, 0));
		Colors.Add(FColor::Magenta);
	}
	AddIndices(16);


	//Right
	Positions.Add(FVector(-V.X, +V.Y, -V.Z)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-V.X, +V.Y, +V.Z)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+V.X, +V.Y, -V.Z)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+V.X, +V.Y, +V.Z)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, +1, 0));
		Tangents.Add(FProcMeshTangent(-1, 0, 0));
		Colors.Add(FColor::Yellow);
	}
	AddIndices(20);

	ProcMeshComp->CreateMeshSection(0, Positions, Indices, Normals, UVs, Colors, Tangents, true);
	ProcMeshComp->SetRelativeScale3D(FVector(100.f));
}

void ACVertexMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACVertexMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < Colors.Num(); i += 4)
	{
		FColor RandomColor = FColor::MakeRandomColor();
		RandomColor.A = 255.f;

		Colors[i + 0] = RandomColor;
		Colors[i + 1] = RandomColor;
		Colors[i + 2] = RandomColor;
		Colors[i + 3] = RandomColor;
	}

	/*for (int32 i = 0; i < Positions.Num(); i++)
	{
		Positions[i] += FVector(10 * DeltaTime, 0, 0);
		GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::White, FString::SanitizeFloat(Positions[i].X));
	}*/

	ProcMeshComp->UpdateMeshSection(0, Positions, Normals, UVs, Colors, Tangents);
}

void ACVertexMesh::AddIndices(int32 StartIndex)
{
	Indices.Add(StartIndex + 2);
	Indices.Add(StartIndex + 1);
	Indices.Add(StartIndex + 0);

	Indices.Add(StartIndex + 3);
	Indices.Add(StartIndex + 1);
	Indices.Add(StartIndex + 2);
}