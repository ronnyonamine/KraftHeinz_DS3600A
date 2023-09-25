#!/usr/bin/env python
##
# @file       tasks.py
# @author     SIANA Systems
# @date       03/2021
# @copyright  The MIT License (MIT)
# @brief      Post-Deployment Customization Script for Oxpecker-based projects
#
# This python scripts uses Python Invoke to define project tasks:
#   - run: invoke --list
#
# The script is expected to be called from the Tools folder in the Deployed
# project folder
#
# Requirements (in Path):
#    - Python 3.6 or higher
#    - git client
#    - doxygen
#    - Touchgfx 4.14.0 environment on path
#    - IAR Embedded Workbench of ARM 8.50.1 on path
#
# Installing dependencies:
#    - Invoke: pip install invoke
#    
# Usage: see invoke => http://pyinvoke.org
#------------------------------------------------------------------------------
# The MIT License (MIT)
# 
# Copyright (c) 2021 Siana Systems
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#  
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#------------------------------------------------------------------------------

__author__ = "SIANA Systems"
__license__ = "MIT"
__version__ = "ALPHA"
__email__ = "support@siana-systems.com"
#----------------------------------------------------------

import sys, os, json
from invoke import task, Collection
from pathlib import Path
import glob
import time

#--->> TUNABLES <<-----------------------------------------

tools_path = os.path.realpath(os.path.join(os.path.dirname(__file__)))

tgfx_project_file  = ""
tgfx_apptemp_file  = ""
application_map_file =  os.path.join(tools_path, 'application_map.json')
tgfx_gui_folder = os.path.join(tools_path, '..' ,'TouchGFX_Oxpecker', 'gui' )
code_reserve_folder = os.path.join(tools_path, 'code_cache' )
tgfx_template_file =  os.path.join(tools_path, 'OxpeckerTGFXTemplate.dat')
tgfx_tempscreen_file =  os.path.join(tools_path, 'TemplateScreen.dat')

tgfx_executable = r'C:\TouchGFX\4.14.0\designer\tgfx.exe'

#--->> Definitions <<--------------------------------------
APP_STATE_DISABLED = 0
APP_STATE_PARTIAL  = 1
APP_STATE_ENABLED  = 2

#--->> Preamble <<-----------------------------------------

#--->> Function Definitions <<-----------------------------
def get_touchgfx_folder():
    # Checks which one is the TouchGFX folder
    # First option for dev is ../TouchGFX_Oxpecker
    path = os.path.join(tools_path, '..', 'TouchGFX_Oxpecker')
    print(path)
    if (os.path.exists(path)):
        return 'TouchGFX_Oxpecker'
    # Else, use the msi path ../TouchGFX
    return 'TouchGFX'

def preamble(c):
    global app_map, tgfx_project, tgfx_project_file, tgfx_apptemp_file, tgfx_gui_folder
    
    touch_gfx_folder = get_touchgfx_folder()
    tgfx_project_file  = glob.glob(os.path.join(tools_path, '..', touch_gfx_folder, '*.touchgfx' ))[0]
    tgfx_apptemp_file  = glob.glob(os.path.join(tools_path, '..', touch_gfx_folder,  '*.part' ))[0]
    tgfx_gui_folder = os.path.join(tools_path, '..', touch_gfx_folder,  'gui' )
    
    with open(application_map_file) as app_map_file:
        app_map = json.load(app_map_file)
        app_map_file.close()

    with open(tgfx_apptemp_file, 'r') as f:
        tgfx_app_template = json.load(f)
    with open(tgfx_apptemp_file, 'w') as f:
        tgfx_app_template['Application'][
            'PostGenerateTargetCommand'] = "touchgfx update_project --project-file=../STM32L4R7I_OCB.ioc --platform=m4"
        json.dump(tgfx_app_template, f, indent=2)
        f.close()

    with open(tgfx_project_file, 'r') as f:
        tgfx_project = json.load(f)
    with open(tgfx_project_file, 'w') as f:
        tgfx_project['Application'][
            'PostGenerateTargetCommand'] = "touchgfx update_project --project-file=../STM32L4R7I_OCB.ioc --platform=m4"
        json.dump(tgfx_project, f, indent=2)
        f.close()

