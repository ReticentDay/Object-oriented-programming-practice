#pragma once
namespace game_framework {
	//成就類別
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
	//成就(純文字)類別
	class GameInfoString : public GameInfoList 
	{
	public:
		GameInfoString(string name);
		string showInfo();
	private:
		string _name;
	};
	//成就(計數)類別
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