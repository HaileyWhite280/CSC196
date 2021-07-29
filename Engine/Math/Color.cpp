#include "Color.h"
#include <string>

namespace nc
{
	const Color Color::white{ 1, 1, 1 };
	const Color Color::red{ 1, 0, 0 };
	const Color Color::blue{ 1, 0, 1 };
	const Color Color::green{ 0, 1, 0 };
	const Color Color::purple{ 1, 0, 1 };
	const Color Color::cyan{ 1, 0, 1 };
	const Color Color::orange{ 1, 0.5f, 1 };
	const Color Color::yellow{ 1, 1, 0 };
	const Color Color::black{ 1, 1, 0 };

	std::istream& operator >> (std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{") != std::string::npos)
		{
			std::string r = line.substr(line.find("{") + 1, line.find(",") - line.find("}") - 1);
			c.r = std::stof(r);

			line = line.substr(line.find(",") + 1);

			std::string g = line.substr(0, line.find(","));
			c.g = std::stof(g);

			std::string b = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
			c.b = std::stof(b);

		}

		return stream;
	}
}