#pragma once

#include <memory>
#include "Expression.h"
#include <map>

namespace XMLCalculator {
	enum Operator {
		ADDITION,
		SUBSTRACTION,
		MULTIPLICATION,
		DIVISION,
		ITEM
	};

	static Operator stringToOperator(const std::string& tag) {
		static std::map<std::string, Operator> conversionMap = {
			{ "addition", ADDITION },
			{ "subtraction", SUBSTRACTION },
			{ "multiplication", MULTIPLICATION },
			{ "division", DIVISION },
			{ "item", ITEM },
			{ "minuend", ITEM },
			{ "subtrahend", ITEM },
			{ "factor", ITEM },
			{ "dividend", ITEM },
			{ "divisor", ITEM }
		};

		return conversionMap[tag];
	}

	bool isComplexExpressionString(const std::string& tag);

	template <typename NumericType>
	struct ExpressionFactory {
		static std::shared_ptr<IExpression<NumericType>> create(const std::string& operation, NumericType value = static_cast<NumericType>(0)) {
			std::shared_ptr<IExpression<NumericType>> expression;

			switch (stringToOperator(operation)) {
				case ADDITION:
					expression = std::shared_ptr<IExpression<NumericType>>(new SumExpression<NumericType>());
					break;
				case SUBSTRACTION:
					expression = std::shared_ptr<IExpression<NumericType>>(new SubstractExpression<NumericType>());
					break;
				case MULTIPLICATION:
					expression = std::shared_ptr<IExpression<NumericType>>(new MultiplyExpression<NumericType>());
					break;
				case DIVISION:
					expression = std::shared_ptr<IExpression<NumericType>>(new DivideExpression<NumericType>());
					break;
				case ITEM:
					expression = std::shared_ptr<IExpression<NumericType>>(new NumericExpression<NumericType>(value));
					break;
				default:
					throw std::invalid_argument("Unrecognized tag in expression factory!");
			}

			return expression;
		}
	};

} // namespace XMLCalculator