#ifndef CODEPRINTER_HPP
#define CODEPRINTER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

class CodePrinter {

	public:

		CodePrinter(std::string const &p_filename, bool const & p_welcomeMessage = true) {

			std::ifstream
			fs(p_filename);

			if(fs.is_open()) {

				std::stringstream
				ss;

				ss << fs.rdbuf();

				fs.close();

				std::string
				s = ss.str();

				std::size_t
				from = 0,
				to = s.find("//@", from);

				while(to != std::string::npos) {

					from = to + 3;

					std::size_t
					send = s.find("\n", to);

					std::string
					name = std::string(s, from, send - from);

					to = s.find("//@", send + 1);

					if(0 < name.length()) {

						text[name] = std::string(s, send + 1, to - send - 1);
					}
				}
			}

			if(! p_welcomeMessage) {

				return;
			}

			std::cout << "\n  - next frame by pressing ENTER or RETURN\n  - to finish the show press one of these keys\n    q, Q, x, X\n    followed by ENTER or RETURN\n\n";
		}

	public:

		std::map< std::string, std::string >
		text;

		void
		print(std::string const & p_snippetname) {

			std::cout <<
			"----------------------------------------------------------------------------------------------------------------" <<
			"\n[" <<
			p_snippetname <<
			"]\nc++:\n" <<
			text[p_snippetname] <<
			"\nout:\n";
		}

		static bool
		waitForENTER() {

			std::cout << "[ENTER] for next frame!\n";

			int
			c = std::cin.get();

			return (c == 'x') || (c == 'X') || (c == 'q') || (c == 'Q');
		}

		static bool
		WFE () {

			if(waitForENTER())
				exit(-1);

			return true;
		}
};

#endif // CODEPRINTER_HPP
