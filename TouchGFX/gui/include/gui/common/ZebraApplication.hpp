/**
  ******************************************************************************
  * @file    ZebraApplication.hpp
  * @author  SIANA Systems
  * @date    04/21/2021
  * @brief   Main class for Zebra application registering.
  *
  * The following class is the backbone of the framework. ZebraApplication
  * is a static class that contains a registry of all the applications that
  * needs to be rendered in the screen. The class provides a hook to update
  * screens dynamically depending of the current application state
  ******************************************************************************
  * @attention
  *
  * <h2><center>© COPYRIGHT 2020 SIANA Systems</center></h2>
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
  *
  ******************************************************************************
  */

#ifndef __ZEBRA_APPLICATION_HPP__
#define __ZEBRA_APPLICATION_HPP__

#include <string>
#include <vector>
#include <algorithm>
#include <gui/common/FrontendApplication.hpp>

/**
 * @brief Forward declaration for ApplicationData class.
 *
 * ApplicationData class resides below ZebraApplication, and
 * currently there is a circular dependency between ApplicationData
 * and ZebraApplication.
 */
class ApplicationData;

/**
 * @brief Pointer to FrontendApplication method.
 *
 * Redefinition of a FrontendApplication method pointer.
 * Used to transition between apps.
 */
typedef void (FrontendApplication::*transition_t)();
/*!
 * @brief ZebraApplication static class
 *
 * Main registration class for the Zebra Application API.
 * This class contains a static application list that can be
 * consulted globally using its static methods.
 */
class ZebraApplication
{
public:
    /**
    * @brief Registers a new Zebra application
    *
    * Appends the application to a static list that can be consulted
    * globally before runtime.
    *
    * @param application Application view
    */
    inline static void RegisterApplication(ZebraApplication application)
    {
        applications().push_back(application);
    }
    /**
    * @brief Returns the static list of Zebra Applications
    *
    * @retval std::vector<ZebraApplication>
    */
    inline static std::vector<ZebraApplication> GetApplications()
    {
        std::vector<ZebraApplication> apps;
      
        for(ZebraApplication app : applications())
        {
           if(app.app_entry)
           {
             apps.push_back(app);
           }
        }
        return apps;
    }
    /**
    * @brief Transitions to Zebra Application screen
    *
    * ZebraApplications contains a brief description of the
    * application, but also a reference to the function that
    * performs the transition. This method executes the 
    * transition engine to refresh the screen.
    */
    inline void transitionToApp()
    {
        (application().*(this->app_entry))();
    }
    /**
    * @brief Gets FrontendApplication instance
    *
    * Casts and return the FrontendApplication singleton instance.
    * This needs to be used with the pointer to transition since
    * it points to a FrontendApplication method.
    *
    * @retval FrontendApplication instance
    */
    static FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }
    /**
    * @brief Sorts the applications
    *
    * @retval None
    */
    inline static void Sort(void) {
        /* Since applications have display priority, sort them... */
        std::sort(
            applications().begin(), 
            applications().end(), 
            ZebraApplication::priority_sorter
        );
    }
    /**
    * @brief ZebraApplication constructor
    *
    * Initializes the Zebra Application description values
    *
    * @param app_name String representation of the application name
    * @param app Pointer to transition function
    * @param priority Priority of the application
    */
    ZebraApplication(std::string app_name, transition_t app, uint8_t priority) : 
        name(app_name),
        app_entry(app),
        priority(priority)
    { 

    }
    /**
    * @brief Application name
    *
    * This name is being used to render some texts on 
    * TouchGFX
    */
    std::string name;
    /**
    * @brief Pointer to transition
    *
    * Member that contains a reference to the method needed
    * to transition to application
    */
    transition_t app_entry;
    /**
    * @brief Priority
    *
    * This number is a priority weight for the application.
    * It can be used to sort the applications displayed on menu
    */
    uint8_t priority;

private:
    /**
    * @brief Static list that contains the description of all
    * Zebra Applications
    */ 
    static std::vector<ZebraApplication> & applications();
    /**
    * @brief Checks if a Zebra Application has priority
    *
    * @param a ZebraApplication with priority
    * @param b ZebraApplication with priority
    * @retval true if a priority is lower. False otherwise
    */
    static bool priority_sorter(ZebraApplication a, ZebraApplication b)
    {
        return a.priority < b.priority;
    }
};
/**
 * @brief Helper class for static constructor
 * 
 * The ApplicationData class implements a C++ static constructor by
 * instantiating it before runtime. The instantiation occurs when the
 * ZEBRA_APPLICATION macro is added to an application view.
 */
class ApplicationData
{
public:
    /**
    * @brief ApplicationData constructor
    *
    * Initializes the Zebra Application description values statically
    *
    * @param app_name String representation of the application name
    * @param app Pointer to transition function
    * @param priority Priority of the application
    */
    ApplicationData(std::string name, transition_t app, uint8_t priority)
    {
        ZebraApplication::RegisterApplication(
            ZebraApplication(name, app, priority)
        );    
    }
};
/**
 * @brief Adds a new ApplicationData member to a ZebraApplication
 * view. This allows a ZebraApplication to be registered before runtime
 */
#define ZEBRA_APPLICATION   public: \
                                static ApplicationData RegisterApplication;
/**
 * @brief Adds a ZebraApplication to the static list.
 */
#define REGISTER_APPLICATION(type, name, app, priority) ApplicationData type::RegisterApplication(name, app, priority);
/**
 * @brief Transform a FrontendApplication method name into a 
 * method reference
 */
#define TRANSITION_CALLBACK(cb) &FrontendApplication::cb

#endif
