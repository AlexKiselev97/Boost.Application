// -----------------------------------------------------------------------------
// limit_single_instance_boost_interprocess_named_mutex.cpp : examples that
// show how use Boost.Application to make a simplest interactive
// (terminal) application 
//
// Note 1: The Boost.Application (Aspects v4) and this sample are in 
//         development process.
// -----------------------------------------------------------------------------

// Copyright 2011-2013 Renato Tegon Forti
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// -----------------------------------------------------------------------------

#define BOOST_ALL_DYN_LINK
#define BOOST_LIB_DIAGNOSTIC

// Single instance mechanism that will support aspect based on
// Boost.Interprocess Named Mutex too.
#define ENABLE_BOOST_INTERPROCESS_NAMED_MUTEX

#include <iostream>
#include <boost/application.hpp>
#include <boost/uuid/string_generator.hpp>

using namespace boost;

// we have a bug here. on windows the destructor of 
// limit_single_instance_named_mutex_behaviour never is called, this cause
// to Named Mutex to not be released, need fix

class myapp
{
public:

   // param
   int operator()(application::context& context)
   {
      
      if(context.has_aspect<application::args>())
      {
         std::vector<std::string> arg_vector = 
            context.use_aspect<application::args>().arg_vector();

         // only print args on screen
         for(std::vector<std::string>::iterator it = arg_vector.begin(); 
            it != arg_vector.end(); ++it) {
            std::cout << *it << std::endl;
         }
      }

      context.use_aspect<application::wait_for_termination_request>().wait();

      return 0;
   }
};

// main

int main(int argc, char *argv[])
{  
   BOOST_APPLICATION_FEATURE_SELECT

   myapp app;
   application::context app_context;

   boost::uuids::string_generator gen;

   app_context.add_aspect<application::limit_single_instance>(
      make_shared<application::limit_single_instance_named_mutex_behaviour>(
         gen("{0F1164AD-ECA5-175D-8784-4BAA329EF9F2}")));

   return application::launch<application::common>(app, app_context);
}
