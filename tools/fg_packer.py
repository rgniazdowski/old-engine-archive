#!/usr/bin/env python2.7
# ''''''''''''''''''''''''''''''''''''''''''''''''''''''
# Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
#
# This file is part of FlexiGame: Flexible Game Engine
#
# FlexiGame source code and any related files can not be copied, modified
# and/or distributed without the express or written consent from the author.
# ''''''''''''''''''''''''''''''''''''''''''''''''''''''
#
import os
import sys
import string
from optparse import OptionParser, make_option

here = os.path.dirname(os.path.abspath(__file__))
fgroot = os.path.realpath(os.path.join(here, ".."))

class fgObj(object):
  pass

fg = fgObj()
fg.platform = fgObj()
fg.platform.linux = False
fg.platform.windows = False
fg.platform.cygwin = False
fg.platform.darwin = False
fg.platform.current = "None"
fg.rootdir = fgroot

from sys import platform as _platform
if _platform == "linux" or _platform == "linux2":
  fg.platform.current = "linux"
  fg.platform.linux = True
elif _platform == "darwin":
  fg.platform.current = "darwin"
  fg.platform.darwin = True
elif _platform == "win32":
  fg.platform.current = "windows"
  fg.platform.windows = True
elif _platform == "cygwin":
  fg.platform.cygwin = True
  fg.platform.current = "cygwin"

#
#
#
def check_s3e_dir():
  global fg
  if fg.platform.windows == True:
    if 'S3E_DIR' not in os.environ:
      print("**S3E_DIR not found in environment - setting default 7.4")
      fg.s3edir = "C:\Marmalade\7.4\s3e"
  else:
    fg.s3edir = False
    print("**INFO** S3E_DIR is not available on this platform")

#
#
#
def run():
  global fg
  print("*****************************************************************")
  print("** Copyright (C) FlexiGame Software - Packer tool - S3E/Marmalade")
  print("** NOTE: This is only for ARM builds (not x86)")
  print("** Project root dir: %s" % fg.rootdir)
  check_s3e_dir()
  if fg.s3edir == False:
	fg.s3edir = "/mnt/c/Marmalade/7.4/s3e"
	print("**ERROR** S3E_DIR not set. Exit...\n")
	#return False

  usage = "usage: %prog [options]"
  option_list = [
	make_option("--android", "--android-arm", action="store_true", dest="android", default=True, help="specify an ARM Android build to use to build the package (apk)"),
	make_option("--ios", "--ios-arm", "--iphone", action="store_true", dest="ios", default=False, help="specify an ARM iOS build to use to build the package (ipa)"),
	make_option("--debug", action="store_true", dest="debug", default=False, help="use the debug build version"),
	make_option("--release", action="store_false", dest="debug", help="use the release build version"),
	make_option("-c", "--config", action="store", type="string", dest="config", default="default", help="specify the target configuration for the deployment package"),
	make_option("--skip-itunes", action="store_true", dest="skip_itunes", default=False, help="skip the last stage - do not call iTunes for package upload"),
	make_option("--skip-ios-sign", "--skip-ios-resign", action="store_true", dest="skip_ios_sign", default=False, help="skip the execution of s3e signing tool - this will create unsigned package (ipa)"),
	make_option("--sign-distribution", "--sign-release", action="store_true", dest="sign_distribution", default=False, help="sign the deployment for distribution")
	]
  parser = OptionParser(usage=usage, option_list=option_list)
  options, args = parser.parse_args()
  fg.options = options

  if fg.options.debug == True:
	build = "debug"
	build_opt = "--debug"
  else:
	build = "release"
	build_opt = ""

  pkgextension=".apk"

  if fg.options.ios == True:
	deploy_os = "iphone"
	fg.options.android = False
	pkgextension=".ipa"
  elif fg.options.android == True:
	deploy_os = "android"
  else:
    deploy_os = "android"

  if fg.options.config == "default" or fg.options.config == "Default":
	deploy_config = "default"
	deploy_config_name = "Default"
	deploy_config_param = "-v"
	fg.pkgfilename="Infinium%s" % pkgextension
  else:
    deploy_config = fg.options.config
    deploy_config_name = fg.options.config
    deploy_config_param = "-v --config=%s" % deploy_config_name
    fg.pkgfilename="%s%s" % (fg.options.config, pkgextension)

  fg.builddir = "build_infinium_vc11"
  fg.projectname="Infinium"
  fg.deploymentdir=os.path.normpath("deployments/%s/%s/%s" % (deploy_config, deploy_os, build))

  if deploy_os == "android":
	fg.deploymentdir="%s/arm" % fg.deploymentdir

  fg.pkgfilepath=os.path.normpath("%s/%s" % (fg.deploymentdir, fg.pkgfilename))

  fg.full_pkgfilepath=os.path.realpath(fg.pkgfilepath)
  fg.full_deploymentdir=os.path.realpath(fg.deploymentdir)
  fg.full_builddir=os.path.realpath("%s/%s" % (fg.rootdir, fg.builddir))
  fg.mkbbat = os.path.normpath("%s/bin/mkb.bat" % fg.s3edir)
  fg.s3edeploybat = os.path.normpath("%s/bin/s3e_deploy.bat" % fg.s3edir)

  ### Checking the MKB project file
  if os.path.exists("%s/%s.mkb" % (fg.rootdir, fg.projectname)) == False:
	print "**ERROR** The main MKB project file does not exist! (%s.mkb)" % fg.projectname
	return False
  else:
	print "**INFO** Found the main MKB project file: %s.mkb" % fg.projectname

  ### Refreshing the deploy_config script file
  print "*****************************************************************"
  print "** Refreshing the %s/deploy_config.py configuration file" % fg.builddir
  command = "%s --verbose=1 --buildenv=VC11 %s.mkb --default-buildenv=vc11 --msvc-project --deploy-only" % (fg.mkbbat, fg.projectname)
  print "** Executing command: %s" % command
  # EXEC

  ### Checking for deploy_config.py existence
  print "*****************************************************************"
  print "** Checking for Python deploy config file: %s/deploy_config.py" % fg.builddir
  if os.path.exists("%s/%s/deploy_config.py" % (fg.rootdir, fg.builddir)) == False:
	print "**ERROR** The deploy config file is missing in build directory: %s" % fg.builddir
	return False
  else:
	print "**INFO** %s/deploy_config.py is available!" % fg.builddir

  ### Creating the special deploy package for the specified build
  print "*****************************************************************"
  print "** Creating deployment for %s - ARM - %s - %s - Config %s" % (string.capitalize(deploy_os),string.upper(build),string.capitalize(fg.projectname),deploy_config_name)
  command = "%s -n -f %s --os=%s %s --arch arm --gcc %s" % (fg.s3edeploybat, deploy_config_param, deploy_os, build_opt, os.path.join(fg.full_builddir, "deploy_config.py"))
  print "** Executing command: %s" % command
  # EXEC

  print "*****************************************************************"
  print "** %s Deployment folder path: %s" % (string.capitalize(build), fg.full_deploymentdir)
  print "** %s Deployment Certificates folder path: %s" % (string.capitalize(build), fg.full_deploymentdir)

#
#
def main():
  run()

if __name__ == '__main__':
  main()
