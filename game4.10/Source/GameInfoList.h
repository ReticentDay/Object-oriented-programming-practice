#pragma once
namespace game_framework {
	//���N���O
	class  GameInfoList
	{
	public:
		GameInfoList();
		virtual string showInfo();
		virtual void setCount(int count);
		virtual int returnCount();
	protected:
	private:
		
	};
	//���N(�¤�r)���O
	class GameInfoString : public GameInfoList 
	{
	public:
		GameInfoString(string name);
		string showInfo();
	private:
		string _name;
	};
	//���N(�p��)���O
	class GameInfoCount : public GameInfoList
	{
	public:
		GameInfoCount(string name ,int count, string backInfo);
		void setCount(int count);
		int returnCount();
		string showInfo();
	private:
		string _name;
		int _count;
		string _backInfo;
	};

}