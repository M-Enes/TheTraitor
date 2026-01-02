#pragma once

namespace TheTraitor {

	/**
	 * @brief Enumeration of all possible action types in the game.
	 */
	enum class ActionType
	{
		TradePact,       ///< Establishes a trade pact between two countries.
		TradeEmbargo,    ///< Initiates a trade embargo against a target country.
		JointResearch,   ///< Conducts joint research with another country.
		SpreadMisinfo,   ///< Spreads misinformation to damage a target's reputation or stats.
		HealthAid,       ///< Sends health aid to a target country.
		PoisonResources, ///< Poisons resources of a target country (Secret Action).
		SpreadPlague,    ///< Spreads a plague to a target country (Secret Action).
		DestroySchool,   ///< Destroys a school in a target country (Secret Action).
		SabotageFactory  ///< Sabotages a factory in a target country (Secret Action).
	};

	/**
	 * @brief Struct representing a packet sent to perform an action.
	 */
	typedef struct ActionPacket {
		ActionType actionType; ///< The type of action to be performed.
		int sourceID;          ///< The ID of the player initiating the action.
		int targetID;          ///< The ID of the target player/country.
	} ActionPacket;
}