#!/usr/bin/env python
# coding=utf-8
# by orientlu
import  ConfigParser

test_cfg = "./default.cfg"

def raw_configparser_rw_test(test_cfg):

    config_raw = ConfigParser.RawConfigParser()
    config_raw.read(test_cfg)

    defaults = config_raw.defaults()
    print defaults

    a_float = config_raw.getfloat('Section1', 'a_float')
    print "-- number : %f type is : %s"%(a_float ,type(a_float))

    a_float = 2.14159
    config_raw.set('Section1', 'a_float', a_float)
    a_float = config_raw.getfloat('Section1', 'a_float')
    print "-- number : %f type is : %s"%(a_float ,type(a_float))

    print "-- RawConfigParser just get raw value"
    str_foo = config_raw.get('Section1', 'foo')
    print str_foo


def configparser_rw_test(test_cfg):

    config = ConfigParser.ConfigParser()
    config.read(test_cfg)

    print "-- ConfigParser can get interpolation"
    str_foo = config.get('Section1', 'foo', raw=1)
    #str_foo = config.get('Section1', 'foo', 1)
    print str_foo
    str_foo = config.get('Section1', 'foo')
    print str_foo
    str_foo = config.get('Section1', 'foo', 0)
    print str_foo

    print "-- After set a new value"
    str_foo = "%(name)s is %(baz)s!"
    config.set('Section1', 'foo', str_foo)
    str_foo = config.get('Section1', 'foo', 1)
    print str_foo
    str_foo = config.get('Section1', 'foo')
    print str_foo

    str_foo = config.get('Section1', 'name')
    print str_foo

    print "-- use default value if pass by vars={}"
    a_float = config.get('Section1', 'a_float1', vars={'a_float1':'0.01'})
    print "-- number : %f type is : %s"%(float(a_float) ,type(a_float))


def use_default_cfg_test():

    config = ConfigParser.ConfigParser()
    config.readfp(open('./default.cfg'))
    config.read(['./user1.cfg', './user2.cfg', './user3.cfg'])
    #config.read(['./user11111111.cfg', './user22222222.cfg'])

    an_int = config.getint('Section1', 'an_int')
    print "-- number : %f type is : %s"%(an_int ,type(an_int))

    str_foo = config.get('Section1', 'name')
    print str_foo


def use_default_value_test():

    config = ConfigParser.ConfigParser({'name' : 'default_name'})
    config.readfp(open('./default.cfg'))

    str_foo = config.get('Section1', 'name')
    print str_foo
    print "-- use default value"
    config.remove_option('Section1', 'name')
    str_foo = config.get('Section1', 'name')
    print str_foo


if __name__ == "__main__":
    #raw_configparser_rw_test(test_cfg)

    #configparser_rw_test(test_cfg)

    use_default_cfg_test()

    #use_default_value_test()
