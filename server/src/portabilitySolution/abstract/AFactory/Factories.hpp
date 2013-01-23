//
// IFactory.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/abstract/IFactory
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 15:56:28 2012 luca savarino
// Last update Thu Jan 10 17:34:35 2013 luca savarino
//

#ifndef FACTORIES__
# define	FACTORIES__

# ifdef _WIN32
#  include "WinFactory.hpp"
typedef creation::windowscreation::WinFactory	Factory;
# else
#  include "LinuxFactory.hpp"
namespace creation
{
  typedef creation::linuxcreation::LinuxFactory	Factory;
}
# endif

#endif
