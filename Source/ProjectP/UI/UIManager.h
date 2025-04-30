#pragma once

#include "../DefaultGameCommon.h"
#include "BaseUserWidget.h"
#include "subsystems/gameinstancesubsystem.h"

//#include "UIManager.generated.h"

class PROJECTP_API CUIManager : public Singleton<CUIManager>
{
public:
	CUIManager() {}
	~CUIManager() {}
	 
protected:
	UPROPERTY()
	TMap<FString, TObjectPtr<UBaseUserWidget>> widgetMap;
public:
	void AddWidget(const FString& Name, UBaseUserWidget* Widget);
	void DeleteWidget(const FString& Name);
	//UBaseUserWidget* FindWidget(const FString& Name);
	
	template <typename T>
	T* FindWidget(const FString& Name) { return Cast<T>(widgetMap.FindRef(Name)); }
};
