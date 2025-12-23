#pragma once

#include <string>

namespace TheTraitor {
    class Player;

    class Action {
    public:
        virtual void execute(Player& player1, Player& player2) = 0;
        virtual std::string getLogMessage(const Player& player1, const Player& player2) = 0;
    protected:
        Action() = default; // allow derived classes to construct
    };

    class SecretAction : public Action {
    public:
        virtual ~SecretAction() = default;
    protected:
        SecretAction() = default;
    };

    class TradePact : public virtual Action {
    public:
        TradePact();
        virtual void execute(Player& player1, Player& player2) override;
        virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
    };

    class TradeEmbargo : public virtual Action {
    public:
        TradeEmbargo();
        virtual void execute(Player& player1, Player& player2) override;
        virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
    };

    class JointResearch : public virtual Action {
    public:
        JointResearch();
        virtual void execute(Player& player1, Player& player2) override;
        virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
    };

    class SpreadMisinfo : public virtual Action {
    public:
        SpreadMisinfo();
        virtual void execute(Player& player1, Player& player2) override;
        virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
    };

    class HealthAid : public virtual Action {
    public:
        HealthAid();
        virtual void execute(Player& player1, Player& player2) override;
        virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
    };

    class PoisonResources : public virtual Action {
    public:
        PoisonResources();
        virtual void execute(Player& player1, Player& player2) override;
        virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
    };

    class SabotageFactory : public virtual SecretAction {
    public:
        SabotageFactory();
        virtual void execute(Player& player1, Player& player2) override;
        virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
    };

    class DestroySchool : public virtual SecretAction {
    public:
        DestroySchool();
        virtual void execute(Player& player1, Player& player2) override;
        virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
    };

    class SpreadPlague : public SecretAction {
    public:
        SpreadPlague();
        virtual void execute(Player& player1, Player& player2) override;
        std::string getLogMessage(const Player& player1, const Player& player2) override;
    };
}