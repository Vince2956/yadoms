#include "stdafx.h"
#include "Application.h"
#include "logConfiguration/LogConfiguration.h"

#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/ErrorHandler.h>
#include <Poco/NestedDiagnosticContext.h>

#include <Poco/Task.h>
#include <Poco/TaskManager.h>
#include <shared/Log.h>

#include "Supervisor.h"
#include <tools/OperatingSystem.h>
#include <csignal>
#include "ErrorHandler.h"

//define the main entry point
POCO_SERVER_MAIN(CYadomsServer)

CYadomsServer::CYadomsServer()
:m_helpRequested(false), m_startupOptions(config())
{
   //define unixstyle for command line parsing
   //so in Windows platform we use --option and -o for options (instead of /option)
   setUnixOptions(true);
}

CYadomsServer::~CYadomsServer()
{

}


void CYadomsServer::initialize(Application& self)
{
   loadConfiguration(); // load default configuration files, if present
   Poco::Util::ServerApplication::initialize(self);

   logConfiguration::CLogConfiguration::configure(m_startupOptions.getLogLevel());
}

void CYadomsServer::uninitialize()
{
   logger().information("shutting down");
   ServerApplication::uninitialize();
}

void CYadomsServer::defineOptions(Poco::Util::OptionSet& options)
{
   //configure Poco::Application options
   ServerApplication::defineOptions(options);
   
   //manage only help option
   options.addOption(
      Poco::Util::Option("help", "h", "display help information on command line arguments")
      .required(false)
      .repeatable(false)
      .callback(Poco::Util::OptionCallback<CYadomsServer>(this, &CYadomsServer::handleHelp)));
   
   //configure startup yadoms options
   m_startupOptions.defineOptions(options);
}

void CYadomsServer::handleHelp(const std::string& name, const std::string& value)
{
   m_helpRequested = true;
   displayHelp();
   stopOptionsProcessing();
}

void CYadomsServer::displayHelp()
{
   Poco::Util::HelpFormatter helpFormatter(options());
   helpFormatter.setCommand(commandName());
   helpFormatter.setUsage("OPTIONS");
   helpFormatter.setHeader("Yadoms command line usage");
   helpFormatter.format(std::cout);
}

int CYadomsServer::main(const Poco::Util::Application::ArgVec& args)
{
   if (!m_helpRequested)
   {
      YADOMS_LOG_CONFIGURE("Main");

      YADOMS_LOG(information) << "********************************************************************";
      YADOMS_LOG(information) << "Yadoms is starting";
      YADOMS_LOG(information) << "********************************************************************";
      YADOMS_LOG(information) << "Startup options :";
      YADOMS_LOG(information) << "\tlog level = " << m_startupOptions.getLogLevel();
      YADOMS_LOG(information) << "\tWeb server port number = " << m_startupOptions.getWebServerPortNumber();
      YADOMS_LOG(information) << "\tWeb server ip = " << m_startupOptions.getWebServerIPAddress();
      YADOMS_LOG(information) << "\tWeb server path = " << m_startupOptions.getWebServerInitialPath();
      YADOMS_LOG(information) << "\tdb path = " << m_startupOptions.getDatabaseFile();
      if (m_startupOptions.getNoPasswordFlag())
         YADOMS_LOG(information) << "\tnoPassword = true";
      YADOMS_LOG(information) << "********************************************************************";

      //configure the Poco ErrorHandler
      CErrorHandler eh;
      Poco::ErrorHandler* pOldEH = Poco::ErrorHandler::set(&eh);

      CSupervisor supervisor(m_startupOptions, *this);
      Poco::Thread thread("Supervisor");
      thread.start(supervisor);
      waitForTerminationRequest();

      supervisor.requestToStop();
      thread.join();

      //restore Poco ErrorHandler
      Poco::ErrorHandler::set(pOldEH);
   }
   return Poco::Util::Application::EXIT_OK;
}


void CYadomsServer::requestToStop(EStopMode stopMode) const
{
   switch (stopMode)
   {
      case IApplicationStopHandler::kStopSystem: 
         tools::COperatingSystem::shutdown(false); 
         break;
      case IApplicationStopHandler::kRestartSystem: 
         tools::COperatingSystem::shutdown(true); 
         break;
   }
   Poco::Util::ServerApplication::terminate();
}

//#include "Application.h"
//#include "logConfiguration/LogConfiguration.h"
//#include "startupOptions/Loader.h"
//#include <shared/Log.h>
//#include <tools/OperatingSystem.h>
//
//CApplication::CApplication()
//{
//}
//   
//
//CApplication::~CApplication()
//{
//   if (!!m_supervisor)
//   {
//      switch(m_supervisor->stopMode())
//      {
//      case IApplicationStopHandler::kStopSystem: tools::COperatingSystem::shutdown(false); break;
//      case IApplicationStopHandler::kRestartSystem: tools::COperatingSystem::shutdown(true); break;
//      default: break;
//      }
//   }
//}
//   
//void CApplication::configure(int argc, char ** argv)
//{
//   m_startupOptions.reset(new startupOptions::CLoader(argc, argv));
//
//   boost::filesystem::path full_path(boost::filesystem::initial_path<boost::filesystem::path>());
//   full_path = boost::filesystem::system_complete(boost::filesystem::path(argv[0]));
//
//   logConfiguration::CLogConfiguration::configure(m_startupOptions->getLogLevel());
//}
//
//int CApplication::run()
//{
//  try
//   {
//
//      YADOMS_LOG_CONFIGURE("Main");
//
//      YADOMS_LOG(information) << "********************************************************************";
//      YADOMS_LOG(information) << "Yadoms is starting";
//      YADOMS_LOG(information) << "********************************************************************";
//      YADOMS_LOG(information) << "Startup options :";
//      YADOMS_LOG(information) << "\tlog level = " << m_startupOptions->getLogLevel();
//      YADOMS_LOG(information) << "\tWeb server port number = " << m_startupOptions->getWebServerPortNumber();
//      YADOMS_LOG(information) << "\tWeb server ip = " << m_startupOptions->getWebServerIPAddress();
//      YADOMS_LOG(information) << "\tWeb server path = " << m_startupOptions->getWebServerInitialPath();
//      YADOMS_LOG(information) << "\tdb path = " << m_startupOptions->getDatabaseFile();
//      if (m_startupOptions->getNoPasswordFlag())
//         YADOMS_LOG(information) << "\tnoPassword = true";
//      YADOMS_LOG(information) << "********************************************************************";
//
//      startupOptions::IStartupOptions & opt = *m_startupOptions.get();
//
//      m_supervisor.reset(new CSupervisor(opt));
//
//      // The main job
//      m_supervisor->doWork();
//
//      YADOMS_LOG(information) << "Yadoms is stopped ";
//   }
//   catch(...)
//   {
//      //dual logging in case logger fails/throws
//      std::cout << "An unhandled exception occurred. Yadoms is now stopped" << std::endl;
//      YADOMS_LOG(fatal) << "An unhandled exception occurred. Yadoms is now stopped";
//      BOOST_ASSERT_MSG(false, "Yadoms exited with error, see console for details");
//   }
//
//   return 0;
//}
//
//void CApplication::stop(boost::function<void()> & callbackAfterStopped)
//{
//   if (m_supervisor)
//   {
//      m_supervisor->requestToStop(callbackAfterStopped);
//   }
//}

