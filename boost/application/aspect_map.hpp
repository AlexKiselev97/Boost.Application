
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/role for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @file
 * @brief Defines the aspect map.
 *
 * Uses typeindex as internal key.
 *
 */


// Changes
// 
// 22-10-2013 dd-mm-yyyy - Renato Forti - Add replace_aspect method
// 23-10-2013 dd-mm-yyyy - Renato Forti - Add remove_aspect method
// 24-10-2013 dd-mm-yyyy - Renato Forti - Use BOOST_APPLICATION_FEATURE_NS_SELECT 
// 
// -----------------------------------------------------------------------------

#ifndef BOOST_ASPECT_MAP_HPP
#define BOOST_ASPECT_MAP_HPP

#include <boost/config.hpp>
#include <boost/application/config.hpp>
#include <utility>

namespace boost
{
  namespace entity
  {
    class aspect_map
    {
      typedef BOOST_APPLICATION_FEATURE_NS_SELECT::
         type_index key_type;

      typedef BOOST_APPLICATION_FEATURE_NS_SELECT::
         shared_ptr<void> value_type;

      typedef BOOST_APPLICATION_FEATURE_NS_SELECT::
         unordered_map<key_type, value_type> map_type;

      map_type aspects_;

    public:
      template <class T>
      void add_aspect(BOOST_APPLICATION_FEATURE_NS_SELECT::
                         shared_ptr<T> asp)
      {

#ifndef BOOST_NO_CXX11_HDR_TYPEINDEX
         key_type ti = typeid(T);
#else
         key_type ti = type_id<T>();
#endif

        if (!aspects_.insert(std::make_pair(ti, asp)).second) throw std::logic_error(
            std::string("Type ") + ti.name() + " already added as an aspect");
      }

      template <class T>
      bool has_aspect() const
      {
        return aspects_.cend() != aspects_.find(key_type(typeid(T)));
      }

      template <class T>
      BOOST_APPLICATION_FEATURE_NS_SELECT::
         shared_ptr<T> get_aspect()
      {
        map_type::const_iterator it = aspects_.find(key_type(typeid(T)));
        if (aspects_.cend() == it) return BOOST_APPLICATION_FEATURE_NS_SELECT::
           shared_ptr<T>();

        return BOOST_APPLICATION_FEATURE_NS_SELECT::
           static_pointer_cast<T>(it->second);
      }

      template <class T>
      BOOST_APPLICATION_FEATURE_NS_SELECT::
         shared_ptr<const T> get_aspect() const
      {
        map_type::const_iterator it = aspects_.find(key_type(typeid(T)));
        if (aspects_.cend() == it) return BOOST_APPLICATION_FEATURE_NS_SELECT::
           shared_ptr<T>();

        return BOOST_APPLICATION_FEATURE_NS_SELECT::
           static_pointer_cast<const T>(it->second);
      }

      template <class T>
      T& use_aspect()
      {
        map_type::const_iterator it = aspects_.find(key_type(typeid(T)));

        if (aspects_.cend() == it)
          throw std::logic_error(std::string("Type ") + key_type(typeid(T)).name() + " is not an aspect");

        return *BOOST_APPLICATION_FEATURE_NS_SELECT::
           static_pointer_cast<T>(it->second);

      }

      template <class T>
      T const& use_aspect() const
      {
        map_type::const_iterator it = aspects_.find(key_type(typeid(T)));
        if (aspects_.cend() == it)
          throw std::logic_error(std::string("Type ") + key_type(typeid(T)).name() + " is not an aspect");

        return *BOOST_APPLICATION_FEATURE_NS_SELECT::
           static_pointer_cast<T>(it->second);

      }

      template <class T>
      void replace_aspect(BOOST_APPLICATION_FEATURE_NS_SELECT::
                             shared_ptr<T> asp)
      {
#ifndef BOOST_NO_CXX11_HDR_TYPEINDEX
         key_type ti = typeid(T);
#else
         key_type ti = type_id<T>();
#endif
        if(aspects_.erase(ti))
          aspects_.insert(std::make_pair(ti, asp));
      }

      template <class T>
      void remove_aspect(BOOST_APPLICATION_FEATURE_NS_SELECT::
                            shared_ptr<T> asp)
      {
#ifndef BOOST_NO_CXX11_HDR_TYPEINDEX
         key_type ti = typeid(T);
#else
         key_type ti = type_id<T>();
#endif
        aspects_.erase(ti);
      }


    };
  }
}

#endif // header

