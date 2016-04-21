#pragma once

#include <TGUI/TGUI.hpp>
#include <SFML/Network.hpp>
#include "Configuration.h"
#include "Connection.h"
#include "StartInfo.h"

/*
lobby namespace
the class/struct in this namespace are for supporting lobby only.
*/
namespace lobby
{
	/*
	Character class for Lobby
	contains the character's texture and name of the character
	*/
	class Character
	{
	public:
		enum Name{SilverGuy, GoldGuy, RedGirl, BrownGirl};	//we will discuss their name later.
	private:
		Name name;
	public:
		Character(Name newName = SilverGuy) : name(newName) { ; }
		void setName(Name newName) { name = newName; }
		void setPic(tgui::Picture::Ptr ptr);	//set the incoming picture to character's picture.
	};
	/*
	Player class for Lobby
	contains the name of player, his/her character and IP. Also included GUI representation.
	*/
	class Player
	{
	private:
		std::string name;	//player's name, not character's name
		sf::IpAddress ip;
		Character character;

		//GUI for player
		tgui::Panel::Ptr panel;
		tgui::Label::Ptr nameText;
		tgui::Picture::Ptr charPic;
	public:
		Player() = delete;
		Player(const Player&) = delete;
		Player operator=(const Player&) = delete;
		Player(std::string newName, sf::IpAddress newIP, Character newChar);

		//getters
		std::string getName() { return name; }
		sf::IpAddress getIP() { return ip; }
		Character getCharacter() { return character; }

		//setters
		void setCharacter(Character::Name name) { character.setName(name); }
		
		//get Panel
		tgui::Panel::Ptr getPanel() { return panel; }
	};
}

/*
Lobby class
Handles the system and the API of multiplayer lobby before the game starts.
Note: Since other widgets are already in panel, so only panel is needed to be added to gui!
*/
class Lobby
{
public:
	//the type of Lobby: client or server?
	enum TYPE { client, server };
private:
	Configuration& config;		//reference to configuration

	tgui::Panel::Ptr panel;
	tgui::Button::Ptr backButton;
	tgui::Button::Ptr startButton;
	tgui::ChatBox::Ptr chatBox;
	tgui::TextBox::Ptr chatInput;
	tgui::Button::Ptr chatInputButton;
	tgui::Picture::Ptr mapPicture;
    
    //the lobby needs connection
    Connection connection;

	//type of lobby
	TYPE type;

	//function to initialize the gui
	void initialize();

	//handles the incoming packet
	void handlePacket(Package& package);

	//debug only
	std::unique_ptr<lobby::Player> playerPtr;
public:
	Lobby() = delete;
	Lobby(const Lobby&) = delete;
	Lobby operator=(const Lobby&) = delete;

	//constructor for client
	Lobby(Configuration& config, sf::IpAddress serverIp);
	//constructor for server
	Lobby(Configuration& config);

	//add the panel to gui
	void addTgui(tgui::Gui& gui);

	//connect the backButton
	template<typename Func, typename...Args>
	unsigned int connectBackButton(const std::string& signalNames, Func func, Args... args)
	{
		return backButton->connect(signalNames, func, args...);
	}

	//connect the startButton
	template<typename Func, typename...Args>
	unsigned int connectStartButton(const std::string& signalNames, Func func, Args... args)
	{
		return startButton->connect(signalNames, func, args...);
	}

	//hide the panel
	void hide();

	//show the panel
	void show();

	//show the panel with effect
	void showWithEffect(const tgui::ShowAnimationType& type, const sf::Time& duration);

	//update the lobby's data
	void update();

	//get the game data
	std::unique_ptr<StartInfo> getStartInfo();
};