#include "XMLParser.h"
#include <sstream>
#include <vector>
#include <utility>
#include "rapidxml-1.13\rapidxml_print.hpp"

namespace XMLCalculator {
namespace XMLProcessor {

// The set contains the expression calculation results on which the output XML will be built
typedef std::pair<std::string, std::string> ResultElement;
typedef std::vector<ResultElement> ResultSet;

void createOutputXML(rapidxml::xml_document<>& outputXML, const ResultSet& results) {
	using namespace rapidxml;

	xml_node<>* expressionsOutputNode = outputXML.allocate_node(node_element, "expressions");
	outputXML.append_node(expressionsOutputNode);

	for (const auto& result : results) {
		xml_attribute<> *attribute = outputXML.allocate_attribute("id", result.first.c_str());
		
		char* result_string = outputXML.allocate_string(result.second.c_str());
		xml_node<> *output_result = outputXML.allocate_node(node_element, "result", result_string);
		
		output_result->append_attribute(attribute);
		expressionsOutputNode->append_node(output_result);
	}
}

void processXML(std::vector<char>& buffer) {
	// parse xml contents
	using namespace rapidxml;
	xml_document<> doc;    // character type defaults to char
	doc.parse<0>(&(*buffer.begin()));    // 0 means default parse flags

	// sanity check
	static const std::string expressionsHeaderString("expressions\n");
	if (!expressionsHeaderString.compare(doc.first_node()->name()) || !expressionsHeaderString.compare(doc.last_node()->name())) {
		throw std::invalid_argument("The XML file does not contain 'expression' tags!");
	}

	ResultSet calculationResults;

	// iterate over the expressions and calculate their result
	xml_node<> *root = doc.first_node();
	for (xml_node<>* expression = root->first_node(); expression; expression = expression->next_sibling()) {
		std::shared_ptr<XMLCalculator::IExpression<int>> calculation = buildExpressionTree<int>(expression);
		
		std::string calculationId = expression->first_attribute("id")->value();
		std::string calculationResult = std::to_string((*calculation)());

		calculationResults.push_back(std::make_pair(calculationId, calculationResult));
	}

	xml_document<> outputXML;

	createOutputXML(outputXML, calculationResults);

	std::cout << outputXML;
}

} // namespace XMLParser;
} // namespace XMLCalculator