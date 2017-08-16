#include <SFML/Graphics.hpp>
#include <vector>
#include "Cursor.cpp"
#include <memory>


class Game {
	private:
		std::vector<std::shared_ptr<Cursor>> cursors;

	public:
		int numPlayers;
		sf::RenderWindow* window;

		int addCursor(std::shared_ptr<Cursor> cursor) {
			cursors.push_back(std::move(cursor));
			return 0;
		}

		std::shared_ptr<Cursor> getCursor(int cursorNumber) {
			return cursors.at(cursorNumber);
		}

		void clearCursors()
		{
			cursors.clear();
		}

};