@task
def list_application_status(c):
    """
    Provides list of currently supported applications and state
    """
    preamble(c)
    global tgfx_project, app_map
    for application in app_map.keys():
        # Remove specific "platform" categories from List
        if application != 'SettingLeaf' and application != 'ZebraPlatformScreen' and application != 'DefaultApp':
            #Check if the views corresponding to these apps are currently included in the project
            print('{} ='.format(application), end=' ' )
            appState = APP_STATE_DISABLED
            screenList = []
            for screen in tgfx_project['Application']['Screens']:
                screenView = '{}View'.format(screen['Name'])
                for appscreen in app_map[application]:
                    if screenView == appscreen:
                        appState = APP_STATE_PARTIAL
                        screenList.append(screenView)
            #we compare the list of included screens against full application screen list
            if len(screenList) == len(app_map[application]):
                appState = APP_STATE_ENABLED
                print('Enabled')
            else:
                if appState == APP_STATE_PARTIAL:
                    print('Partially Enabled')
                else:
                    print('Disabled')

@task(help={'app': "Name of the application to disable from build as listed in list-application-status"})
def disable_application(c, app):
    """
    Disables the application passed as a parameter
    """
    preamble(c)
    global tgfx_project, app_map
    # Check if the application to remove exist within the application map
    if app in app_map.keys():
        # remove all screens associated with this application
        for appscreen in app_map[app]:
            for screen in tgfx_project['Application']['Screens']:
                screenView = '{}View'.format(screen['Name'])
                if screenView == appscreen:
                    tgfx_project['Application']['Screens'].remove(screen)
                    #move the User sources to a "reserve" folder
                    folder_name = '{}_screen'.format(screen['Name'].lower())
                    header_name = '{}App.hpp'.format(screen['Name'][2:])
                    include_folder = os.path.join(tgfx_gui_folder, 'include', 'gui', folder_name)
                    source_folder = os.path.join(tgfx_gui_folder, 'src', folder_name)
                    common_header = os.path.join(tgfx_gui_folder, 'include', 'gui', 'common', header_name)
                    common_header_alt = os.path.join(tgfx_gui_folder, 'include', 'gui', 'common', 'ApplicationClasses', header_name)
                    if os.path.exists(include_folder):
                        c.run('xcopy {} {} /E/H/I/Y '.format(include_folder,
                                                         os.path.join(code_reserve_folder, 'include', folder_name)))
                    if os.path.exists(source_folder):
                        c.run('xcopy {} {} /E/H/I/Y '.format(source_folder,
                                                         os.path.join(code_reserve_folder, 'src', folder_name)))
                    if os.path.exists(common_header):
                        c.run('copy {} {}'.format(common_header,
                                                         os.path.join(code_reserve_folder, 'include', 'common', header_name)))
                    # Temporaly removed due to conflicts with AppClasses.hpp
                    # if os.path.exists(common_header_alt):
                        # c.run('copy {} {}'.format(common_header_alt,
                                                         # os.path.join(code_reserve_folder, 'include', 'common', header_name)))
                    if os.path.exists(include_folder):
                        c.run('rmdir {} /Q/S'.format(include_folder))
                    if os.path.exists(source_folder):
                        c.run('rmdir {} /Q/S'.format(source_folder))
                    if os.path.exists(common_header):
                        c.run('del {}'.format(common_header))
                    # Temporaly removed due to conflicts with AppClasses.hpp
                    # if os.path.exists(common_header_alt):
                        # c.run('del {}'.format(common_header_alt))
        with open(tgfx_project_file, 'w') as f:
            tgfx_project['Application']['PostGenerateTargetCommand'] = "touchgfx update_project --project-file=../STM32L4R7I_OCB.ioc --platform=m4"
            json.dump(tgfx_project, f, indent=2)
            f.close()
            print('>> Application removed from TGFX project')
        print('>> Regenerating Codebase')
        c.run('tgfx generate -p {}'.format(tgfx_project_file))
    else:
        print('>> Application does no exist in the application map')

