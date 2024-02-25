#pragma once
#include "../utils/ntshengn_defines.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>
#include <algorithm>
#include <numeric>

namespace NtshEngn {

	class Profiler {
	public:
		struct ResultNode {
			std::string name = "";

			std::vector<double> times;
			double totalTime = 0.0;
			double meanTime = 0.0;
			uint32_t minTimeIndex = 0;
			double minTime = 0.0;
			uint32_t maxTimeIndex = 0;
			double maxTime = 0.0;

			std::vector<ResultNode> children;
		};

	private:
		struct Node {
			std::string name = "";

			std::vector<double> times;
			double totalTime = 0.0;
			double meanTime = 0.0;
			uint32_t minTimeIndex = 0;
			double minTime = 0.0;
			uint32_t maxTimeIndex = 0;
			double maxTime = 0.0;

			double start;

			Node* parent = nullptr;
			std::vector<Node*> children;

			ResultNode getResults() const {
				ResultNode resultNode;
				resultNode.name = name;
				resultNode.times = times;
				resultNode.totalTime = totalTime;
				resultNode.meanTime = meanTime;
				resultNode.minTimeIndex = minTimeIndex;
				resultNode.minTime = times[resultNode.minTimeIndex];
				resultNode.maxTimeIndex = maxTimeIndex;
				resultNode.maxTime = maxTime;

				for (const Node* child : children) {
					resultNode.children.push_back(child->getResults());
				}

				return resultNode;
			}
		};

	public:
		void start(const std::string& sessionName) {
			if (!m_isRunning) {
				m_rootNode.name = sessionName;
				m_rootNode.start = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

				m_currentNode = &m_rootNode;

				m_isRunning = true;
			}
		}

		ResultNode getResults() {
			ResultNode resultNode;

			if (m_isRunning) {
				resultNode.name = m_rootNode.name;
				resultNode.totalTime = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() - m_rootNode.start;
				resultNode.times = { resultNode.totalTime };

				for (const Node* child : m_rootNode.children) {
					resultNode.children.push_back(child->getResults());
				}
			}

			return resultNode;
		}

		ResultNode end() {
			ResultNode resultNode = getResults();
			m_profilerNodes.clear();
			m_isRunning = false;

			return resultNode;
		}

		bool isRunning() const {
			return m_isRunning;
		}

		void startBlock(const std::string& blockName) {
			if (m_isRunning) {
				if (m_profilerNodes.find(blockName) == m_profilerNodes.end()) {
					Node newProfilerNode;
					newProfilerNode.name = blockName;
					newProfilerNode.parent = m_currentNode;
					m_profilerNodes[blockName] = newProfilerNode;
					
					m_currentNode->children.push_back(&m_profilerNodes[blockName]);
				}
				Node* profilerNode = &m_profilerNodes[blockName];

				m_currentNode = profilerNode;

				profilerNode->start = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
			}
		}

		void endBlock() {
			if (m_isRunning) {
				if (m_currentNode != &m_rootNode) {
					const double blockTime = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() - m_currentNode->start;

					m_currentNode->times.push_back(blockTime);
					m_currentNode->totalTime += blockTime;
					if (m_currentNode->times.size() > 1) {
						m_currentNode->meanTime = m_currentNode->totalTime / static_cast<double>(m_currentNode->times.size());
						m_currentNode->minTimeIndex = (blockTime < m_currentNode->minTime) ? static_cast<uint32_t>(m_currentNode->times.size() - 1) : m_currentNode->minTimeIndex;
						m_currentNode->minTime = (blockTime < m_currentNode->minTime) ? blockTime : m_currentNode->minTime;
						m_currentNode->maxTimeIndex = (blockTime > m_currentNode->maxTime) ? static_cast<uint32_t>(m_currentNode->times.size() - 1) : m_currentNode->maxTimeIndex;
						m_currentNode->maxTime = (blockTime > m_currentNode->maxTime) ? blockTime : m_currentNode->maxTime;
					}
					else {
						m_currentNode->meanTime = m_currentNode->totalTime;
						m_currentNode->minTimeIndex = 0;
						m_currentNode->minTime = blockTime;
						m_currentNode->maxTimeIndex = 0;
						m_currentNode->maxTime = blockTime;
					}

					m_currentNode = m_currentNode->parent;
				}
			}
		}

	public:
		static std::string to_string(const ResultNode& resultNode) {
			return to_string(resultNode, 0, false);
		}

	private:
		static std::string to_string(const ResultNode& resultNode, size_t indentationLevel, bool indentFirst) {
			std::string resultNodeString = indentFirst ? std::string(indentationLevel, '\t') : "";

			resultNodeString += resultNode.name + ": Count: " + std::to_string(resultNode.times.size()) + ", Total: " + std::to_string(resultNode.totalTime) + "ms, Mean: " + std::to_string(resultNode.meanTime) + "ms, Min: " + std::to_string(resultNode.minTime) + "ms (" + std::to_string(resultNode.minTimeIndex) + "), Max: " + std::to_string(resultNode.maxTime) + "ms (" + std::to_string(resultNode.maxTimeIndex) + ").\n";
			for (const ResultNode& child : resultNode.children) {
				resultNodeString += to_string(child, indentationLevel + 1, true);
			}

			return resultNodeString;
		}

	private:
		std::unordered_map<std::string, Node> m_profilerNodes;
		Node m_rootNode;
		Node* m_currentNode = nullptr;

		bool m_isRunning = false;
	};

}