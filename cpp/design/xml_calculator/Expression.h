#pragma once
#include <memory>
#include <vector>

namespace XMLCalculator {

	template<typename NumericType>
	class IExpression {
	public:
		virtual NumericType operator()() = 0;

		virtual void addArgument(const std::shared_ptr<IExpression>& expression) = 0;
	};

	template<typename NumericType>
	class NumericExpression : public IExpression<NumericType>
	{
	public:
		NumericExpression<NumericType>(const NumericType& value) : value(value) {}

		virtual NumericType operator()() {
			return value;
		}

		virtual void addArgument(const std::shared_ptr<IExpression>& expression) {}

	private:
		NumericType value;
	};

	template<typename NumericType>
	class Expression : public IExpression<NumericType>
	{
	public:
		void addArgument(const std::shared_ptr<IExpression>& expression) {
			elements.push_back(expression);
		}

	protected:
		std::vector<std::shared_ptr<IExpression> > elements;
	};

	template<typename NumericType>
	class SumExpression : public Expression<NumericType> {
	public:
		NumericType operator()() {
			NumericType result = 0;
			for (auto element : elements) {
				result += (*element)();
			}
			return result;
		}
	};

	template<typename NumericType>
	class SubstractExpression : public Expression<NumericType> {
	public:
		NumericType operator()() {
			if (elements.empty() || elements.size() != 2) {
				throw std::logic_error("Error: Substraction requires two arguments!");
			}

			return (*elements[0])() - (*elements[1])();
		}
	};

	template<typename NumericType>
	class MultiplyExpression : public Expression<NumericType> {
	public:
		NumericType operator()() {
			NumericType result = 1;
			for (auto& element : elements) {
				result *= (*element)();
			}
			return result;
		}
	};

	template<typename NumericType>
	class DivideExpression : public Expression<NumericType> {
	public:
		NumericType operator()() {
			if (elements.empty() || elements.size() != 2) {
				throw std::logic_error("Error: Division requires two arguments!");
			}

			NumericType divisor = ((*elements[1])());
			if (divisor == static_cast<NumericType>(0)) {
				throw std::logic_error("Error: Division by zero!");
			}

			return ((*elements[0])()) / divisor;
		}
	};

} // namespace XMLCalculator