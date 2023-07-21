#pragma once
#include "ntshengn_defines.h"
#include <string>
#include <fstream>
#include <vector>
#include <forward_list>
#include <unordered_map>
#include <variant>

#if defined(NTSHENGN_DEBUG)
#define NTSHENGN_JSON_INFO(message) \
	do { \
		std::cerr << "\33[1m\33[37mJSON \33[34mINFO\33[39m\33[0m: " << message << std::endl; \
	} while(0)
#else
#define NTSHENGN_JSON_INFO(message) \
	do { \
	} while(0)
#endif

#if defined(NTSHENGN_DEBUG)
#define NTSHENGN_JSON_WARNING(message) \
	do { \
		std::cerr << "\33[1m\33[37mJSON \33[93mWARNING\33[39m\33[0m: " << message << std::endl; \
	} while(0)
#else
#define NTSHENGN_JSON_WARNING(message) \
	do { \
	} while(0)
#endif

#if defined(NTSHENGN_DEBUG)
#define NTSHENGN_JSON_ERROR(message, code) \
	do { \
		std::cerr << "\33[1m\33[37mJSON \33[31mERROR\33[39m\33[0m: " << message << " (" << #code << ")" << std::endl; \
		exit(1); \
	} while(0)
#else
#define NTSHENGN_JSON_ERROR(message, code) \
	do { \
		exit(1); \
	} while(0)
#endif

namespace NtshEngn {

	namespace JSON {

		enum class Type {
			Object,
			Number,
			String,
			Array,
			Boolean,
			Null
		};

		class Node {
		public:
			// Construct JSON::Type::Object
			Node(const std::unordered_map<std::string, Node*> children) : m_type(Type::Object), m_value(children) {}

			// Construct JSON::Type::Number
			Node(float number) : m_type(Type::Number), m_value(number) {}

			// Construct JSON::Type::String
			Node(const std::string& string) : m_type(Type::String), m_value(string) {}

			// Construct JSON::Type::Array
			Node(const std::vector<Node*>& array) : m_type(Type::Array), m_value(array) {}

			// Construct JSON::Type::Boolean
			Node(bool boolean) : m_type(Type::Boolean), m_value(boolean) {}

			// Construct JSON::Type::Null
			Node() : m_type(Type::Null), m_value() {}

			Type getType() {
				return m_type;
			}

			// Access JSON::Type::Object
			const Node* operator[](const std::string& childName) {
				NTSHENGN_ASSERT(m_type == Type::Object);
				const std::unordered_map<std::string, Node*>& valObject = std::get<std::unordered_map<std::string, Node*>>(m_value);
				NTSHENGN_ASSERT(valObject.find(childName) != valObject.end());

				return valObject.at(childName);
			}

			// Access JSON::Type::Number
			float getNumber() {
				NTSHENGN_ASSERT(m_type == Type::Number);
				const float valNumber = std::get<float>(m_value);

				return valNumber;
			}

			// Access JSON::Type::String
			std::string getString() {
				NTSHENGN_ASSERT(m_type == Type::String);
				const std::string& val = std::get<std::string>(m_value);

				return val;
			}

			// Access JSON::Type::Array
			const Node* operator[](const size_t element) {
				NTSHENGN_ASSERT(m_type == Type::Array);
				const std::vector<Node*>& val = std::get<std::vector<Node*>>(m_value);
				NTSHENGN_ASSERT(element < val.size());

				return val.at(element);
			}

			// Access JSON::Type::Boolean
			bool getBoolean() {
				NTSHENGN_ASSERT(m_type == Type::Boolean);
				const bool val = std::get<bool>(m_value);

				return val;
			}

			// Add object to JSON::Type::Object
			void addObject(const std::string& childName, Node* childNode) {
				NTSHENGN_ASSERT((m_type == Type::Object) || (m_type == Type::Null));
				std::unordered_map<std::string, Node*>& val = std::get<std::unordered_map<std::string, Node*>>(m_value);
				NTSHENGN_ASSERT(val.find(childName) == val.end());

				m_type = Type::Object;
				val[childName] = childNode;
			}

