#!/usr/bin/env python
##
# @file       post_build.py
# @author     SIANA Systems
# @date       02/2021
# @copyright  The MIT License (MIT)
# @brief      Post-build script for Oxpecker Platform Library Build
#
# This python script is used as the post-build when building the Oxpecker
# platform library build. It purpose is renaming the resulting file and moving
# it to a proper location, then clean up other build artifacts
#
# The script should be configured for the project (TUNABLES section.)
# Requirements:
#    - Python 3.x (validted with 3.9)
#
# Installing dependencies:
#    - siana's build utilities: sbutils (see TUNABLES)
#    
# Usage: post_build.py
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

from struct import *
import sys, os
import CppHeaderParser
import json
import glob

#--->> TUNABLES <<-----------------------------------------

# path to project root: ../../
root_path = os.path.realpath(os.path.join(os.path.dirname(__file__),  ".."))

# relative path to project folder
prj_path = os.path.join(root_path, "EWARM")



#----------------------------------------------------------

verbose = True


#--->> Generate App Map <<--------------------------------

# Initialize empty application map (as a dictionary)
raw_application_map = {}
application_map = {}

gui_path = os.path.join(root_path, "TouchGFX", "gui","include")
out_path = os.path.join(root_path, "Tools","application_map.json")
default_path = os.path.join(root_path, "Tools","default_map.json")
cache_path= os.path.join(root_path, "Tools", "code_cache", "include" )
tgfx_path = glob.glob(os.path.join(root_path ,'TouchGFX', '*.touchgfx' ))[0]
tgfx_cache_path=os.path.join(root_path, "Tools","OxpeckerTGFXTemplate.dat")

#Backup old application_map in RAM for comparison
with open(default_path, 'r') as file:
    old_app_map =  json.load(file)
    file.close()
    
# Iterate over the entire /gui/ folder
for root, dirs, files in os.walk(gui_path):
    # For every file in the gui folder
    for filename in files:
        header = CppHeaderParser.CppHeader(os.path.join(root,filename))
        # #f the header contains an actual class
        if len(header.CLASSES) > 0:
            for classname in header.CLASSES.keys():
                # Review from what classes do each class inherit from
                inheritlist = header.CLASSES[classname]['inherits']
                if len(inheritlist) > 0:
                    for baseclass in inheritlist:
                        if baseclass['class'] in raw_application_map:
                            raw_application_map[baseclass['class']].append(classname)
                        else:
                            raw_application_map[baseclass['class']] = [classname]
                            
#Also iterate over code cache folder - to include "disabled" applications
for root, dirs, files in os.walk(cache_path):
 # For every file in the cache folder
    for filename in files:
        header = CppHeaderParser.CppHeader(os.path.join(root,filename))
        # if the header contains an actual class
        if len(header.CLASSES) > 0:
            for classname in header.CLASSES.keys():
                # Review from what classes do each class inherit from
                inheritlist = header.CLASSES[classname]['inherits']
                if len(inheritlist) > 0:
                    for baseclass in inheritlist:
                        if baseclass['class'] in raw_application_map:
                            raw_application_map[baseclass['class']].append(classname)
                        else:
                            raw_application_map[baseclass['class']] = [classname]

# clear the application map from irrelevant entries & Template App
for classes  in raw_application_map['OxpeckerApplication']:
    if classes == 'TemplateApp':
        continue
    # Fixed in case there is a key duplicate
    if classes in raw_application_map:
        entry = raw_application_map.pop(classes)
        application_map[classes] = entry

json_dump =json.dumps(application_map, sort_keys=True, indent=2)
with open(out_path, 'w') as file:
    file.write(json_dump)
    file.close()

#Compre Old and New App maps - remove all default Zebra apps
for app in list(application_map):
    if app in old_app_map:
        application_map.pop(app)

if len(application_map) == 0:
    #no new apps -> Just quit, we are finished
    exit(0)

#Compare Baseline and current TGFX projects
with open(tgfx_cache_path, 'r') as file:
    tgfx_baseline =  json.load(file)
    file.close()
with open(tgfx_path, 'r') as file:
    tgfx_project =  json.load(file)
    file.close()

#seek every screen in the current TGFX Project
for screen in tgfx_project['Application']['Screens']:
    #See if it a part of the new application screens
    for apps in application_map.keys():
        for appscreen in application_map[apps]:
            if (screen['Name']+ 'View') == appscreen:
                #It is - See if it exist in Baseline
                for basescreen in tgfx_baseline['Application']['Screens']:
                    if screen['Name'] == basescreen['Name']:
                        # update it ->remove old version
                        tgfx_baseline['Application']['Screens'].remove(basescreen)
                #Add the new one
                tgfx_baseline['Application']['Screens'].append(screen)

#Save new baseline
with open(tgfx_cache_path, 'w') as f:
    json.dump(tgfx_baseline, f, indent=4)
    f.close()


# done -> all good!
exit(0)