@task(help={'app': "Name of the application to enable as listed in list-application-status"})
def enable_application(c, app):
    """
    Enables the application passed as a parameter
    """
    preamble(c)
    global tgfx_project, app_map
    # Check if the application to restore exist within the application map
    if app in app_map.keys():
        #It exist, so we only need to re-incorporate into the TouchGFX Project
        with open(tgfx_template_file, 'r') as f:
            tgfx_original = json.load(f)
            f.close()
        #For all screens in the original/expanded screens
        for screen in tgfx_original['Application']['Screens']:
            screenView = '{}View'.format(screen['Name'])
            #if the screen corresponds to the application....
            if screenView in app_map[app]:
                #... and the screen is removed from the main tgfx project
                if screen not in tgfx_project['Application']['Screens']:
                    # ... add to it back to the tgfx project.
                    tgfx_project['Application']['Screens'].append(screen)
                    #... and restore the sources
                    folder_name = '{}_screen'.format(screen['Name'].lower())
                    header_name = '{}App.hpp'.format(screen['Name'][2:])
                    include_folder = os.path.join(tgfx_gui_folder, 'include', 'gui', folder_name)
                    source_folder = os.path.join(tgfx_gui_folder, 'src', folder_name)
                    common_header = os.path.join(tgfx_gui_folder, 'include', 'gui', 'common', header_name)
                    if os.path.exists(os.path.join(code_reserve_folder, 'include', folder_name)):
                        c.run('xcopy {} {} /E/H/I/Y '.format(os.path.join(code_reserve_folder, 'include', folder_name),include_folder))
                    if os.path.exists(os.path.join(code_reserve_folder, 'src', folder_name)):
                        c.run('xcopy {} {} /E/H/I/Y '.format(os.path.join(code_reserve_folder, 'src', folder_name),source_folder))
                    if os.path.exists(os.path.join(code_reserve_folder, 'include', 'common', header_name)):
                        c.run('copy {} {}'.format(os.path.join(code_reserve_folder, 'include', 'common', header_name),common_header))
                    if os.path.exists(os.path.join(code_reserve_folder, 'include', folder_name)):
                        c.run('rmdir {} /Q/S'.format(os.path.join(code_reserve_folder, 'include', folder_name)))
                    if os.path.exists(os.path.join(code_reserve_folder, 'src', folder_name)):
                        c.run('rmdir {} /Q/S'.format(os.path.join(code_reserve_folder, 'src', folder_name)))
                    if os.path.exists(os.path.join(code_reserve_folder, 'include', 'common', header_name)):
                        c.run('del {}'.format(os.path.join(code_reserve_folder, 'include', 'common', header_name)))
        with open(tgfx_project_file, 'w') as f:
            tgfx_project['Application']['PostGenerateTargetCommand'] = "touchgfx update_project --project-file=../STM32L4R7I_OCB.ioc --platform=m4"
            json.dump(tgfx_project, f, indent=2)
            f.close()
            print('>> Application restored into the TGFX project')
        print('>> Regenerating Codebase')
        c.run('tgfx generate -p {}'.format(tgfx_project_file))
    else:
        print('>> Application does no exist in the application map')