			// Set number to JSON::Type::Number
			void setNumber(float number) {
				NTSHENGN_ASSERT((m_type == Type::Number) || (m_type == Type::Null));
				float& val = std::get<float>(m_value);

				m_type = Type::Number;
				val = number;
			}

			// Set string to JSON::Type::String
			void setString(const std::string& string) {
				NTSHENGN_ASSERT((m_type == Type::String) || (m_type == Type::Null));
				std::string& val = std::get<std::string>(m_value);

				m_type = Type::String;
				val = string;
			}

			// Add object to JSON::Type::Array
			void addObject(Node* element) {
				NTSHENGN_ASSERT((m_type == Type::Array) || (m_type == Type::Null));
				std::vector<Node*>& val = std::get<std::vector<Node*>>(m_value);

				m_type = Type::Array;
				val.push_back(element);
			}

			// Set boolean to JSON::Type::Boolean
			void setBoolean(bool boolean) {
				NTSHENGN_ASSERT((m_type == Type::Boolean) || (m_type == Type::Null));
				bool& val = std::get<bool>(m_value);

				m_type = Type::Boolean;
				val = boolean;
			}

			std::string to_string(size_t indentationLevel, bool indentFirst = false) {
				std::string jsonString = "";
				const std::string indentation = std::string(indentationLevel, '\t');

				switch (m_type) {
				case Type::Object: {
					std::unordered_map<std::string, Node*>& val = std::get<std::unordered_map<std::string, Node*>>(m_value);
					jsonString += (indentFirst ? indentation : "") + "{\n";
					for (std::unordered_map<std::string, Node*>::iterator it = val.begin(); it != val.end(); it++) {
						jsonString += indentation + "\t\"" + it->first + "\": " + it->second->to_string(indentationLevel + 1);
						std::unordered_map<std::string, Node*>::iterator tmp = it;
						tmp++;
						jsonString += (tmp != val.end()) ? ",\n" : "\n";
					}
					jsonString += indentation + "}";
					break;
				}

				case Type::Number: {
					const float val = std::get<float>(m_value);
					jsonString += (indentFirst ? indentation : "") + std::to_string(val);
					break;
				}

				case Type::String: {
					const std::string& val = std::get<std::string>(m_value);
					jsonString += (indentFirst ? indentation : "") + "\"" + val + "\"";
					break;
				}

				case Type::Array: {
					std::vector<Node*>& val = std::get<std::vector<Node*>>(m_value);
					jsonString += (indentFirst ? indentation : "") + "[\n";
					for (size_t i = 0; i < val.size(); i++) {
						jsonString += val[i]->to_string(indentationLevel + 1, true);
						jsonString += (i < (val.size() - 1)) ? ",\n" : "\n";
					}
					jsonString += indentation + "]";
					break;
				}

				case Type::Boolean: {
					const bool val = std::get<bool>(m_value);
					jsonString += (indentFirst ? indentation : "") + (val ? "true" : "false");
					break;
				}

				case Type::Null: {
					jsonString += (indentFirst ? indentation : "") + "null";
					break;
				}

				default:
					break;
				}

				return jsonString;
			}

		private:
			Type m_type;
			std::variant<std::unordered_map<std::string, Node*>, float, std::string, std::vector<Node*>, bool> m_value;
		};

		std::forward_list<Node> nodes;

		enum class TokenType {
			CurlyBracketOpen,
			CurlyBracketClose,
			Colon,
			Comma,
			String,
			Number,
			ArrayBracketOpen,
			ArrayBracketClose,
			Boolean,
			Null,
			EndOfFile
		};

		struct Token {
			TokenType type;
			std::string value = "";
		};

		class Lexer {
		public:
			Lexer(const std::string& filePath) {
				m_file.open(filePath, std::fstream::in);
				if (!m_file.is_open()) {
					NTSHENGN_JSON_ERROR("Cannot open JSON file \"" + filePath + "\".", Result::JSONError);
				}
			}
			~Lexer() {
				if (m_file.is_open()) {
					m_file.close();
				}
			}

