// Copyright 2017-2018 Csaba Molnar, Daniel Butum
#include "DlgDataDisplayTreeNode.h"

#define LOCTEXT_NAMESPACE "FDlgDataDisplayTreeNode"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FDlgDataDisplayTreeNode
FDlgDataDisplayTreeNode::FDlgDataDisplayTreeNode(const FText& InDisplayText, TSharedPtr<Self> InParent)
	: Super(InDisplayText, InParent)
{
}

TWeakObjectPtr<const AActor> FDlgDataDisplayTreeNode::GetParentActor() const
{
	if (Parent.IsValid())
	{
		return Parent.Pin()->GetParentActor();
	}

	return nullptr;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FDialogueBrowserTreeRootNode
FDlgDataDisplayTreeRootNode::FDlgDataDisplayTreeRootNode() :
	Super(FText::FromString(TEXT("ROOT")), nullptr)
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FDlgDataDisplayTreeActorNode
FDlgDataDisplayTreeActorNode::FDlgDataDisplayTreeActorNode(const FText& InDisplayText,
	FDlgDataDisplayTreeNodePtr InParent, TWeakObjectPtr<const AActor> InActor) :
	Super(InDisplayText, InParent), Actor(InActor)
{
	TextType = EDlgDataDisplayTextTreeNodeType::Actor;
}

TWeakObjectPtr<const AActor> FDlgDataDisplayTreeActorNode::GetParentActor() const
{
	// Get the Actor from this.
	if (Actor.IsValid())
	{
		return Actor;
	}

	return Super::GetParentActor();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FDlgDataDisplayTreeCategoryNode
FDlgDataDisplayTreeCategoryNode::FDlgDataDisplayTreeCategoryNode(const FText& InDisplayText,
	FDlgDataDisplayTreeNodePtr InParent, const EDlgDataDisplayCategoryTreeNodeType InCategoryType) :
	Super(InDisplayText, InParent)
{
	CategoryType = InCategoryType;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FDlgDataDisplayTreeVariableNode
FDlgDataDisplayTreeVariableNode::FDlgDataDisplayTreeVariableNode(const FText& InDisplayText,
	FDlgDataDisplayTreeNodePtr InParent, const FName& InVariableName,
	const EDlgDataDisplayVariableTreeNodeType InVariableType) :
	Super(InDisplayText, InParent), VariableName(InVariableName), VariableType(InVariableType)
{
	TextType = EDlgDataDisplayTextTreeNodeType::Variable;
}

#undef LOCTEXT_NAMESPACE
