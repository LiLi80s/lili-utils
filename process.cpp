/*************************************************************************
* Copyright Liqun LIU [liulq80s@gmail.com]
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/


#include <iostream>
#include <pthread.h>
using namespace std;

#include "mutex.h"
#include "message_queue.h"
#include "message.h"

int Process::launch(){

	int i, fd0, fd1, fd2;
    pid_t pid;

    struct rlimit rl;
    struct sigaction sa;

    umask(0);

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        cout<<"Process " <<": can't get file limit" << endl;;

    if ((pid = fork()) < 0){
    	cout<<"Process "<<": can't fork"<< endl;
    }else if (pid != 0) {
    	/* parent */

    	return 0;
    }

    setsid();


    if (rl.rlim_max == RLIM_INFINITY) rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; i++)
        close(i);

   /*
	* Attach file descriptors 0, 1, and 2 to /dev/null.
	*/

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	//execlp();
    main();

    return 0;
}

int Process::main(){
	return 0;
}

int Process::daemonize(){
    int i, fd0, fd1, fd2;
    pid_t pid;

    struct rlimit rl;
    struct sigaction sa;

   /*
    * Clear file creation mask.
    */

    umask(0);

   /*
    * Get maximum number of file descriptors.
    */

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err_quit("%s: can't get file limit", cmd);
   /*
    * Become a session leader to lose controlling TTY.
    */

    if ((pid = fork()) < 0) err_quit("%s: can't fork", cmd);
    else if (pid != 0) /* parent */ exit(0);

    setsid();

   /*
    * Ensure future opens won't allocate controlling TTYs.
    */

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("%s: can't ignore SIGHUP");
   /*fork process again*/
    if ((pid = fork()) < 0)
        err_quit("%s: can't fork", cmd);
    else if (pid != 0) /* parent */
        exit(0);

   /*
    * Change the current working directory to the root so
    * we won't prevent file systems from being unmounted.
    * This document was created by an unregistered ChmMagic,
    * please go to http://www.bisenter.com to register it. Thanks
    */

    if (chdir("/") < 0)
        err_quit("%s: can't change directory to /");

   /*
    * Close all open file descriptors.
    */

    if (rl.rlim_max == RLIM_INFINITY) rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; i++) close(i);

   /*
    * Attach file descriptors 0, 1, and 2 to /dev/null.
    */

    fd0 = open("/dev/null", O_RDWR); fd1 = dup(0);
    fd2 = dup(0);

   /*
    * Initialize the log file.
    */

    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
	return 0;
}

int Process::wait(void){
    return 0;
}

int Process::kill(void){
    return 0;
}


