#include "Logger.hpp"

char Logger::m_logBuffer[m_nBuffer] = "";

void Logger::onAppendMsgToLog(const char* msg)
{
  if (std::strlen(m_logBuffer) + std::strlen(msg) < m_nBuffer)
    strcat_s(m_logBuffer, m_nBuffer, msg);
  else
    std::memset(m_logBuffer, 0, sizeof(m_logBuffer));
}

void Logger::onWriteToFile(const char* msg)
{
  m_output.open("Logs.txt", std::ios::app);
  if (m_output.is_open())
  {
    m_output << msg;
    m_output.close();
  }
  else
    onAppendMsgToLog("Can't write to file!\n");
}