#include "ExpressionFactory.h" 

namespace XMLCalculator {

bool isComplexExpressionString(const std::string& tag) {
	static std::vector<std::string> ExpressionStrings{ "addition", "subtraction", "multiplication", "division" };
	return (std::find(ExpressionStrings.begin(), ExpressionStrings.end(), tag) != ExpressionStrings.end());
}

} // namespace XMLCalculator