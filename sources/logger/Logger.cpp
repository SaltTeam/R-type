/*
** Logger.cpp for r-type in /home/god/TEK3/C++/R-type/sources/logger/Logger.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Jan 15 16:37:13 2018 Maxime PILLON
** Last update Mon Jan 15 16:37:13 2018 Maxime PILLON
*/

#include <chrono>
#include <regex>
#include <cstring>
#include "logger/Logger.hpp"

namespace logger {
    Logger Logger::m_instance = Logger();

    Logger::Logger() : _logLevel(Debug), _logs(5) {
	Parser::getLogLevel(LOGGER_CONF_PATHNAME, this->_logLevel);
	Parser::getDebug(LOGGER_CONF_PATHNAME, this->_logs[Debug]);
	Parser::getInfo(LOGGER_CONF_PATHNAME, this->_logs[Info]);
	Parser::getWarning(LOGGER_CONF_PATHNAME, this->_logs[Warning]);
	Parser::getError(LOGGER_CONF_PATHNAME, this->_logs[Error]);
	Parser::getCritical(LOGGER_CONF_PATHNAME, this->_logs[Critical]);
    }

    Logger::~Logger() {
	this->_logs[Debug].file.close();
	this->_logs[Info].file.close();
	this->_logs[Warning].file.close();
	this->_logs[Error].file.close();
	this->_logs[Critical].file.close();
    }

    Logger &Logger::getLogger() {
	return m_instance;
    }

    void Logger::formatDate(std::string &fmt) const {
	size_t it;
	std::string date;
	std::time_t time;

	time = std::chrono::system_clock::to_time_t(
	    std::chrono::system_clock::now());
	date = std::ctime(&time);
	date.erase(--date.end());
	it = fmt.find("{{date}}");
	while (it != std::string::npos) {
	    fmt.replace(it, 8, date);
	    it = fmt.find("{{date}}");
	}
    }

    void Logger::formatMsg(std::string &fmt, std::string const &msg) const {
	size_t it;

	it = fmt.find("{{message}}");
	while (it != std::string::npos) {
	    fmt.replace(it, 11, msg);
	    it = fmt.find("{{message}}");
	}
    }

    void Logger::log(log_type type, std::string const &logMsg) {
	if (type < this->_logLevel)
	    return;

	std::string fmt = this->_logs[type].format;
	this->formatDate(fmt);
	this->formatMsg(fmt, logMsg);
	this->_logs[type].file << fmt << std::endl;
    }

    /*
     *
     * Parser class definition
     *
     */
    bool Logger::Parser::isReadable(std::string const &pathname) {
	std::ofstream file(pathname, std::ios::in);
	if (!file.is_open())
	    return false;
	file.close();
	return true;

    }

    bool
    Logger::Parser::getLogLevel(std::string const &pathname, log_type &typo) {
	if (!isReadable(pathname)) {
	    //todo log can't open logger.conf
	    typo = Info;
	    return false;
	}
	std::ifstream file(pathname, std::ios::in);
	std::string line;
	std::cmatch cm;
	std::getline(file, line);
	if (std::regex_match(line.c_str(), cm, std::regex("LOGLEVEL (.*)"))) {
	    if (!std::strcmp(cm[1].str().c_str(), "DEBUG"))
		typo = Debug;
	    else if (!std::strcmp(cm[1].str().c_str(), "INFO"))
		typo = Info;
	    else if (!std::strcmp(cm[1].str().c_str(), "WARNING"))
		typo = Warning;
	    else if (!std::strcmp(cm[1].str().c_str(), "ERROR"))
		typo = Error;
	    else if (!std::strcmp(cm[1].str().c_str(), "CRITICAL"))
		typo = Critical;
	    return true;
	}
	typo = Info;
	return true;
    }

    bool Logger::Parser::getDebug(std::string const &pathname, t_typo &typo) {
	if (!isReadable(pathname)) {
	    std::clog << "Can't open logger.conf file" << std::endl;
	    typo.file = std::ofstream(BASIC_DEBUG_LOG_FILE, std::ios::out | std::ios::app);
	    if (!typo.file.is_open())
		std::clog << "Can't open basic debug log file" << std::endl;
	    typo.format = "[DEBUG] {{date}} - {{message}}";
	    return false;
	}
	std::ifstream file(pathname, std::ios::in);
	std::string line;
	std::cmatch cm;
	bool find_typo = false;
	while (std::getline(file, line))
	    if (std::regex_match(line.c_str(), cm, std::regex("DEBUG \"(.*)\" \"(.*)\""))) {
		typo.format = cm[2].str();
		typo.file = std::ofstream(cm[1].str(), std::ios::out | std::ios::app);
		if (!typo.file.is_open()) {
		    std::clog << "can't open the specified debug file in logger.conf" << std::endl;
		}
		find_typo = true;
	    }
	if (!find_typo) {
	    std::clog << "Don't have a section DEBUG in your conf file" << std::endl;
	    typo.file = std::ofstream(BASIC_DEBUG_LOG_FILE, std::ios::out | std::ios::app);
	    if (!typo.file.is_open())
		std::clog << "Can't open basic debug log file" << std::endl;
	    typo.format = "[DEBUG] {{date}} - {{message}}";
	    return false;
	}
	return true;
    }

