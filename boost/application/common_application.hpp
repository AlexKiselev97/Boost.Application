// common_application.hpp ----------------------------------------------------//
// -----------------------------------------------------------------------------

// Copyright 2011-2013 Renato Tegon Forti

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// -----------------------------------------------------------------------------

// Revision History
// 10-10-2013 dd-mm-yyyy - Initial Release

// -----------------------------------------------------------------------------

#ifndef BOOST_APPLICATION_COMMON_APPLICATION_HPP
#define BOOST_APPLICATION_COMMON_APPLICATION_HPP

#include <boost/application/config.hpp>
#include <boost/application/context.hpp>
#include <boost/application/detail/app.hpp>
// platform dependent
#if defined( BOOST_WINDOWS_API )
#include <boost/application/detail/windows/common_application_impl.hpp>
#elif defined( BOOST_POSIX_API )
#include <boost/application/detail/posix/common_application_impl.hpp>
#else
#error "Sorry, no boost application are available for this platform."
#endif

namespace boost { namespace application {

   /*!
    * \brief This class hold a application mode system. 
    *  
    * common : Can be seen as Terminal/Console/Interactive 
    *          aplication type. 
    *  
    * An application mode is a collection of aspects that 
    * define application instantiation and behaviour. 
    *  
    * The usual use of this class is to pass it as 
    * template param on launch free function. 
    * 
    */
   class common : public app
   {

   public:

      /*!
       * Creates a common application.
       *
       * \param context An context of application, that hold all
       *        aspects.
       * 
       * \param ec Variable (boost::system::error_code) that will be 
       *        set to the result of the operation.
       * 
       * Check ec for errors.
       * 
       */

      template <typename Application>
      common(Application& myapp, application::context &context, boost::system::error_code& ec)
         : app(context, ec)
      {
         BOOST_APPLICATION_FEATURE_SELECT

         if(ec) return;

         // default aspects patterns added to this kind of application

         context_.add_aspect_if_not_exists<run_mode>(
            make_shared<run_mode>(run_mode::common));

         impl_.reset(new common_application_impl(
            boost::bind<int>( &Application::operator(), &myapp, _1), context, ec)); 
      }

      template <typename Application>
      common(Application& myapp, singularity<application::context> &context, boost::system::error_code& ec)
         : app(context.get_global(), ec)
      {
         BOOST_APPLICATION_FEATURE_SELECT

         if(ec) return;

         // default aspects patterns added to this kind of application

         context_.add_aspect_if_not_exists<run_mode>(
            make_shared<run_mode>(run_mode::common));

         impl_.reset(new common_application_impl(
            boost::bind<int>( &Application::operator(), &myapp), context, ec));
      }

      int run()
      {
         return impl_->run();
      }

      /*!
       * Destruct an common application.
       *
       */
      virtual ~common() 
      {
      }

   private:

      BOOST_APPLICATION_FEATURE_NS_SELECT::
         shared_ptr<common_application_impl> impl_;

   };

}} // boost::application 

#endif // BOOST_APPLICATION_COMMON_APPLICATION_HPP
       