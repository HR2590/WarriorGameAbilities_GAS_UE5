// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTarea3GAS, Log, All);

class TAREA3GAS_API ITagManager:public IModuleInterface
{

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
