/*
** Logger.hpp for r-type in /home/god/TEK3/C++/R-type/includes/logger/Logger.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Jan 15 16:37:24 2018 Maxime PILLON
** Last update Mon Jan 15 16:37:24 2018 Maxime PILLON
*/

#pragma once

# include <vector>
# include <string>
# include <fstream>
# include <iostream>

# ifdef WIN32 /* if you are on windows */

#  ifndef LOGGER_CONF_PATHNAME
#   define LOGGER_CONF_PATHNAME "%~dp0\log\logger.conf"
#  endif //!LOGGER_CONF_PATHNAME

#  ifndef BASIC_DEBUG_LOG_FILE
#   define BASIC_DEBUG_LOG_FILE "%~dp0\log\indie.log"
#  endif //!BASIC_DEBUG_LOG_FILE

#  ifndef BASIC_INFO_LOG_FILE
#   define BASIC_INFO_LOG_FILE "%~dp0\log\indie.log"
#  endif //!BASIC_INFO_LOG_FILE

#  ifndef BASIC_WARNING_LOG_FILE
#   define BASIC_WARNING_LOG_FILE "%~dp0\log\indie.log"
#  endif //!BASIC_WARNING_LOG_FILE

#  ifndef BASIC_ERROR_LOG_FILE
#   define BASIC_ERROR_LOG_FILE "%~dp0\log\indie.log"
#  endif //!BASIC_ERROR_LOG_FILE

#  ifndef BASIC_CRITICAL_LOG_FILE
#   define BASIC_CRITICAL_LOG_FILE "%~dp0\log\indie.log"
#  endif //!BASIC_CRITICAL_LOG_FILE

# else /* defined (linux cause error)*/

#  ifndef LOGGER_CONF_PATHNAME
#   define LOGGER_CONF_PATHNAME "log/logger.conf"
#  endif //!LOGGER_CONF_PATHNAME

#  ifndef BASIC_DEBUG_LOG_FILE
#   define BASIC_DEBUG_LOG_FILE "log/indie.log"
#  endif //!BASIC_DEBUG_LOG_FILE

#  ifndef BASIC_INFO_LOG_FILE
#   define BASIC_INFO_LOG_FILE "log/indie.log"
#  endif //!BASIC_INFO_LOG_FILE

#  ifndef BASIC_WARNING_LOG_FILE
#   define BASIC_WARNING_LOG_FILE "log/indie.log"
#  endif //!BASIC_WARNING_LOG_FILE

#  ifndef BASIC_ERROR_LOG_FILE
#   define BASIC_ERROR_LOG_FILE "log/indie.log"
#  endif //!BASIC_ERROR_LOG_FILE

#  ifndef BASIC_CRITICAL_LOG_FILE
#   define BASIC_CRITICAL_LOG_FILE "log/indie.log"
#  endif //!BASIC_CRITICAL_LOG_FILE

# endif

/// \namespace logger
namespace logger
{
  /// \enum log_type
  enum log_type
  {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    CRITICAL = 4
  };

  /// \struct s_typo
  typedef struct s_typo
  {
    std::string format; //!< format of the log level
    std::ofstream file; //!< ofstream which pointed where put log
  }		t_typo;

  /// \class Logger
  class Logger {
  public:
    /// \brief Function to get the Logger or create it if he hasn't be created yet.
    /// \return Return the logger object.
    static Logger &getLogger();

    /// \brief Function which permits to throw log.
    /// \param type is the level of log (DEBUG | INFO ... | CRITICAL)
    /// \param logMsg the message associated to the log to print.
    void log(log_type type, std::string const& logMsg);

  private:
    /// \brief Function to replace {{date}} by the actual date.
    /// \param fmt the format string put in logger.conf
    void formatDate(std::string& fmt) const;

    /// \brief Function to replace {{message}} by the message the user try to throw
    /// \param fmt the format string put in logger.conf
    /// \param msg the message the user try yo throw
    void formatMsg(std::string& fmt, std::string const& msg)const ;

  private:
    /// \brief This is the constructor of logger object.
    /// This constructor is private because only getLogger method can call it.
    Logger();

    /// \brief This is the destructor of logger object.
    ~Logger();

    /// \brief Copy operator.
    /// \param other, The logger to copy
    /// \return *this
    Logger &operator=(Logger const &other) {static_cast<void>(other); return *this; };

    /// \brief Do nothing just for good working of singleton
    /// \param other useless
    Logger(Logger const &other) {static_cast<void>(other);};

  private:
    log_type _logLevel;
    std::vector<t_typo> _logs;
    static Logger m_instance;

  private:
    class Parser
    {
    private:
      static bool isReadable(std::string const& pathname);

    public:
      static bool getLogLevel(std::string const& pathname, log_type& typo);
      static bool getDebug(std::string const& pathname, t_typo& typo);
      static bool getInfo(std::string const& pathname, t_typo& typo);
      static bool getWarning(std::string const& pathname, t_typo& typo);
      static bool getError(std::string const& pathname, t_typo& typo);
      static bool getCritical(std::string const& pathname, t_typo& typo);
    };

  };
}
