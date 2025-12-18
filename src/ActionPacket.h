#pragma once

namespace TheTraitor {

	enum class ActionType
	{
		TradePact,
		TradeEmbargo,
		JointResearch,
		SpreadMisinfo,
		HealthAid,
		PoisonResources
	};

	typedef struct ActionPacket {
		ActionType actionType;
		int targetID;
	} ActionPacket;
}