@task(help={'appname': "Name of the new application", 'displayname': "Name to de displayed on the Device Menu"})
def create_application(c, appname, displayname):
    """
    Generates a new empty application
    """
    preamble(c)
    global tgfx_project, app_map
    if len(appname) > 16:
        print(">>> Application name too long - should be 16 characters or less")
        return
    #Checks the application map to see if there is already an app with that name
    appnameapp = appname + 'App'
    if appnameapp in app_map.keys():
        #app already exists -> return
        print(">>> There is already an application with that name")
        return
    
    #loads the new application template for the touchgfx project
    with open(tgfx_tempscreen_file, 'r') as f:
        tgfx_original = json.load(f)
        f.close()
    # Retrieve the Template Screen from it
    for screen in tgfx_original['Application']['Screens']:
        if screen['Name'] == 'SnTemplate':
            template_screen = screen
    #Rename the screen based on provided name
    template_screen['Name'] = 'Sn'+ appname
    template_screen['Interactions'][0]['Action']['ActionComponent'] = template_screen['Name']
    #Add New Application to the TGFX file
    tgfx_project['Application']['Screens'].append(template_screen)
    with open(tgfx_project_file, 'w') as f:
        tgfx_project['Application'][
            'PostGenerateTargetCommand'] = "touchgfx update_project --project-file=../STM32L4R7I_OCB.ioc --platform=m4"
        json.dump(tgfx_project, f, indent=2)
        f.close()
    #Copy Template User files into the project
    folder_name = '{}_screen'.format(template_screen['Name'].lower())
    include_folder = os.path.join(tgfx_gui_folder, 'include', 'gui', folder_name)
    source_folder = os.path.join(tgfx_gui_folder, 'src', folder_name)
    common_folder = os.path.join(tgfx_gui_folder, 'include', 'gui', 'common')
    c.run('xcopy {} {} /E/H/I/Y '.format(os.path.join(code_reserve_folder, 'include', 'sntemplate_screen'), include_folder))
    c.run('xcopy {} {} /E/H/I/Y '.format(os.path.join(code_reserve_folder, 'src', 'sntemplate_screen'), source_folder))
    c.run('xcopy {} {} /E/H/I/Y '.format(os.path.join(code_reserve_folder, 'include', 'common'), common_folder))
    #Rename Template User Files
    viewhpp = os.path.join(include_folder, 'Sn'+ appname +'View.hpp')
    presenterhpp = os.path.join(include_folder, 'Sn' + appname + 'Presenter.hpp')
    viewcpp = os.path.join(source_folder, 'Sn' + appname + 'View.cpp')
    presentercpp = os.path.join(source_folder, 'Sn' + appname + 'Presenter.cpp')
    baseclasshpp = os.path.join(common_folder, appname + 'App.hpp')
    c.run('rename {} {}'.format(os.path.join(include_folder, 'SnTemplatePresenter.hpp'), 'Sn' + appname + 'Presenter.hpp'))
    c.run('rename {} {}'.format(os.path.join(include_folder, 'SnTemplateView.hpp'), 'Sn'+ appname +'View.hpp'))
    c.run('rename {} {}'.format(os.path.join(source_folder, 'SnTemplatePresenter.cpp'), 'Sn' + appname + 'Presenter.cpp'))
    c.run('rename {} {}'.format(os.path.join(source_folder, 'SnTemplateView.cpp'), 'Sn' + appname + 'View.cpp'))
    c.run('rename {} {}'.format(os.path.join(common_folder, 'TemplateApp.hpp'),  appname + 'App.hpp'))
    #Modify Contents of the files
    source_files = [ viewhpp, viewcpp, presentercpp, presenterhpp, baseclasshpp]
    for path in source_files:
        f = open(path, 'r')
        temp_string = []
        for line in f:
             temp_string.append(line.replace('Template', appname))
        f.close()
        f = open(path, 'w')
        f.writelines(temp_string)
        f.close()
    #UpperCases in header Defines
    for path in source_files:
        f = open(path, 'r')
        temp_string = []
        for line in f:
            temp_string.append(line.replace('TEMPLATE', appname.upper()))
        f.close()
        f = open(path, 'w')
        f.writelines(temp_string)
        f.close()
    # UpperCases in header Defines
    for path in source_files:
        f = open(path, 'r')
        temp_string = []
        for line in f:
            temp_string.append(line.replace('template', appname.lower()))
        f.close()
        f = open(path, 'w')
        f.writelines(temp_string)
        f.close()
    #Application Name on Menu
    with open(viewcpp,'r') as file:
        temp_string = []
        for line in file:
            temp_string.append(line.replace('TempName', displayname))
        file.close()
    f = open(viewcpp, 'w')
    f.writelines(temp_string)
    f.close()
    #Add new application to application Map
    app_map[appname+'App'] = ['Sn'+appname+'View']
    time.sleep(2)
    print('>> Regenerating Codebase')
    c.run('tgfx generate -p {}'.format(tgfx_project_file))
    with open(application_map_file,'w') as file:
        json.dump(app_map, file, indent=2)
        file.close()
    print('>> Application {} Added to project'.format(appname))
    
