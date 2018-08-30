#!/usr/bin/env python
# coding=utf-8
# by orientlu
## fabric version 1.14.0
import fabric
from fabric.api import *

class ssh_client(object):

    def __init__(self, hosts_list=None, roles_list=None):

        env.hosts=[]
        env.passwords={}
        env.roledefs = {}

        if hosts_list != None:
            for key in hosts_list.keys():
                env.hosts.append(key)
                env.passwords[key] = hosts_list[key]

        if roles_list != None:
            for key in roles_list.keys():
                env.roledefs[key] = roles_list[key]

    def _run_cmd(self, cmd, path=None):
        result = None
        if path != None:
            with cd(path):
                result = run(cmd, shell=False,warn_only=True,quiet=True)
        else:
            result = run(cmd, shell=False,warn_only=True,quiet=True)

        return result


    def remote_cmd(self, cmd, path=None,roles=None, is_parallel=0):
        if roles != None and len(roles) > 0:
            func=fabric.api.roles(*roles)(self._run_cmd)
        else:
            func=self._run_cmd

        if is_parallel == 1:
            func = fabric.api.parallel(func)

        result=execute(func,cmd,path)
        return result


    def local_cmd(self, cmd, path=None):
        result = None
        if path == None:
            path = './'
            with lcd(path):
                with settings(warn_only=True):
                    result = local(cmd, capture=1)

        return result

    def _get_file(self, remote_path=None, file_name=None, local_path='./', alias=None):
        if remote_path != None and file_name != None:
            with cd(remote_path):
                with lcd(local_path):
                    if alias == None:
                        alias = file_name
                        result = get(file_name, alias)
                    else:
                        result = None

        return result

    def get_file(self, remote_path=None, file_name=None, local_path='./', alias=None, roles=None):
        if roles != None and len(roles) > 0:
            func=fabric.api.roles(*roles)(self._get_file)
        else:
            func=self._get_file

        result=execute(func,remote_path, file_name, local_path, alias)
        return result


    def _put_file(self, src_path='./', file_name=None, dst_path=None, alias=None):
        if file_name != None and dst_path != None:
            with lcd(src_path):
                with cd(dst_path):
                    if alias == None:
                        alias = file_name
                        result = put(file_name, alias)
                    else:
                        result = None

        return result

    def put_file(self, src_path='./', file_name=None, dst_path=None, alias=None, roles=None, is_parallel=0):
        if roles != None and len(roles) > 0:
            func=fabric.api.roles(*roles)(self._put_file)
        else:
            func=self._put_file

        if is_parallel == 1:
            func = fabric.api.parallel(func)

        result=execute(func,src_path, file_name, dst_path, alias)
        return result


if __name__ == "__main__":
    #env.skip_bad_hosts = True
    #env.colorize_errors = True
    ## 主机登录信息
    hosts_list = {
            "lcd@192.168.37.134" : "jklfds",
            "lcd@192.168.37.135" : "jklfds",
            "lcd@192.168.37.136" : "jklfds",
            "lcd@192.168.37.137" : "jklfds",
    }

    ## 主机分组，按组执行任务
    roles_list = {
            "role1" : ["lcd@192.168.37.134"],
            "role2" : ["lcd@192.168.37.135", "lcd@192.168.37.137"],
            "role3" : ["lcd@192.168.37.134", "lcd@192.168.37.136"],
            "role4" : ["lcd@192.168.37.134"],
    }


    client = ssh_client(hosts_list, roles_list)

    result = client.remote_cmd("ls | wc -l", roles=["role1", "role3"])
    print result

    result = client.local_cmd("rm ./aa")
    print result

    client.get_file("/home/lcd", ".bashrc", local_path='./', alias='aa', roles=['role1'])

    client.put_file(file_name='aa', dst_path='/home/lcd', alias='cc', roles=['role1'])