    bool Logger::Parser::getInfo(std::string const &pathname, t_typo &typo) {
	if (!isReadable(pathname)) {
	    std::clog << "Can't open logger.conf file" << std::endl;
	    typo.file = std::ofstream(BASIC_INFO_LOG_FILE, std::ios::out | std::ios::app);
	    if (!typo.file.is_open())
		std::clog << "Can't open basic info log file" << std::endl;
	    typo.format = "[INFO] {{date}} - {{message}}";
	    return false;
	}
	std::ifstream file(pathname, std::ios::in);
	std::string line;
	std::cmatch cm;
	bool find_typo = false;
	while (std::getline(file, line))
	    if (std::regex_match(line.c_str(), cm, std::regex("INFO \"(.*)\" \"(.*)\""))) {
		typo.format = cm[2].str();
		typo.file = std::ofstream(cm[1].str(), std::ios::out | std::ios::app);
		if (!typo.file.is_open()) {
		    std::clog << "can't open the specified info file in logger.conf" << std::endl;
		}
		find_typo = true;
	    }
	if (!find_typo) {
	    std::clog << "Don't have a section INFO in your conf file" << std::endl;
	    typo.file = std::ofstream(BASIC_INFO_LOG_FILE, std::ios::out | std::ios::app);
	    if (!typo.file.is_open())
		std::clog << "Can't open basic info log file" << std::endl;
	    typo.format = "[INFO] {{date}} - {{message}}";
	    return false;
	}
	return true;
    }

    bool Logger::Parser::getWarning(std::string const &pathname, t_typo &typo) {
	if (!isReadable(pathname)) {
	    std::clog << "Can't open logger.conf file" << std::endl;
	    typo.file = std::ofstream(BASIC_WARNING_LOG_FILE, std::ios::out | std::ios::app);
	    if (!typo.file.is_open())
		std::clog << "Can't open basic warning log file" << std::endl;
	    typo.format = "[WARNING] {{date}} - {{message}}";
	    return false;
	}
	std::ifstream file(pathname, std::ios::in);
	std::string line;
	std::cmatch cm;
	bool find_typo = false;
	while (std::getline(file, line))
	    if (std::regex_match(line.c_str(), cm, std::regex("WARNING \"(.*)\" \"(.*)\""))) {
		typo.format = cm[2].str();
		typo.file = std::ofstream(cm[1].str(), std::ios::out | std::ios::app);
		if (!typo.file.is_open()) {
		    std::clog << "can't open the specified warning file in logger.conf" << std::endl;
		}
		find_typo = true;
	    }
	if (!find_typo) {
	    std::clog << "Don't have a section WARNING in your conf file" << std::endl;
	    typo.file = std::ofstream(BASIC_WARNING_LOG_FILE, std::ios::out | std::ios::app);
	    if (!typo.file.is_open())
		std::clog << "Can't open basic warning log file" << std::endl;
	    typo.format = "[WARNING] {{date}} - {{message}}";
	    return false;
	}
	return true;
    }

    bool Logger::Parser::getError(std::string const &pathname, t_typo &typo) {
	if (!isReadable(pathname)) {
	    std::clog << "Can't open logger.conf file" << std::endl;
	    typo.file = std::ofstream(BASIC_ERROR_LOG_FILE, std::ios::out | std::ios::app);
	    if (!typo.file.is_open())
		std::clog << "Can't open basic error log file" << std::endl;
	    typo.format = "[ERROR] {{date}} - {{message}}";
	    return false;
	}
	std::ifstream file(pathname, std::ios::in);
	std::string line;
	std::cmatch cm;
	bool find_typo = false;
	while (std::getline(file, line))
	    if (std::regex_match(line.c_str(), cm, std::regex("ERROR \"(.*)\" \"(.*)\""))) {
		typo.format = cm[2].str();
		typo.file = std::ofstream(cm[1].str(), std::ios::out | std::ios::app);
		if (!typo.file.is_open()) {
		    std::clog << "can't open the specified error file in logger.conf" << std::endl;
		}
		find_typo = true;
	    }
	if (!find_typo) {
	    std::clog << "Don't have a section ERROR in your conf file" << std::endl;
	    typo.file = std::ofstream(BASIC_ERROR_LOG_FILE, std::ios::out | std::ios::app);
	    if (!typo.file.is_open())
		std::clog << "Can't open basic error log file" << std::endl;
	    typo.format = "[ERROR] {{date}} - {{message}}";
	    return false;
	}
	return true;
    }

    bool
    Logger::Parser::getCritical(std::string const &pathname, t_typo &typo) {
	if (!isReadable(pathname)) {
	    std::clog << "Can't open logger.conf file" << std::endl;
	    typo.file = std::ofstream(BASIC_CRITICAL_LOG_FILE, std::ios::out | std::ios::app);
	    if (!typo.file.is_open())
		std::clog << "Can't open basic critical log file" << std::endl;
	    typo.format = "[CRITICAL] {{date}} - {{message}}";
	    return false;
	}
	std::ifstream file(pathname, std::ios::in);
	std::string line;
	std::cmatch cm;
	bool find_typo = false;
	while (std::getline(file, line))
	    if (std::regex_match(line.c_str(), cm, std::regex("CRITICAL \"(.*)\" \"(.*)\""))) {
		typo.format = cm[2].str();
		typo.file = std::ofstream(cm[1].str(), std::ios::out | std::ios::app);
		if (!typo.file.is_open()) {
		    std::clog << "can't open the specified critical file in logger.conf" << std::endl;
		}
		find_typo = true;
	    }
	if (!find_typo) {
	    std::clog << "Don't have a section CRITICAL in your conf file" << std::endl;
	    typo.file = std::ofstream(BASIC_CRITICAL_LOG_FILE, std::ios::out | std::ios::app);
	    if (!typo.file.is_open())
		std::clog << "Can't open basic critical log file" << std::endl;
	    typo.format = "[CRITICAL] {{date}} - {{message}}";
	    return false;
	}
	return true;
    }
}