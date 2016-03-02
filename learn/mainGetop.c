/*************************************************************************
	> File Name: mainGetop.c
	> Author: luchaodong
	> Mail: luchaodong@meizu.com
	> Created Time: Wed 02 Mar 2016 01:13:09 PM HKT
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
	int oc;		/*选项字符 */
	char ec;	/*无效的选项字符*/
	char *b_opt_arg;            /*选项参数字串 */

/*:ngl:  第一个 ，表示出错getopt不显示系统的提示，用户自定义
	第二个，表示， -l 后面必须跟参数*/
	while((oc = getopt(argc, argv, ":ngl:")) != -1)
	{
		switch(oc)
		{
		case 'n':
			printf("n\n");
			break;
		case 'g':
			printf("g:\n");
			break;
		case 'l':
			b_opt_arg = optarg;
			printf("-l %s\n", optarg);
			break;
		case '?':
			ec = (char)optopt;
			printf("无效的选项字符 \' %c \'!\n", ec);
			break;
		case ':':
			printf("缺少选项参数！\n");
			break;
		}
	}
	    return 0;

}
