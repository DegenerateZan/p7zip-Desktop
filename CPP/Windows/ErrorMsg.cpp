// Windows/ErrorMsg.h

#include "StdAfx.h"

#include "Windows/ErrorMsg.h"
#include "Common/StringConvert.h"

namespace NWindows {
namespace NError {

UString MyFormatMessage(DWORD errorCode)
{
  const char * txt = nullptr; // Use nullptr for null pointer initialization
  AString msg;

  switch(errorCode) {
    case ERROR_NO_MORE_FILES   : txt = "No more files"; break ;
    case static_cast<DWORD>(E_NOTIMPL)             : txt = "E_NOTIMPL"; break ;
    case static_cast<DWORD>(E_NOINTERFACE)         : txt = "E_NOINTERFACE"; break ;
    case static_cast<DWORD>(E_ABORT)               : txt = "E_ABORT"; break ;
    case static_cast<DWORD>(E_FAIL)                : txt = "E_FAIL"; break ;
    case static_cast<DWORD>(STG_E_INVALIDFUNCTION) : txt = "STG_E_INVALIDFUNCTION"; break ;
    case static_cast<DWORD>(E_OUTOFMEMORY)         : txt = "E_OUTOFMEMORY"; break ;
    case static_cast<DWORD>(E_INVALIDARG)          : txt = "E_INVALIDARG"; break ;
    case ERROR_DIRECTORY          : txt = "Error Directory"; break ;
    default:
      txt = strerror(static_cast<int>(errorCode)); // Cast errorCode to int for strerror
  }

  if (txt) {
    msg = txt;
  } else {
    char msgBuf[256];
    snprintf(msgBuf, sizeof(msgBuf), "error #%x", static_cast<unsigned>(errorCode)); // Cast errorCode to unsigned
    msgBuf[sizeof(msgBuf)-1] = 0;
    msg = msgBuf;
  }

  return MultiByteToUnicodeString(msg);
}

#if 0
bool MyFormatMessage(DWORD messageID, CSysString &message)
{
  const char * txt = 0;
  AString msg;

  switch(messageID) {
    case ERROR_NO_MORE_FILES   : txt = "No more files"; break ;
    case E_NOTIMPL             : txt = "E_NOTIMPL"; break ;
    case E_NOINTERFACE         : txt = "E_NOINTERFACE"; break ;
    case E_ABORT               : txt = "E_ABORT"; break ;
    case E_FAIL                : txt = "E_FAIL"; break ;
    case STG_E_INVALIDFUNCTION : txt = "STG_E_INVALIDFUNCTION"; break ;
    case E_OUTOFMEMORY         : txt = "E_OUTOFMEMORY"; break ;
    case E_INVALIDARG          : txt = "E_INVALIDARG"; break ;
    default:
      txt = strerror(messageID);
  }
  if (txt) {
    msg = txt;
  } else {
    char msgBuf[256];
    snprintf(msgBuf,sizeof(msgBuf),"error #%x",(unsigned)messageID);
    msgBuf[sizeof(msgBuf)-1] = 0;
    msg = msgBuf;
  }
  
  msg += "                ";

#ifdef _UNICODE
  message = MultiByteToUnicodeString(msg);
#else
  message = msg;
#endif
  return true;
}

#ifndef _UNICODE
bool MyFormatMessage(DWORD messageID, UString &message)
{
    CSysString messageSys;
    bool result = MyFormatMessage(messageID, messageSys);
    message = GetUnicodeString(messageSys);
    return result;
}
#endif

#endif

}}

