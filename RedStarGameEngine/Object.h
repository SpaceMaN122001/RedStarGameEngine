#ifndef _OBJECT_H_
#define _OBJECT_H_

namespace rsge
{
	class Object : public sf::Sprite
	{
	public:
		Object() {}
		~Object() {}
		void setTextureFromFile(std::string pathToTexture);
		static std::vector<std::string> getObjectsList(std::string pathToObjects);
		static std::string getObjectProperty(std::string pathToObject, std::string propertyName);
		void setId(std::string id) { mId = id; }
		void setRenderState(bool isRenderState) { mIsRender = isRenderState; }
		std::string& getId() { return mId; }
		bool& isRender() { return mIsRender; }
		std::string& getPathToTexture() { return mPathToTexture; }
	private:
		sf::Texture mTexture;
		std::string mId;
		bool mIsRender = true;
		std::string mPathToTexture;
	};
}

#endif