@task(help={'appname': "Name of the new application", 'displayname': "Name to de displayed on the Device Menu"})
def create_minimal(c, appname, displayname):
    """
    Generates a new minimal empty application
    """
    preamble(c)
    global tgfx_project, app_map
    if len(appname) > 16:
	    print(">>> Application name too long - should be 16 characters or less")
	    return	
    #Checks the application map to see if there is already an app with that name
    appnameapp = appname + 'App'
    if appnameapp in app_map.keys():
        #app already exists -> return
        print(">>> There is already an application with that name")
        return
    
    #loads the new application template for the touchgfx project
    with open(tgfx_tempscreen_file, 'r') as f:
        tgfx_original = json.load(f)
        f.close()
    # Retrieve the Template Screen from it
    for screen in tgfx_original['Application']['Screens']:
        if screen['Name'] == 'SnTemplate':
            template_screen = screen
    #Rename the screen based on provided name
    template_screen['Name'] = 'Sn'+ appname
    template_screen['Interactions'][0]['Action']['ActionComponent'] = template_screen['Name']
    #Add New Application to the TGFX file
    tgfx_project['Application']['Screens'].append(template_screen)
    with open(tgfx_project_file, 'w') as f:
        tgfx_project['Application'][
            'PostGenerateTargetCommand'] = "touchgfx update_project --project-file=../STM32L4R7I_OCB.ioc --platform=m4"
        json.dump(tgfx_project, f, indent=2)
        f.close()
    #Copy Template User files into the project
    folder_name = '{}_screen'.format(template_screen['Name'].lower())
    include_folder = os.path.join(tgfx_gui_folder, 'include', 'gui', folder_name)
    source_folder = os.path.join(tgfx_gui_folder, 'src', folder_name)
    common_folder = os.path.join(tgfx_gui_folder, 'include', 'gui', 'common')
    c.run('xcopy {} {} /E/H/I/Y '.format(os.path.join(code_reserve_folder, 'include', 'snminimal_screen'), include_folder))
    c.run('xcopy {} {} /E/H/I/Y '.format(os.path.join(code_reserve_folder, 'src', 'snminimal_screen'), source_folder))
    c.run('xcopy {} {} /E/H/I/Y '.format(os.path.join(code_reserve_folder, 'include', 'common_min'), common_folder))
    #Rename Template User Files
    viewhpp = os.path.join(include_folder, 'Sn'+ appname +'View.hpp')
    presenterhpp = os.path.join(include_folder, 'Sn' + appname + 'Presenter.hpp')
    viewcpp = os.path.join(source_folder, 'Sn' + appname + 'View.cpp')
    presentercpp = os.path.join(source_folder, 'Sn' + appname + 'Presenter.cpp')
    baseclasshpp = os.path.join(common_folder, appname + 'App.hpp')
    c.run('rename {} {}'.format(os.path.join(include_folder, 'SnMinimalPresenter.hpp'), 'Sn' + appname + 'Presenter.hpp'))
    c.run('rename {} {}'.format(os.path.join(include_folder, 'SnMinimalView.hpp'), 'Sn'+ appname +'View.hpp'))
    c.run('rename {} {}'.format(os.path.join(source_folder, 'SnMinimalPresenter.cpp'), 'Sn' + appname + 'Presenter.cpp'))
    c.run('rename {} {}'.format(os.path.join(source_folder, 'SnMinimalView.cpp'), 'Sn' + appname + 'View.cpp'))
    c.run('rename {} {}'.format(os.path.join(common_folder, 'MinimalApp.hpp'),  appname + 'App.hpp'))
    #Modify Contents of the files
    source_files = [ viewhpp, viewcpp, presentercpp, presenterhpp, baseclasshpp]
    for path in source_files:
        f = open(path, 'r')
        temp_string = []
        for line in f:
             temp_string.append(line.replace('Minimal', appname))
        f.close()
        f = open(path, 'w')
        f.writelines(temp_string)
        f.close()
    #UpperCases in header Defines
    for path in source_files:
        f = open(path, 'r')
        temp_string = []
        for line in f:
            temp_string.append(line.replace('MINIMAL', appname.upper()))
        f.close()
        f = open(path, 'w')
        f.writelines(temp_string)
        f.close()
    # UpperCases in header Defines
    for path in source_files:
        f = open(path, 'r')
        temp_string = []
        for line in f:
            temp_string.append(line.replace('minimal', appname.lower()))
        f.close()
        f = open(path, 'w')
        f.writelines(temp_string)
        f.close()
    #Application Name on Menu
    with open(viewcpp,'r') as file:
        temp_string = []
        for line in file:
            temp_string.append(line.replace('TempName', displayname))
        file.close()
    f = open(viewcpp, 'w')
    f.writelines(temp_string)
    f.close()
    #Add new application to application Map
    app_map[appname+'App'] = ['Sn'+appname+'View']
    time.sleep(2)
    print('>> Regenerating Codebase')
    c.run('tgfx generate -p {}'.format(tgfx_project_file))
    with open(application_map_file,'w') as file:
        json.dump(app_map, file, indent=2)
        file.close()
    print('>> Application {} Added to project'.format(appname))

