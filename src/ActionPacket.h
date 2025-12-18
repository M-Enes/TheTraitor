#pragma once

namespace TheTraitor {

	enum class ActionType
	{
		TradePact,
		TradeEmbargo,
		JointResearch,
		SpreadMisinfo,
		HealthAid,
		PoisonResources,
		SpreadPlague,
		DestroySchool,
		SabotageFactory
	};

	typedef struct ActionPacket {
		ActionType actionType;
		int sourceID;
		int targetID;
	} ActionPacket;
}