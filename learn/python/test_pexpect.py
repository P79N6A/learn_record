#!/usr/bin/env python
# coding=utf-8
# by orientlu

import pexpect
import sys, os
import time
import getpass

class pexpect_test:

    def __init__(self):
       self.host = 'localhost'
       self.port = '36000'
       self.user='lcd'
       self.cmd = 'pwd'

    def log_file(self, cmd='ls -l', logfile='./pexpect_test.log'):
        """
        run a cmd and write the output into log file
        """
        with open(logfile, "ab") as outfile:
            p = pexpect.spawn(cmd)
            p.logfile = outfile
            p.expect(pexpect.EOF)

    def stdout_cmd(self, cmd='pwd'):
        p = pexpect.spawn(cmd)
        p.logfile = sys.stdout
        p.expect(pexpect.EOF)

    def ssh_cmd_1(self):

        child = pexpect.spawn('ssh -p %s -l %s %s %s'%(self.port, self.user, self.host, self.cmd))
        i = child.expect([pexpect.TIMEOUT, 'yes/no', 'assword'])
        if i == 0:
            print("timeout1")
            return None
        elif i == 1:
            child.sendline('yes')
            time.sleep(0.1)
            i = child.expect([pexpect.TIMEOUT, 'assword'])
            if i == 0:
                print("timeout2")
                return None

        password= getpass.getpass()
        child.sendline(password)
        child.expect(pexpect.EOF)
        print(child.before)
        print(child.after)
        #child.interact()

    def ssh_cmd(self):
        child = pexpect.spawn('ssh -p %s -l %s %s'%(self.port, self.user, self.host))
        i = child.expect([pexpect.TIMEOUT, 'yes/no', 'assword'])
        if i == 0:
            print("timeout1")
            return None
        elif i == 1:
            child.sendline('yes')
            time.sleep(0.1)
            i = child.expect([pexpect.TIMEOUT, 'assword'])
            if i == 0:
                print("timeout2")
                return None

        password= getpass.getpass()
        child.sendline(password)
        child.expect(self.user) # wait
        child.sendline('cd ~/')
        child.expect(self.user)
        child.sendline("touch test_aa")
        child.expect(self.user)
        print(child.before)
        print(child.after)
        #child.interact()

    def ssh_by_paramiko(self):
        import paramiko
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect('localhost', '36000', 'lcd', 'jklfds', timeout=5)
        cmds = ['ls', 'uptime', 'pwd', 'cd /home', 'pwd']
        for cmd in cmds:
            stdin, stdout, stderr = ssh.exec_command(cmd)
            #stdin.write('Y')
            out = stdout.readlines()
            for o in out:
                print(o)
        ssh.close()

if __name__ == '__main__':
    test = pexpect_test()
    #test.log_file()
    #test.stdout_cmd()
    #test.ssh_cmd1()
    test.ssh_cmd()
    #test.ssh_by_paramiko()