@task(help={'app': "Name of the application to remove from build as listed in list-application-status"})
def remove_application(c, app):
    """
    Removes the application passed as a parameter
    """
    preamble(c)
    global tgfx_project, app_map
    # Check if the application to remove exist within the application map
    if app in app_map.keys():
        # remove all screens associated with this application
        for appscreen in app_map[app]:
            for screen in tgfx_project['Application']['Screens']:
                screenView = '{}View'.format(screen['Name'])
                if screenView == appscreen:
                    tgfx_project['Application']['Screens'].remove(screen)
                    # remove the User sources from project
                    folder_name = '{}_screen'.format(screen['Name'].lower())
                    header_name = '{}App.hpp'.format(screen['Name'][2:])
                    include_folder = os.path.join(tgfx_gui_folder, 'include', 'gui', folder_name)
                    source_folder = os.path.join(tgfx_gui_folder, 'src', folder_name)
                    common_header = os.path.join(tgfx_gui_folder, 'include', 'gui', 'common', header_name)
                    if os.path.exists(include_folder):
                        c.run('rmdir {} /Q/S'.format(include_folder))
                    if os.path.exists(source_folder):
                        c.run('rmdir {} /Q/S'.format(source_folder))
                    if os.path.exists(common_header):
                        c.run('del {}'.format(common_header))
        # remove the User source from "reserve" folder
        folder_name = 'sn{}_screen'.format(app[:-3].lower())
        header_name = '{}.hpp'.format(app)
        include_folder = os.path.join(code_reserve_folder, 'include', folder_name)
        source_folder = os.path.join(code_reserve_folder, 'src', folder_name)
        common_header = os.path.join(code_reserve_folder, 'include', 'common', header_name)
        if os.path.exists(include_folder):
            c.run('rmdir {} /Q/S'.format(include_folder))
        if os.path.exists(source_folder):
            c.run('rmdir {} /Q/S'.format(source_folder))
        if os.path.exists(common_header):
            c.run('del {}'.format(common_header))
        with open(tgfx_project_file, 'w') as f:
            tgfx_project['Application']['PostGenerateTargetCommand'] = "touchgfx update_project --project-file=../STM32L4R7I_OCB.ioc --platform=m4"
            json.dump(tgfx_project, f, indent=2)
            f.close()
            print('>> Application removed from TGFX project')
        print('>> Regenerating Codebase')
        c.run('tgfx generate -p {}'.format(tgfx_project_file))
        app_map.pop(app, None)
        with open(application_map_file,'w') as file:
            json.dump(app_map, file, indent=2)
            file.close()
        print('>> Application {} removed from project'.format(app))
    else:
        print('>> Application does no exist in the application map')
