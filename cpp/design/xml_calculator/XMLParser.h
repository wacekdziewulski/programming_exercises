#pragma once

#include "rapidxml-1.13\rapidxml.hpp"
#include "Expression.h"
#include "ExpressionFactory.h"
#include <iostream>
#include <string>

namespace XMLCalculator {
namespace XMLProcessor {

	template<typename NumericType>
	std::shared_ptr<XMLCalculator::IExpression<NumericType>> buildExpressionTree(rapidxml::xml_node<>* node) {
		using namespace rapidxml;
		std::shared_ptr<XMLCalculator::IExpression<NumericType>> result = XMLCalculator::ExpressionFactory<NumericType>::create(node->name());

		for (xml_node<>* expression = node->first_node(); expression; expression = expression->next_sibling()) {
			if (expression->first_node() && XMLCalculator::isComplexExpressionString(expression->first_node()->name())) {
				result->addArgument(buildExpressionTree<NumericType>(expression->first_node()));
			}
			else {
				result->addArgument(XMLCalculator::ExpressionFactory<NumericType>::create(expression->name(), std::stod(expression->value())));
			}
		}

		return result;
	}

	void processXML(std::vector<char>& buffer);

} // namespace XMLParser;
} // namespace XMLCalculator