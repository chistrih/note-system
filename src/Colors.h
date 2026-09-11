#pragma once
#include <string>

namespace Color {
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";
	const std::string RED = "\033[31m";
	const std::string GREEN = "\033[32m";
	const std::string YELLOW = "\033[33m";
	const std::string CYAN = "\033[96m";
	const std::string MAGENTA = "\033[35m";
	
	const std::string DIM     = "\033[2m";
	const std::string CLEAR   = "\033[2J\033[1;1H";
}
