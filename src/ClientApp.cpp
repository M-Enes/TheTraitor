#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "CommonTypes.h"
#include "ClientApp.h"
#include "GameState.h"
#include "PacketType.h"

namespace TheTraitor {

ClientApp::ClientApp(std::string executableFolderPath)
    : window(sf::VideoMode::getFullscreenModes()[0], "The Traitor", sf::Style::None, sf::State::Fullscreen),
      inputHandler(window),
      gameView(window, executableFolderPath),
      serverPort(5000),
      serverIp(sf::IpAddress::LocalHost) {

    gameState.currentPhase = WIN; // Test: Change to GAMEOVER or WIN to test end screens. Currently it is ACT

    window.setFramerateLimit(60);

    // Dummy players for initial testing
    gameState.players.push_back(Player("Player 1", new Country()));
    gameState.players.push_back(Player("Player 2", new Country()));
    gameState.players.push_back(Player("Player 3", new Country()));
    gameState.players.push_back(Player("Player 4", new Country()));
    gameState.players.push_back(Player("Player 5", new Country())); // for ui test
}

void ClientApp::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        update(deltaTime);
        render();
    }
}

void ClientApp::updateMenu() {
    const InputData& inputData = inputHandler.getInputData();
    const ViewData& viewData = gameView.handleMenuInput(inputData);

    if (gameState.currentPhase == LOBBY) {
        (void)viewData; // Placeholder until menu transitions are wired
    }
}

void ClientApp::updateLobby() {
    // TODO: Get actual player names from server
    sf::sleep(sf::seconds(1));
    gameState.currentPhase = ACTION_PHASE; // TODO: action set for debugging purposes
}

void ClientApp::updateDiscussionPhase() {
}

void ClientApp::updateActionPhase() {
    const InputData& inputData = inputHandler.getInputData();
    const ViewData& viewData = gameView.handleActionPhaseInput(inputData);
    if (viewData.isActionRequested) {
        // TODO: send action packet
    }
}

void ClientApp::updateResolutionPhase() {
}

void ClientApp::updateGameover() {
}

void ClientApp::updateWin() {
}

void ClientApp::update(sf::Time deltaTime) {
    inputHandler.handleEvents();
    switch (gameState.currentPhase) {
    case MENU:
        updateMenu();
        break;
    case LOBBY:
        updateLobby();
        break;
    case DISCUSSION_PHASE:
        updateDiscussionPhase();
        break;
    case ACTION_PHASE:
        updateActionPhase();
        break;
    case RESOLUTION_PHASE:
        updateResolutionPhase();
        break;
    case GAMEOVER:
        updateGameover();
        break;
    case WIN:
        updateWin();
        break;
    default:
        break;
    }
}

void ClientApp::render() {
    window.clear(sf::Color(0, 0, 0, 255));
    switch (gameState.currentPhase) {
    case MENU:
        gameView.renderMenu();
        break;
    case LOBBY:
        gameView.renderLobby(gameState.players);
        break;
    case DISCUSSION_PHASE:
        gameView.renderDiscussionPhase();
        break;
    case ACTION_PHASE:
        gameView.renderActionPhase(gameState.players);
        break;
    case RESOLUTION_PHASE:
        gameView.renderResolutionPhase();
        break;
    case GAMEOVER:
        gameView.renderGameover();
        break;
    case WIN:
        gameView.renderWin();
        break;
    }
    
    window.display();
}

sf::TcpSocket* ClientApp::openTCPSocket(sf::IpAddress ip, unsigned short port) {
    sf::TcpSocket* socket = new sf::TcpSocket();
    if (socket->connect(ip, port) != sf::Socket::Status::Done) {
        //error
    }
    socket->setBlocking(false);
    return socket;
}

void ClientApp::receivePackets(sf::TcpSocket& socket) {
    sf::Packet packet;
    PacketType packetType;
    if (socket.receive(packet) != sf::Socket::Status::Done) {
        //error
        return;
    }
    packet >> packetType;
    switch (packetType) {
    case PacketType::ACTION_PACKET: {
        ActionPacket actionPacket;
        packet >> actionPacket;
        // Process actionPacket
        break;
    }
    default:
        break;
    }
}

void ClientApp::sendPacket(sf::TcpSocket* socket, Packet& packet) {
    sf::Packet sfmlPacket;
    sfmlPacket << packet;
    if (socket->send(sfmlPacket) != sf::Socket::Status::Done) {
        //error
    }
}

} // namespace TheTraitor