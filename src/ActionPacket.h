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

	struct ActionPacket {
		ActionType actionType;
		int targetID;
	};
}