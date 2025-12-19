#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "CommonTypes.h"
#include "ClientApp.h"
#include "GameState.h"
#include "Packet.h"

namespace TheTraitor {

	void ClientApp::run()
	{
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

		
		}
	}

	void ClientApp::updateLobby()
	{
		// TODO: Get actual player names from server
		sf::sleep(sf::seconds(1));
		gameState.currentPhase = ACTION_PHASE; // TODO: action set for debugging purposes

	}

	void ClientApp::updateDiscussionPhase()
	{
	}

	void ClientApp::updateActionPhase() {
		const InputData& inputData = inputHandler.getInputData();
		const ViewData& viewData = gameView.handleActionPhaseInput(inputData);
		if (viewData.isActionRequested) {
			// TODO: send action packet
		}
	}

	void ClientApp::updateResolutionPhase()
	{
	}

	void ClientApp::updateGameover()
	{
	}

	void ClientApp::updateWin()
	{
	}

	void ClientApp::update(sf::Time deltaTime)
	{
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
		}
	}

	void ClientApp::render()
	{

		window.clear(sf::Color(0, 0, 0, 255));
		switch (gameState.currentPhase) {
		case MENU:
			gameView.renderMenu();
			break;
		case LOBBY:
			gameView.renderLobby(gameState.players); // Pass players to renderLobby // <- Check this again
			break;
		case DISCUSSION_PHASE:
			gameView.renderDiscussionPhase();
			break;
		case ACTION_PHASE:
			gameView.renderActionPhase();
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

	ClientApp::ClientApp(std::string executableFolderPath) :
		window(sf::VideoMode::getFullscreenModes()[0], "The Traitor", sf::Style::None, sf::State::Fullscreen),
		inputHandler(window),
		gameView(window, executableFolderPath),
		serverPort(5000),//Give port here
		serverIp(sf::IpAddress::LocalHost)//Give ip here
		// currently action for testing purposes
	{
		gameState.currentPhase = ACTION_PHASE;

		window.setFramerateLimit(60);

		//Set dummy players and give to the vector for testing purposes
		gameState.players.push_back(TheTraitor::Player("Player 1", new TheTraitor::Country()));
		gameState.players.push_back(TheTraitor::Player("Player 2", new TheTraitor::Country()));
		gameState.players.push_back(TheTraitor::Player("Player 3", new TheTraitor::Country()));
		gameState.players.push_back(TheTraitor::Player("Player 4", new TheTraitor::Country()));
	}

}

sf::TcpSocket* TheTraitor::ClientApp::openTCPSocket(sf::IpAddress ip, unsigned short port) {
	sf::TcpSocket* socket = new sf::TcpSocket();
	if (socket->connect(ip, port) != sf::Socket::Status::Done) {
		//error
	}
	socket->setBlocking(false);
	return socket;
}

void TheTraitor::ClientApp::receivePackets(sf::TcpSocket* socket) {
	sf::Packet packet;
	if (socket->receive(packet) != sf::Socket::Status::Done) {
		//error
	}
	TheTraitor::Packet* packetData = new TheTraitor::Packet();
	packet >> *packetData;

	// Process packetData as needed
	if (packetData->gameState) {
		// Handle game state update
		gameState = packetData->data.gameState;
	} else if (packetData->string) {
		// Handle string data
	}
}

void sendPacket(sf::TcpSocket* socket, TheTraitor::Packet& packet) {
	sf::Packet sfmlPacket;
	sfmlPacket << packet;
	if (socket->send(sfmlPacket) != sf::Socket::Status::Done) {
		//error
	}
}