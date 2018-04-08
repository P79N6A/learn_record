#!/usr/bin/env python3
# coding=utf-8

import configparser

config = configparser.ConfigParser()
print("- Empty config %s"%config.sections())

print("- Load config file")
config.read("./example.ini")
print("> config sections : %s"%config.sections())
print('bitbucket.org' in config )
print("> Load config file is :")
for section in config.keys():
    print("[{s}]".format(s=section))
    for key in config[section]:
        print("{k} = {v}".format(k=key, v=config[section][key]))


print("\n- Get value like dict :user =  %s"%config['bitbucket.org']['user'])
conf_bitbucket = config['bitbucket.org']
print(conf_bitbucket['user'])

"""
The DEFAULT section which provides default values for all other sections"""
print("\n- DEFAULT Section")
for key in config['bitbucket.org']: print(key)
print("> Get default value : forwardx11 = %s\n"%config['bitbucket.org']['forwardx11'])


"""
recognizes Boolean values from 'yes'/'no', 'on'/'off', 'true'/'false' and '1'/'0'"""
print("\n- Support datatypes")
forwardx11 = config['bitbucket.org'].getboolean('forwardx11')
int_port = config.getint('topsecret.server.com', 'port')
float_port = config.getfloat('topsecret.server.com', 'port')
print("> Get int port = %d type : %s"%(int_port, type(int_port)))
print("> Get float port = %f type : %s"%(float_port, type(float_port)))

"""
return Fallback Values when value can not find(normal section and DEFAULT)
"""
print("\n- Retur Fallback")
print("> Get value user = %s"%(config.get('bitbucket.org', 'user')))
print("> Get value user = %s"%(config.get('bitbucket.org', 'user', fallback="fallback_name")))
print("> Get value forwardx11 = %s"%(config.getboolean('bitbucket.org', 'forwardx11', fallback=False)))
print("> Get value forwardx22 = %s"%(config.getboolean('bitbucket.org', 'forwardx22', fallback=False)))
print("> Get value user2 = %s"%(config.get('bitbucket.org', 'user2', fallback="fallback_name")))




print("\n- BasicInterpolation")
#default : config = configparser.ConfigParser(interpolation=configparser.BasicInterpolation())
config.read("./basic_interpolation.ini")
print("> Get raw value %s"%(config.get('Paths', 'my_dir', raw = 1)))
print("> Get value %s"%(config.get('Paths', 'my_dir', raw = 0)))


print("\n- ExtendedInterpolation - other sections")
config = configparser.ConfigParser(interpolation=configparser.ExtendedInterpolation())
config.read("./extended_interpolation.ini")
print("> Get raw value %s"%(config.get('Arthur', 'python_dir', raw = 1)))
print("> Get value %s"%(config.get('Arthur', 'python_dir', raw = 0)))