			char nextCharacter() {
				char c = ' ';
				while ((c == ' ') || (c == '\n') || (c == '\t')) {
					m_file.get(c);

					if (((c == ' ') || (c == '\n') || (c == '\t')) && m_file.eof()) {
						return '\0';
					}
				}

				return c;
			}

			Token getNextToken() {
				Token token;

				char c;

				if (m_file.eof()) {
					NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): reached end-of-file early.", Result::JSONError);
				}

				m_previousPosition = m_file.tellg();
				c = nextCharacter();
				if (c == '"') {
					token.type = TokenType::String;
					token.value = "";

					m_file.get(c);
					while (c != '\"') {
						token.value += c;

						m_file.get(c);
					}
				}
				else if (c == '{') {
					token.type = TokenType::CurlyBracketOpen;
				}
				else if (c == '}') {
					token.type = TokenType::CurlyBracketClose;
				}
				else if (c == '[') {
					token.type = TokenType::ArrayBracketOpen;
				}
				else if (c == ']') {
					token.type = TokenType::ArrayBracketClose;
				}
				else if (c == ':') {
					token.type = TokenType::Colon;
				}
				else if (c == ',') {
					token.type = TokenType::Comma;
				}
				else if (c == '-' || ((c >= '0') && (c <= '9'))) {
					token.type = TokenType::Number;
					token.value += c;

					size_t previousCharPosition;
					while ((c == '-') || (c == '.') || (c == 'e') || ((c >= '0') && (c <= '9'))) {
						previousCharPosition = m_file.tellg();
						m_file.get(c);

						if (m_file.eof()) {
							break;
						}

						if ((c == '-') || (c == '.') || (c == 'e') || ((c >= '0') && (c <= '9'))) {
							token.value += c;
						}
						else {
							m_file.seekg(previousCharPosition);
							break;
						}
					}
				}
				else if (c == 't') {
					token.type = TokenType::Boolean;
					token.value = "t";

					m_file.get(c);
					token.value += c;

					if (c == 'r') {
						m_file.get(c);
						token.value += c;

						if (c == 'u') {
							m_file.get(c);
							token.value += c;

							if (c != 'e') {
								NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): \"" + token.value + "\" token is invalid.", Result::JSONError);
							}
						}
						else {
							NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): \"" + token.value + "\" token is invalid.", Result::JSONError);
						}
					}
					else {
						NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): \"" + token.value + "\" token is invalid.", Result::JSONError);
					}
				}
				else if (c == 'f') {
					token.type = TokenType::Boolean;
					token.value = "f";

					m_file.get(c);
					token.value += c;

					if (c == 'a') {
						m_file.get(c);
						token.value += c;

						if (c == 'l') {
							m_file.get(c);
							token.value += c;

							if (c == 's') {
								m_file.get(c);
								token.value += c;

								if (c != 'e') {
									NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): \"" + token.value + "\" token is invalid.", Result::JSONError);
								}
							}
							else {
								NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): \"" + token.value + "\" token is invalid.", Result::JSONError);
							}
						}
						else {
							NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): \"" + token.value + "\" token is invalid.", Result::JSONError);
						}
					}
					else {
						NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): \"" + token.value + "\" token is invalid.", Result::JSONError);
					}
				}
				else if (c == 'n') {
					token.type = TokenType::Null;
					std::string nullValue = "n";

					m_file.get(c);
					nullValue += c;
					if (c == 'u') {
						m_file.get(c);
						nullValue += c;

						if (c == 'l') {
							m_file.get(c);
							nullValue += c;

							if (c != 'l') {
								NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): \"" + nullValue + "\" token is invalid.", Result::JSONError);
							}
						}
						else {
							NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): \"" + nullValue + "\" token is invalid.", Result::JSONError);
						}
					}
					else {
						NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): \"" + nullValue + "\" token is invalid.", Result::JSONError);
					}
				}
				else if (c == '\0') {
					token.type = TokenType::EndOfFile;
				}
				else {
					NTSHENGN_JSON_ERROR("JSON::Lexer::getNextToken(): reached an unknown token (\"" + std::string() + c + "\").", Result::JSONError);
				}

				return token;
			}

			bool endOfFile() {
				return m_file.eof();
			}

		private:
			std::fstream m_file;
			size_t m_previousPosition;
		};

		class Parser {
		public:
			Parser(Lexer& lexer) : m_lexer(lexer) {}

			Node parse() {
				Node root;
				bool rootInitialized = false;

				while (!m_lexer.endOfFile()) {
					Token token = m_lexer.getNextToken();
					Node node;
					switch (token.type) {
					case TokenType::CurlyBracketOpen: {
						node = parseObject();
						break;
					}

					case TokenType::String: {
						node = Node(token.value);
						break;
					}

					case TokenType::Number: {
						node = Node(std::stof(token.value));
						break;
					}

					case TokenType::ArrayBracketOpen: {
						node = parseArray();
						break;
					}

					case TokenType::Boolean: {
						node = Node(token.value == "true");
						break;
					}

					default:
						break;
					}

					if (!rootInitialized) {
						root = node;

						rootInitialized = true;
					}
				}

				return root;
			}

		private:
			Node parseObject() {
				Node objectNode = Node(std::unordered_map<std::string, Node*>());

				bool endOfObject = false;
				while (!endOfObject) {
					// Map key
					Token keyToken = m_lexer.getNextToken();

					// Empty object
					if (keyToken.type == TokenType::CurlyBracketClose) {
						return objectNode;
					}

					// Colon
					if (m_lexer.getNextToken().type != TokenType::Colon) {
						NTSHENGN_JSON_ERROR("An object key (\"" + keyToken.value + "\") is not followed by a colon.", Result::JSONError);
					}

					Token token = m_lexer.getNextToken();
					Node node;
					switch (token.type) {
					case TokenType::CurlyBracketOpen: {
						node = parseObject();
						break;
					}

					case TokenType::String: {
						node = Node(token.value);
						break;
					}

					case TokenType::Number: {
						node = Node(std::stof(token.value));
						break;
					}

					case TokenType::ArrayBracketOpen: {
						node = parseArray();
						break;
					}

					case TokenType::Boolean: {
						node = Node(token.value == "true");
						break;
					}

					case TokenType::EndOfFile: {
						NTSHENGN_JSON_ERROR("Reached end-of-file while parsing an object.", Result::JSONError);
					}

					default:
						break;
					}

					nodes.push_front(node);
					objectNode.addObject(keyToken.value, &nodes.front());

					// Next token is either a comma or a curly bracket close
					if (m_lexer.getNextToken().type == TokenType::CurlyBracketClose) {
						endOfObject = true;
					}
				}

				return objectNode;
			}

			Node parseArray() {
				Node arrayNode = Node(std::vector<Node*>());

				bool endOfArray = false;
				while (!endOfArray) {
					Token token = m_lexer.getNextToken();
					Node node;
					switch (token.type) {
					case TokenType::CurlyBracketOpen: {
						node = parseObject();
						break;
					}

					case TokenType::String: {
						node = Node(token.value);
						break;
					}

					case TokenType::Number: {
						node = Node(std::stof(token.value));
						break;
					}

					case TokenType::ArrayBracketOpen: {
						node = parseArray();
						break;
					}

					case TokenType::Boolean: {
						node = Node(token.value == "true");
						break;
					}

					case TokenType::EndOfFile: {
						NTSHENGN_JSON_ERROR("Reached end-of-file while parsing an array.", Result::JSONError);
					}

					default:
						break;
					}

					nodes.push_front(node);
					arrayNode.addObject(&nodes.front());

					// Next token is either a comma or an array bracket close
					if (m_lexer.getNextToken().type == TokenType::ArrayBracketClose) {
						endOfArray = true;
					}
				}

				return arrayNode;
			}

		private:
			Lexer& m_lexer;
		};

		Node read(const std::string& filePath) {
			Lexer lexer(filePath);
			Parser parser(lexer);

			return parser.parse();
		}

		std::string to_string(Node& root) {
			return root.to_string(0);
		}
	}

}